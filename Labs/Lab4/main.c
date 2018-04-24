#include <stdio.h>

#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/vga.h"
#include "./drivers/inc/ps2_keyboard.h"


void test_char();
void test_byte();
void test_pixel();

 int main() {

	while(1) {
		//check if PB0 is pressed 										
		if(PB_data_is_pressed_ASM(PB0)){
			if (read_slider_switches_ASM() != 0) {
				//If slider is HIGH, we test byte
				//test_byte() calls VGA_write_byte_ASM()
				//which writes HEX_ASCII
				test_byte(); 
			}
			else {
				//If none of the sliders are LOW
				//simply spit out ASCII table
				test_char();
			}
		}
		//Check if PB1 is pressed
		if(PB_data_is_pressed_ASM(PB1)){
			//call test_pixel();
			//test_pixel() tests VGA_draw_point_ASM()
			test_pixel();
		}
		//Check if PB2 is pressed
		if(PB_data_is_pressed_ASM(PB2)){
			//clear character buffer
			VGA_clear_charbuff_ASM();

		}
		if(PB_data_is_pressed_ASM(PB3)){
			//clear pixel buffer
			VGA_clear_pixelbuff_ASM(); 
		}	
	}
	return 0;
}

void test_char(){
	int x,y;
	char c = 70;
	
	for(y=0;y<=59;y++){
		for(x=0;x<=79;x++){
			VGA_write_char_ASM(x,y,c++);
		}
	}
}

void test_byte(){
	int x,y;
	char c =0;
	for(y=0;y<=59;y++){
		for(x=0;x<=79;x+=3){
			VGA_write_byte_ASM(x,y,c++);
		}
	}
}

void test_pixel(){
	int x,y;
	unsigned short colour = 0;
	
	for(y=0;y<=239;y++)
		for(x=0;x<=319;x++)
			VGA_draw_point_ASM(x,y,colour++);
}
