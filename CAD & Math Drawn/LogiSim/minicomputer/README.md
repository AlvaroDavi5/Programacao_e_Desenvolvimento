# Overview


## States

- Reset: restart the FSM
- Fetch1: search next instruction on memory by address
- Fetch2: read instruction data on memory
- Fetch3: store instruction and increment next instruction
- Decode: decode stored instruction
- Execute: execute stored instruction
- Memory: read or write data on memory
- WriteBack: store the result on a register

