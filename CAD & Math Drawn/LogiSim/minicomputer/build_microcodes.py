#!/usr/bin/env python3
"""
build_microcodes.py

Reads microcodes/signals.csv and microcodes/fsm.csv and generates:
  microcodes/signals.hex  — controlROM (128 entries × 14-bit, v3.0 hex words plain)
  microcodes/fsm.hex      — stateROM  (2048 entries × 3-bit,  v2.0 raw)

controlROM address: [currentState(3b) | opcode(4b)]          =  7 bits → 128 entries
stateROM  address: [currentState(3b) | opcode(4b) | flags(4b)] = 11 bits → 2048 entries

Control word layout (14 bits, MSB→LSB):
  13-12  srcPC[1:0]  — PC source when loadPC=1 (00=PC+1, 01=ALU, 10=Imm, 11=Bus)
  11     loadPC      — latch PC
  10     loadSP      — latch SP
   9     loadMAR     — latch MAR
   8     loadMDR     — latch MDR
   7     loadIR      — latch IR
   6     weReg       — write-enable register file
   5     memRead     — assert RAM read
   4     memWrite    — assert RAM write
   3     PC_out      — drive bus from PC
   2     MDR_out     — drive bus from MDR
   1     ALU_out     — drive bus from ALU
   0     Imm_out     — drive bus from Immediate Generator

signals.csv columns:
  state, opcode, srcPC, loadPC, loadSP, loadMAR, loadMDR, loadIR,
  weReg, memRead, memWrite, PC_out, MDR_out, ALU_out, Imm_out

fsm.csv columns:
  currentState, opcode, flags, nextState

  opcode and flags accept '*' or 'XXXX' as wildcards (all combinations).
  flags also accepts 4-char patterns like 'XX1X' (X = don't-care bit).
  Rows are applied top-to-bottom; later rows overwrite earlier ones.
"""

import csv
import os
import sys

# ---------------------------------------------------------------------------
# Lookup tables
# ---------------------------------------------------------------------------

STATE_NAMES = {
    'reset': 0, 'fetch1': 1, 'fetch2': 2, 'fetch3': 3,
    'decode': 4, 'execute': 5, 'memory': 6, 'writeback': 7,
}

OPCODE_NAMES = {
    'noop': 0,  'alu': 1,   'li': 2,    'mov': 3,
    'load': 4,  'store': 5, 'push': 6,  'pop': 7,
    'jmp': 8,   'beq': 9,   'bne': 10,  'blt': 11,
    'bge': 12,  'bmi': 13,  'bpl': 14,  'halt': 15,
}

# ---------------------------------------------------------------------------
# Parsers
# ---------------------------------------------------------------------------

def parse_state(s: str):
    s = s.strip().lower()
    if s in STATE_NAMES:
        return STATE_NAMES[s]
    return int(s, 0)


def parse_opcodes(s: str):
    """Return list of opcode integers; '*' expands to all 16."""
    s = s.strip().lower()
    if s == '*':
        return list(range(16))
    if s in OPCODE_NAMES:
        return [OPCODE_NAMES[s]]
    return [int(s, 0)]


def parse_flags(s):
    """
    Return list of flag nibble integers.
    '*' or 'XXXX'  → all 16 values
    '1001'         → [9]
    'XX1X'         → every value where bit 1 = 1 (8 values)
    Bit order: bit3=V, bit2=C, bit1=N, bit0=Z (MSB left in the pattern string)
    """
    s = s.strip().upper()
    if s in ('*', 'XXXX', 'X'):
        return list(range(16))
    if len(s) == 4 and all(c in 'X01' for c in s):
        results = []

        def expand(idx, acc):
            if idx == 4:
                results.append(acc)
                return
            c = s[idx]
            bit_pos = 3 - idx
            if c == 'X':
                expand(idx + 1, acc)
                expand(idx + 1, acc | (1 << bit_pos))
            else:
                expand(idx + 1, acc | (int(c) << bit_pos))

        expand(0, 0)
        return results
    # plain integer (binary or decimal)
    if all(c in '01' for c in s):
        return [int(s, 2)]
    return [int(s, 0)]


def parse_bit(val, default=0):
    v = str(val).strip()
    if v == '':
        return default
    return int(v) & 1


def parse_2bit(val, default=0):
    v = str(val).strip()
    if v == '':
        return default
    return int(v) & 3

# ---------------------------------------------------------------------------
# ROM builders
# ---------------------------------------------------------------------------

CTRL_ROM_SIZE = 128   # 2^7
STATE_ROM_SIZE = 2048  # 2^11

CTRL_COLUMNS = [
    'srcPC', 'loadPC', 'loadSP', 'loadMAR', 'loadMDR', 'loadIR',
    'weReg', 'memRead', 'memWrite', 'PC_out', 'MDR_out', 'ALU_out', 'Imm_out',
]


