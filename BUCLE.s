.data
X: .word 0,1,2,3,4,5
A: .word 10
Xtop: .word 5
Xpointer: .word 4

k: .word 1

.text

start:

	LW R1,A ; R1=A
	LW R2,Xtop ;R2 = stop = 5
	LW R3,Xpointer ; R3 = 4
	LW R4,k ; R4 = 1

	ADD R5,R0,R0 
	ADD R6,R0,R0 ; R6 = R0 + R0

loop:	LW R6, X(R5)	;R6=X[0]=0
	ADD R6,R1,R6
	SW X(R5), R6	;X[0]<-R6

	ADD R5,R5,R3
	SUB R2,R2,R4
	BNEZ R2,loop
	NOP
trap 6
