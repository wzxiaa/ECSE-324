
			.text
			.global audio
			.equ FIFO_SPACE, 0xFF203044 
			.equ LEFTDATA, 0xFF203048
			.equ RIGHTDATA, 0xFF20304C

audio:




			LDR R1, =FIFO_SPACE
			LDR R2, [R1]
			
			AND R4, R2, #0xFF000000	//Extract for WSLC
			AND R5, R2, #0x00FF0000	//Extract for WSRC
			LSR R4, R4, #6		
			LSR R5, R5, #4

			CMP R4, #1
			BLT EXIT
			CMP R5, #1
			BLT EXIT

			LDR R6, =LEFTDATA
			LDR R7, =RIGHTDATA
			STR R0,[R6]
			STR R0,[R7]
			MOV R0, #1
			BX LR

EXIT:		
			MOV R0, #0
			BX LR

			.end