def build_control_rom(path):
    words = [0] * CTRL_ROM_SIZE
    with open(path, newline='') as f:
        reader = csv.DictReader(f)
        for lineno, row in enumerate(reader, start=2):
            state_raw = row.get('state', '').strip()
            if not state_raw or state_raw.startswith('#'):
                continue

            state = parse_state(state_raw)
            opcodes = parse_opcodes(row.get('opcode', '*'))

            srcPC    = parse_2bit(row.get('srcPC',    0))
            loadPC   = parse_bit(row.get('loadPC',   0))
            loadSP   = parse_bit(row.get('loadSP',   0))
            loadMAR  = parse_bit(row.get('loadMAR',  0))
            loadMDR  = parse_bit(row.get('loadMDR',  0))
            loadIR   = parse_bit(row.get('loadIR',   0))
            weReg    = parse_bit(row.get('weReg',    0))
            memRead  = parse_bit(row.get('memRead',  0))
            memWrite = parse_bit(row.get('memWrite', 0))
            PC_out   = parse_bit(row.get('PC_out',   0))
            MDR_out  = parse_bit(row.get('MDR_out',  0))
            ALU_out  = parse_bit(row.get('ALU_out',  0))
            Imm_out  = parse_bit(row.get('Imm_out',  0))

            ctrl = (
                (srcPC    << 12) |
                (loadPC   << 11) |
                (loadSP   << 10) |
                (loadMAR  <<  9) |
                (loadMDR  <<  8) |
                (loadIR   <<  7) |
                (weReg    <<  6) |
                (memRead  <<  5) |
                (memWrite <<  4) |
                (PC_out   <<  3) |
                (MDR_out  <<  2) |
                (ALU_out  <<  1) |
                (Imm_out  <<  0)
            )

            for op in opcodes:
                addr = (state << 4) | op
                words[addr] = ctrl

    return words


def build_state_rom(path):
    words = [0] * STATE_ROM_SIZE
    with open(path, newline='') as f:
        reader = csv.DictReader(f)
        for lineno, row in enumerate(reader, start=2):
            cur_raw = row.get('currentState', '').strip()
            if not cur_raw or cur_raw.startswith('#'):
                continue

            cur_state  = parse_state(cur_raw)
            opcodes    = parse_opcodes(row.get('opcode', '*'))
            flags_list = parse_flags(row.get('flags', '*'))
            next_state = parse_state(row.get('nextState', '0'))

            for op in opcodes:
                for fl in flags_list:
                    addr = (cur_state << 8) | (op << 4) | fl
                    words[addr] = next_state

    return words

# ---------------------------------------------------------------------------
# Output formatters (Logisim-Evolution)
# ---------------------------------------------------------------------------

def fmt_v3_hex(words, words_per_line=16):
    """v3.0 hex words plain — 4-hex-digit words."""
    lines = ['v3.0 hex words plain']
    for i in range(0, len(words), words_per_line):
        lines.append(' '.join(f'{w:04x}' for w in words[i:i + words_per_line]))
    return '\n'.join(lines) + '\n'


def fmt_v2_raw(words, words_per_line=16):
    """v2.0 raw — space-separated hex bytes."""
    lines = ['v2.0 raw']
    for i in range(0, len(words), words_per_line):
        lines.append(' '.join(f'{w:02x}' for w in words[i:i + words_per_line]))
    return '\n'.join(lines) + '\n'

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    base = os.path.dirname(os.path.abspath(__file__))
    mc_dir = os.path.join(base, 'microcodes')
    os.makedirs(mc_dir, exist_ok=True)

    signals_csv = os.path.join(mc_dir, 'signals.csv')
    fsm_csv     = os.path.join(mc_dir, 'fsm.csv')
    signals_hex = os.path.join(mc_dir, 'signals.hex')
    fsm_hex     = os.path.join(mc_dir, 'fsm.hex')

    ok = True

    if os.path.exists(signals_csv):
        ctrl_words = build_control_rom(signals_csv)
        with open(signals_hex, 'w') as f:
            f.write(fmt_v3_hex(ctrl_words, words_per_line=16))
        nonzero = sum(1 for w in ctrl_words if w)
        print(f'[signals] written {signals_hex}  ({CTRL_ROM_SIZE} entries, {nonzero} non-zero)')
    else:
        print(f'[signals] {signals_csv} not found — skipped', file=sys.stderr)
        ok = False

    if os.path.exists(fsm_csv):
        state_words = build_state_rom(fsm_csv)
        with open(fsm_hex, 'w') as f:
            f.write(fmt_v2_raw(state_words, words_per_line=16))
        nonzero = sum(1 for w in state_words if w)
        print(f'[fsm]     written {fsm_hex}  ({STATE_ROM_SIZE} entries, {nonzero} non-zero)')
    else:
        print(f'[fsm]     {fsm_csv} not found — skipped', file=sys.stderr)
        ok = False

    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
