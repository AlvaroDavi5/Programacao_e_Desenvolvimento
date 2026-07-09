# Overview

16 bits computer with datapath, control unity, RAM memory, registers database and ALU.

This project don't represent a real computer with complex architecture and
internal bus. This project is only for academic purposes.

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

### Translation to Instructions to Microinstructions

...

