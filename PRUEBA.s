.data 0
A: .float 2
B: .float 8
C: .float 0

.text
main:
LF F1,A		;LW R1,A -> CARGA PALABRA EN EL REGISTRO 1
		;EL REGISTRO 0 NO SE PUEDE USAR
LF F2,B

ADDF F3,F2,F1
SF C,F3
		;
trap 6		;"interrupción" para terminar programa
