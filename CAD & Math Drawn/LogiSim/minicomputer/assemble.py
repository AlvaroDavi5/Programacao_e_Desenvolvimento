#!/usr/bin/env python3
"""
assemble.py — single-pass assembler for the 16-bit minicomputer ISA.

Usage:
    python3 assemble.py <source.asm>            # writes <source.hex>
    python3 assemble.py <source.asm> -o out.hex

Instruction formats
    Format R : OPCODE(4) | RD(3) | RS1(3) | RS2(3) | ALUCODE(3)
    Format I : OPCODE(4) | RD(3) | IMM9(9)   signed 9-bit immediate

Assembly syntax (case-insensitive, ';' starts a comment):
    LABEL:
    LI    Rx, #imm              ; Rx ← sign_extend(imm9)
    ALU   Rd, Rs1, Rs2 [,OP]   ; Rd ← Rs1 OP Rs2  (OP default ADD)
    MOV   Rd, Rs1               ; Rd ← Rs1
    LOAD  Rd, Rs1               ; Rd ← MEM[Rs1]       (Format R)
    LOAD  Rd, #addr             ; Rd ← MEM[addr]       (Format I)
    STORE Rs1, Rs2              ; MEM[Rs2] ← Rs1       (Format R)
    STORE Rs1, #addr            ; MEM[addr] ← Rs1      (Format I)
    PUSH  Rs1                   ; MEM[SP] ← Rs1; SP--
    POP   Rd                    ; SP++; Rd ← MEM[SP]
    JMP   #addr                 ; PC ← addr            (absolute)
    BEQ   #offset               ; if Z=1: PC ← PC+offset
    BNE   #offset               ; if Z=0: PC ← PC+offset
    BLT   #offset               ; if N=1: PC ← PC+offset
    BGE   #offset               ; if N=0: PC ← PC+offset
    BMI   #offset               ; if N=1: PC ← PC+offset (alias BLT)
    BPL   #offset               ; if N=0: PC ← PC+offset (alias BGE)
    NOOP                        ; no operation
    HALT                        ; freeze CPU

Registers  : R0–R7  (R0 always reads as 0)
Immediates : decimal (42), hex (0x2A), binary (0b101010), char ('A')
             Negative: -1, -0x10
"""

import re
import sys
import os

# ---------------------------------------------------------------------------
# Encoding tables
# ---------------------------------------------------------------------------

OPCODES = {
    'noop': 0x0, 'alu': 0x1, 'li': 0x2,  'mov': 0x3,
    'load': 0x4, 'store': 0x5, 'push': 0x6, 'pop': 0x7,
    'jmp':  0x8, 'beq':  0x9, 'bne':  0xA, 'blt': 0xB,
    'bge':  0xC, 'bmi':  0xD, 'bpl':  0xE, 'halt': 0xF,
}

ALU_OPS = {
    'add': 0, 'sub': 1, 'mul': 2, 'div': 3,
    'or':  4, 'and': 5, 'shr': 6, 'shl': 7,
}

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def parse_reg(tok):
    tok = tok.strip().lower()
    if not tok.startswith('r'):
        raise ValueError(f'expected register, got {tok!r}')
    n = int(tok[1:])
    if n < 0 or n > 7:
        raise ValueError(f'register out of range: {tok!r}')
    return n


def parse_imm(tok, bits, signed=True):
    tok = tok.strip()
    if tok.startswith('#'):
        tok = tok[1:]
    # character literal
    if len(tok) == 3 and tok[0] == "'" and tok[2] == "'":
        val = ord(tok[1])
    elif tok.startswith('0x') or tok.startswith('0X'):
        val = int(tok, 16)
    elif tok.startswith('0b') or tok.startswith('0B'):
        val = int(tok, 2)
    elif tok.startswith('-0x') or tok.startswith('-0X'):
        val = -int(tok[1:], 16)
    else:
        val = int(tok, 10)

    lo = -(1 << (bits - 1)) if signed else 0
    hi = (1 << (bits - 1)) - 1 if signed else (1 << bits) - 1
    if val < lo or val > hi:
        raise ValueError(f'immediate {val} out of {bits}-bit range [{lo}, {hi}]')
    return val & ((1 << bits) - 1)


def encode_r(opcode, rd, rs1, rs2, alucode=0):
    return (opcode << 12) | (rd << 9) | (rs1 << 6) | (rs2 << 3) | alucode


def encode_i(opcode, rd, imm9):
    return (opcode << 12) | (rd << 9) | (imm9 & 0x1FF)

