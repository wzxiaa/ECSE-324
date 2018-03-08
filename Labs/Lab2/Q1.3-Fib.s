				.text
				.global _start

_start:			
				MOV R0, #3			
				BL FIB					//DO FIB
				B END

FIB:			PUSH {LR}
				PUSH {R12}
				PUSH {R11}				//PUSH R11, R12 AND LR
				CMP R0, #2				//SEE IF R0 IS GREATER OR EQUAL TO 2
				BGE IF					//IF R0 IS GREATER THAN 2
				BLT ELSE				//BGE R0, #2, IF

IF:							
				MOV R12, R0				
				SUB R0, R12, #2			//Fib(n-2)
				BL FIB
				
				MOV R11, R0
				SUB R0, R12, #1			//Fib(n-1)
				BL FIB

				ADD R0, R0, R11
				B RETURN

ELSE:			MOV R0, #1
				B RETURN

RETURN:			POP {R11}
				POP {R12}
				POP {LR}
				BX LR

END: 			B END


			
