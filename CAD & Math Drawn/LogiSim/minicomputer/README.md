# Overview

16-bit computer with datapath, control unit, RAM memory, register file, and ALU.

This project does not represent a real computer with a complex architecture and
internal bus. It is intended for academic purposes only.

[Full ISA and microcode documentation](./ISA_AND_MICROCODE.md).

## Processor States (with codes)

- Reset: restart the FSM
- Fetch1: search next instruction on memory by address
- Fetch2: read instruction data on memory
- Fetch3: store instruction and increment next instruction
- Decode: decode stored instruction
- Execute: execute stored instruction
- Memory: read or write data on memory
- WriteBack: store the result on a register

|   State      | FSM Code |           Description                            |
|--------------|----------|--------------------------------------------------|
|   Reset      |    000   | Restart the FSM                                  |
|   Fetch1     |    001   | Search next instruction on memory by address     |
|   Fetch2     |    010   | Read instruction data on memory                  |
|   Fetch3     |    011   | Store instruction and increment next instruction |
|   Decode     |    100   | Decode stored instruction                        |
|   Execute    |    101   | Execute stored instruction                       |
|   Memory     |    110   | Read or write data on memory                     |
|   WriteBack  |    111   | Store the result on a register                   |

## Instruction Formats

**Format R:** `Opcode(4) | RD(3) | RS1(3) | RS2(3) | ALUCODE(3)`

**Format I:** `Opcode(4) | RD(3) | Immediate(9)`

## ALU Operations (ALUCODE)

| Code | Operation |
|------|-----------|
| 000  | ADD       |
| 001  | SUB       |
| 010  | MUL       |
| 011  | DIV       |
| 100  | OR        |
| 101  | AND       |
| 110  | SHR       |
| 111  | SHL       |

## Opcodes (summary)

| Code | Instruction |
|------|-------------|
| 0000 | NOOP        |
| 0001 | ALU         |
| 0010 | LI          |
| 0011 | MOV         |
| 0100 | LOAD        |
| 0101 | STORE       |
| 0110 | PUSH        |
| 0111 | POP         |
| 1000 | JMP         |
| 1001 | BEQ         |
| 1010 | BNE         |
| 1011 | BLT         |
| 1100 | BGE         |
| 1101 | BMI         |
| 1110 | BPL         |
| 1111 | HALT        |

For complete instruction semantics, control-signal bit maps,
per-instruction micro-sequences, and `stateROM` / `controlROM` tables,
see [ISA_AND_MICROCODE.md](./ISA_AND_MICROCODE.md).