# ---------------------------------------------------------------------------
# Assembler
# ---------------------------------------------------------------------------

def assemble(source_text):
    """Return list of (address, word) and symbol table."""
    lines = source_text.splitlines()
    words = {}       # addr → 16-bit word
    labels = {}      # name → address
    fixups = []      # (addr, label, is_relative, line_no)
    addr = 0

    def split_args(s):
        return [a.strip() for a in s.split(',') if a.strip()]

    for lineno, raw in enumerate(lines, 1):
        line = raw.split(';')[0].strip()
        if not line:
            continue

        # label
        if line.endswith(':'):
            labels[line[:-1].lower()] = addr
            continue
        if ':' in line.split()[0]:
            label, rest = line.split(':', 1)
            labels[label.strip().lower()] = addr
            line = rest.strip()
            if not line:
                continue

        tokens = re.split(r'[\s,]+', line)
        mnemonic = tokens[0].lower()
        args = [t for t in tokens[1:] if t]

        try:
            word = assemble_instruction(mnemonic, args, addr, labels, fixups, lineno)
        except Exception as e:
            raise SyntaxError(f'line {lineno}: {e}\n  {raw.strip()}') from None

        words[addr] = word
        addr += 1

    # resolve forward-reference fixups
    for fix_addr, label, is_relative, orig_addr, lineno in fixups:
        if label not in labels:
            raise SyntaxError(f'line {lineno}: undefined label {label!r}')
        target = labels[label]
        w = words[fix_addr]
        opcode = (w >> 12) & 0xF
        rd     = (w >> 9) & 0x7
        if is_relative:
            offset = target - (orig_addr + 1)  # relative to next instruction
            imm9 = offset & 0x1FF
        else:
            imm9 = target & 0x1FF
        words[fix_addr] = encode_i(opcode, rd, imm9)

    return words, labels


def assemble_instruction(mnemonic, args, addr, labels, fixups, lineno):
    op = OPCODES.get(mnemonic)
    if op is None:
        raise ValueError(f'unknown mnemonic {mnemonic!r}')

    def label_or_imm(tok, bits, signed, relative, orig_addr):
        tok = tok.strip()
        ref = tok.lstrip('#').lower()
        if ref in labels:
            target = labels[ref]
            if relative:
                val = target - (orig_addr + 1)
            else:
                val = target
            lo = -(1 << (bits - 1)) if signed else 0
            hi = (1 << (bits - 1)) - 1 if signed else (1 << bits) - 1
            if val < lo or val > hi:
                raise ValueError(f'branch target {val} out of range')
            return val & ((1 << bits) - 1), False
        # unknown label → fixup
        if not tok.startswith('#') and not tok[0].isdigit() and not tok[0] in "-+'":
            fixups.append((addr, ref, relative, orig_addr, lineno))
            return 0, True
        return parse_imm(tok, bits, signed), False

    if mnemonic == 'noop':
        return encode_i(op, 0, 0)

    if mnemonic == 'halt':
        return encode_i(op, 0, 0)

    if mnemonic == 'li':
        rd  = parse_reg(args[0])
        imm = parse_imm(args[1], 9, signed=True)
        return encode_i(op, rd, imm)

    if mnemonic == 'alu':
        rd  = parse_reg(args[0])
        rs1 = parse_reg(args[1])
        rs2 = parse_reg(args[2])
        alu = ALU_OPS.get(args[3].lower() if len(args) > 3 else 'add', 0)
        return encode_r(op, rd, rs1, rs2, alu)

    if mnemonic == 'mov':
        rd  = parse_reg(args[0])
        rs1 = parse_reg(args[1])
        return encode_r(op, rd, rs1, 0, ALU_OPS['add'])

    if mnemonic == 'load':
        rd = parse_reg(args[0])
        if args[1].startswith('#') or (args[1].lstrip('#')[0:2] not in ('r0','r1','r2','r3','r4','r5','r6','r7') and not args[1].lower().startswith('r')):
            imm, _ = label_or_imm(args[1], 9, signed=False, relative=False, orig_addr=addr)
            return encode_i(op, rd, imm)
        rs1 = parse_reg(args[1])
        return encode_r(op, rd, rs1, 0, 0)

    if mnemonic == 'store':
        rs1 = parse_reg(args[0])
        if args[1].startswith('#') or not args[1].lower().startswith('r'):
            imm, _ = label_or_imm(args[1], 9, signed=False, relative=False, orig_addr=addr)
            return encode_i(op, rs1, imm)
        rs2 = parse_reg(args[1])
        return encode_r(op, rs1, 0, rs2, 0)

    if mnemonic == 'push':
        rs1 = parse_reg(args[0])
        return encode_r(op, 0, rs1, 0, 0)

    if mnemonic == 'pop':
        rd = parse_reg(args[0])
        return encode_r(op, rd, 0, 0, 0)

    if mnemonic == 'jmp':
        imm, _ = label_or_imm(args[0], 9, signed=False, relative=False, orig_addr=addr)
        return encode_i(op, 0, imm)

    if mnemonic in ('beq', 'bne', 'blt', 'bge', 'bmi', 'bpl'):
        imm, _ = label_or_imm(args[0], 9, signed=True, relative=True, orig_addr=addr)
        return encode_i(op, 0, imm)

    raise ValueError(f'unhandled mnemonic {mnemonic!r}')

