; demo.asm — exercises register operations and RAM read/write
; RAM: 64K x 16-bit  (addresses 0x0000–0xFFFF)
; Data area: 0x0100–0x0105

; ── Phase 1: load constants into registers ──────────────────────────────────
        LI    R1, #10          ; R1 = 10
        LI    R2, #20          ; R2 = 20
        LI    R3, #3           ; R3 = 3  (used as shift count / divisor)

; ── Phase 2: arithmetic operations ──────────────────────────────────────────
        ALU   R4, R1, R2, ADD  ; R4 = R1 + R2 = 30
        ALU   R5, R2, R1, SUB  ; R5 = R2 - R1 = 10
        ALU   R6, R1, R2, MUL  ; R6 = R1 * R2 = 200  (low 16 bits)
        ALU   R7, R2, R1, DIV  ; R7 = R2 / R1 = 2

; ── Phase 3: bitwise and shift operations ────────────────────────────────────
        ALU   R4, R1, R2, OR   ; R4 = R1 | R2 = 30
        ALU   R5, R1, R2, AND  ; R5 = R1 & R2 = 0
        ALU   R6, R2, R3, SHL  ; R6 = R2 << 3 = 160
        ALU   R7, R2, R3, SHR  ; R7 = R2 >> 3 = 2

; ── Phase 4: store results to RAM ───────────────────────────────────────────
        LI    R1, #10          ; restore R1 = 10
        LI    R2, #20          ; restore R2 = 20
        ALU   R4, R1, R2, ADD  ; R4 = 30
        ALU   R5, R2, R1, SUB  ; R5 = 10
        ALU   R6, R1, R2, MUL  ; R6 = 200
        STORE R4, #0x100       ; MEM[0x100] = 30
        STORE R5, #0x101       ; MEM[0x101] = 10
        STORE R6, #0x102       ; MEM[0x102] = 200

; ── Phase 5: read back from RAM ─────────────────────────────────────────────
        LOAD  R1, #0x100       ; R1 = MEM[0x100] = 30
        LOAD  R2, #0x101       ; R2 = MEM[0x101] = 10
        LOAD  R3, #0x102       ; R3 = MEM[0x102] = 200

; ── Phase 6: operate on RAM values ──────────────────────────────────────────
        ALU   R4, R1, R2, ADD  ; R4 = 30 + 10 = 40
        ALU   R5, R1, R2, SUB  ; R5 = 30 - 10 = 20
        ALU   R6, R2, R3, ADD  ; R6 = 10 + 200 = 210
        STORE R4, #0x103       ; MEM[0x103] = 40
        STORE R5, #0x104       ; MEM[0x104] = 20
        STORE R6, #0x105       ; MEM[0x105] = 210

; ── Phase 7: conditional branch demo (count down R1 to 0) ───────────────────
        LI    R1, #5           ; loop counter
        LI    R2, #1           ; decrement step
loop:
        ALU   R1, R1, R2, SUB ; R1 = R1 - 1
        BNE   loop             ; if R1 != 0 (Z=0), branch back

; ── Phase 8: stack operations ────────────────────────────────────────────────
        LI    R1, #65          ; 'A'
        LI    R2, #66          ; 'B'
        PUSH  R1               ; stack: [A]
        PUSH  R2               ; stack: [A, B]
        POP   R3               ; R3 = B, stack: [A]
        POP   R4               ; R4 = A, stack: []

        HALT
