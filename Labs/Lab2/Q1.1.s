					.text
					.global _s

_s: 	
					LDR R2, =N				//R2 POINTS TO THE NUMBER OF ELEMENTS IN THE LIST
					LDR R2, [R2]			//R2 HAS THE VALUE OF NUMBER OF ELEMENTS IN THE LIST
					LDR R3, =NUMBERS		//R3 POINTS TO THE FIRST ELEMENT IN THE LIST
					
LOOP:				LDR R4, [R3]			//R4 HAS THE VALUE OF THE FIRST ELEMENT IN THE LIST
					STR R4, [SP, #4]!		//PUSH VALUE FROM R4 TO THE TOP OF THE STACK
					ADD R3, R3, #4			//R3 POINTS TO THE NEXT ELEMENT IN THE LIST
					SUB R2, R2, #1			//DECREMENT THE LOOP COUNTER
					CMP R2, #0			
					BEQ CONTINUE			//BRANCH OUT IF LOOP COUNTER IS 0
					B LOOP					//ELSE GO BACK TO THE LOOP
					
CONTINUE:			LDMDA SP!, {R5-R9}		//POP TOP 5 VALUES OF THE STACK TO R5, R6, R7, R8, R9
END:				B END

N:					.word 5
NUMBERS:			.word 9, 3, 8, 5, 6