# ---------------------------------------------------------------------------
# Output formatter
# ---------------------------------------------------------------------------

def fmt_hex(words, total=None):
    if total is None:
        total = max(words.keys()) + 1 if words else 0
        # round up to next multiple of 16
        total = ((total + 15) // 16) * 16
    flat = [words.get(i, 0) for i in range(total)]
    lines = ['v3.0 hex words plain']
    for i in range(0, len(flat), 16):
        lines.append(' '.join(f'{w:04x}' for w in flat[i:i+16]))
    return '\n'.join(lines) + '\n'

# ---------------------------------------------------------------------------
# Disassembler (for listing)
# ---------------------------------------------------------------------------

def disassemble(word):
    op      = (word >> 12) & 0xF
    rd      = (word >> 9)  & 0x7
    rs1     = (word >> 6)  & 0x7
    rs2     = (word >> 3)  & 0x7
    alucode = word & 0x7
    imm9_u  = word & 0x1FF
    imm9_s  = imm9_u if imm9_u < 256 else imm9_u - 512

    mn = {v: k.upper() for k, v in OPCODES.items()}[op]
    alu_mn = {v: k.upper() for k, v in ALU_OPS.items()}

    if mn == 'NOOP':  return 'NOOP'
    if mn == 'HALT':  return 'HALT'
    if mn == 'ALU':   return f'ALU   R{rd}, R{rs1}, R{rs2}, {alu_mn[alucode]}'
    if mn == 'LI':    return f'LI    R{rd}, #{imm9_s}'
    if mn == 'MOV':   return f'MOV   R{rd}, R{rs1}'
    if mn == 'LOAD':
        if imm9_u != 0 or rs1 == 0:
            return f'LOAD  R{rd}, #{imm9_u:#05x}'
        return f'LOAD  R{rd}, R{rs1}'
    if mn == 'STORE':
        if rs1 == 0 and imm9_u == 0:
            return f'STORE R{rd}, #{imm9_u:#05x}'
        return f'STORE R{rd}, #{imm9_u:#05x}'
    if mn in ('PUSH',):  return f'PUSH  R{rs1}'
    if mn in ('POP',):   return f'POP   R{rd}'
    if mn == 'JMP':   return f'JMP   #{imm9_u:#05x}'
    if mn in ('BEQ','BNE','BLT','BGE','BMI','BPL'):
        return f'{mn:<5} #{imm9_s:+d}'
    return f'{mn} 0x{word:04x}'

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    import argparse
    ap = argparse.ArgumentParser(description='Assembler for 16-bit minicomputer')
    ap.add_argument('source', help='assembly source file (.asm)')
    ap.add_argument('-o', '--output', help='output hex file (default: <source>.hex)')
    ap.add_argument('-l', '--listing', action='store_true', help='print listing to stdout')
    args = ap.parse_args()

    src_path = args.source
    out_path = args.output or os.path.splitext(src_path)[0] + '.hex'

    with open(src_path) as f:
        source = f.read()

    words, labels = assemble(source)

    with open(out_path, 'w') as f:
        f.write(fmt_hex(words))

    rev_labels = {v: k for k, v in labels.items()}

    if args.listing or True:
        print(f'Assembled {len(words)} word(s) → {out_path}')
        print()
        print(f'{"Addr":>4}  {"Word":>4}  Instruction')
        print('-' * 40)
        for a in sorted(words):
            label = f'{rev_labels[a]}:' if a in rev_labels else ''
            print(f'{a:04x}  {words[a]:04x}  {label:<10} {disassemble(words[a])}')
        if labels:
            print()
            print('Labels:')
            for name, addr in sorted(labels.items(), key=lambda x: x[1]):
                print(f'  {name:<16} = 0x{addr:04x}')


if __name__ == '__main__':
    main()
