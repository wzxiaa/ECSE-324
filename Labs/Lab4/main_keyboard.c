#include <stdio.h>

#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/vga.h"
#include "./drivers/inc/ps2_keyboard.h"

int main(){
	int x = 0;
	int y = 0;
	//clear the character buffer first
	VGA_clear_charbuff_ASM();
	while(1){
		char user;
		//read character from user from the keyboard
		if(read_PS2_data_ASM(&user)){
			VGA_write_byte_ASM(x,y,user);
			//skips three columns
			x+=3;
			//80x60
			if(x>=80) {
				//reach the end of the row, enter to a new row
				x=0; 
				y++;
				//reach the end of the screen, reset to (0,0)
				if(y>=60){
					//clear the character buffer
					VGA_clear_charbuff_ASM();
					x = 0;
					y = 0;
				}
			}
		}
	}
	return 0;
}
