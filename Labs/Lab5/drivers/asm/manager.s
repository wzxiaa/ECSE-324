			.text
			.global remove_note_asm
			.global add_note_asm
			.global print_wave_asm
			.global note_to_freq_asm

add_note_asm:
			ORR R0, R0, R1
			BX LR

//R0 will be original note
//R1 will hold note to be removed (should only be 1 at a time)
remove_note_asm:
			MOV R3, #-1
			EOR R1, R1, R3		//flip the bits
			AND R0, R0, R1
			BX LR

//converts a note to a frequency
note_to_freq_asm:
			//R0 takes initial note
			//R1 points to array
			PUSH {LR}
			MOV R2, #0		//R2 is counter

			CMP R0, #0x01 		//If initial note is C
			BEQ ntf_valid
			ADD R2, R2, #1		//increment counter

			CMP R0, #0x02 		//D
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x04		//E
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x08		//F
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x10		//G
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x20		//A
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x40		//B
			BEQ ntf_valid
			ADD R2, R2, #1

			CMP R0, #0x80		//c
			BEQ ntf_valid

			MOV R0, #0x0		//R0 is not a valid value
			B ntf_return

ntf_valid:
			MOV R3, #4
			MUL R2, R2, R3		//R2 to count in words, 4 bytes
			ADD R1, R1, R2 		//R1 points to spot in array based on R2s size
			LDR R0, [R1]

ntf_return:
			PUSH {LR}
			BX LR

//VGA_draw_point_ASM
//R0 = x
//R1 = y
//R2 = colour
print_wave_asm:
			//R0 holds signal
			//R1 holds column
			PUSH {R4-R8, LR}
			MOV R7, #0xFF
			LSL R7, R7, #8
			ORR R7, #0xFF
			LSL R7, R7, #7		//R7 holds 0x7FF (15 high bits)
			ORR R7, #0x7F

			MOV R4, R0			//R4 holds signal
			MOV R5, R1			//R5 Holds column number
			MOV R6, #0			//R6 is a row counter

//clear the row
//write to the one lit pixel
loop:
			MOV R0, R5
			MOV R1, R6
			//clear or write
			CMP R4, R6			//if correct row
			MOVEQ R2, R7		//if equal, write
			MOVNE R2, #0		//else clear

			BL VGA_draw_point_ASM

			ADD R6, R6, #1
			CMP R6, #0xF0		//Exit when counter reachs 240
			BLT loop

			POP {R4-R8, LR}
			BX LR

.end