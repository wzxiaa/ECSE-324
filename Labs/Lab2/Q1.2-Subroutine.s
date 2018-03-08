.text
				.global	_star

_star:
				LDR R4, =RESULT		//R4 points to result location
				LDR R2, [R4, #4]	//R2 has the number of elements in the list (loop counter)
				ADD R3, R4,	#8		//R3 points to the first number
				LDR R0, [R3]		//R0 has the value of the first element
				BL  LOOP			//'LOOP' and store the address of next instruction in LR, that is the return address

LOOP:
				SUBS R2, R2, #1		//decrement the loop counter
				BEQ DONE			//end loop is condition flag is 0 meaning counter is 0
				ADD R3, R3, #4		//R3 points to next element in the list
				LDR R1, [R3]		//R1 holds the next element in the list
				CMP R0, R1			//check if current value greater than max
				BGE LOOP			//if no, go back
				MOV R0, R1			//if yes, update value
				BX  LR				//return

DONE:		
				STR R0, [R4]		//store the result in the memory location

END:			B END


RESULT:			.word 0
N:				.word 7
NUMBERS:		.word 4, 11, 3, 6
				.word 1, 8, 2
