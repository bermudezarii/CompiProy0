.data
.balign 4
BB:
    .word 0
.balign 4
A:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_BB
  MOV r3, #300
  STR r3, [r1] 

  LDR r1, addr_of_A
  MOV r3, #200
  STR r3, [r1] 

BX lr

addr_of_BB: .word BB
addr_of_A: .word A
.data
.balign 4
BB:
    .word 0
.balign 4
A:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_BB
  MOV r3, #300
  STR r3, [r1] 

  LDR r1, addr_of_A
  MOV r3, #200
  STR r3, [r1] 

  BX lr 

addr_of_BB: .word BB
addr_of_A: .word A
.data
.balign 4
A:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
.data
.balign 4
A:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
.data
.balign 4
A:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
.data
.balign 4
A:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
.data
.global _start
 _start: 
  BX lr 

.data
.global _start
 _start: 
  BX lr 

.data
.global _start
 _start: 
  BX lr 

.data
.balign 4
A:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_C
  ADR r3, 
  STR r3, [r1] 

  BX lr 

addr_of_A: .word A
addr_of_C: .word C
.data
.global _start
 _start: 
  BX lr 

.data
.balign 4
A:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_C
  ADR r3, 
  STR r3, [r1] 

  BX lr 

addr_of_A: .word A
addr_of_C: .word C
.data
.balign 4
A:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_C
  ADR r3, 
  STR r3, [r1] 

  BX lr 

addr_of_A: .word A
addr_of_C: .word C
.data
.balign 4
A:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  LDR r1, addr_of_C
  ADR r3, 
  STR r3, [r1] 

  BX lr 

addr_of_A: .word A
addr_of_C: .word C
.data
.balign 4
A:
    .word 0
.balign 4
B:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
addr_of_B: .word B
.data
.balign 4
A:
    .word 0
.balign 4
B:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
addr_of_B: .word B
.data
.balign 4
A:
    .word 0
.balign 4
B:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
addr_of_B: .word B
.data
.balign 4
A:
    .word 0
.balign 4
B:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  BX lr 

addr_of_A: .word A
addr_of_B: .word B
addr_of_C: .word C
.data
.balign 4
A:
    .word 0
.balign 4
D:
    .word 0
.balign 4
Temp&1:
    .word 0
.balign 4
B:
    .word 0
.balign 4
C:
    .word 0
.global _start
 _start: 
  LDR R4, addr_of_A
  LDR R4, [R4]
  LDR R5, addr_of_D
  LDR R5, [R5]
  ADD R4, R4,R5

  LDR r1, addr_of_Temp&1
  STR r4, [r1] 

  BX lr 

addr_of_A: .word A
addr_of_D: .word D
addr_of_Temp&1: .word Temp&1
addr_of_B: .word B
addr_of_C: .word C
