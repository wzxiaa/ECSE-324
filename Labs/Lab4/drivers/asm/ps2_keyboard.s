				.text
				.global read_PS2_data_ASM
				.equ PS2_DATA, 0xFF200100

read_PS2_data_ASM:
				LDR R3, =PS2_DATA
				LDR R3, [R3]
				//TST R3, #65536
				TST R3, #32768 //?
				//LSR R4, R3, #16
				//TST R4, #1
				BNE STORE_ARG
				MOV R0, #0
				BX LR
STORE_ARG:		STRB R3, [R0]
				MOV R0, #1
				BX LR		
				
				.end
