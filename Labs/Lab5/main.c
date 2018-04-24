#include <stdlib.h>

#include "./drivers/inc/vga.h"
#include "./drivers/inc/ISRs.h"
#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/audio.h"
#include "./drivers/inc/HPS_TIM.h"
#include "./drivers/inc/int_setup.h"
#include "./drivers/inc/wavetable.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/ps2_keyboard.h"
#include "./drivers/inc/HEX_displays.h"
#include "./drivers/inc/slider_switches.h"
void drawWelcome();
//base colour we start off with
short colour = 4095;
//an integer array that takes the keys that the user entered
int notesPlayed[8] = {};
//array holding the frequencies, index matched to the keys pressed
float frequencies[] = {130.813, 146.832, 164.814, 174.614, 195.998, 220.000, 246.942, 261.626};

char notes[8] = {0};

double getSample(float freq, int t) {
	double signal = 0.0;
	int index = ((int)freq*t)%48000;
	float difference  = (freq*t)-index;
	if(difference = 0){
		signal = sine[index];
	}else{
		signal = (1.0 - difference) * sine[index] + difference * sine[index + 1]; 
	}
	return signal;
}

double makeSignal(int* notePlayed, int t){
	int i;
	double sumOfSamples = 0.0;
	for(i = 0;i<8;i++){
		if(notePlayed[i] == 1){
			sumOfSamples += getSample(frequencies[i],t);
		}
	}
	return sumOfSamples;
}

// Write names at the top of the screen
void drawTitle(){
	//Screen is 79 x 59
	VGA_write_char_ASM(34, 2, 'E');
	VGA_write_char_ASM(35, 2, 'C');
	VGA_write_char_ASM(36, 2, 'S');
	VGA_write_char_ASM(37, 2, 'E');

	VGA_write_char_ASM(38, 2, ' ');

	VGA_write_char_ASM(39, 2, '3');
	VGA_write_char_ASM(40, 2, '2');
	VGA_write_char_ASM(41, 2, '4');

	VGA_write_char_ASM(42, 2, ' ');

	VGA_write_char_ASM(43, 2, 'L');
	VGA_write_char_ASM(44, 2, 'A');
	VGA_write_char_ASM(45, 2, 'B');
	VGA_write_char_ASM(46, 2, '#');
	VGA_write_char_ASM(47, 2, '5');

}

void drawAuthor(){
	VGA_write_char_ASM(34, 3, 'K');
	VGA_write_char_ASM(35, 3, 'A');
	VGA_write_char_ASM(36, 3, 'R');
	VGA_write_char_ASM(37, 3, 'L');
	VGA_write_char_ASM(38, 3, ' ');
	VGA_write_char_ASM(39, 3, '&');
	VGA_write_char_ASM(40, 3, ' ');
	VGA_write_char_ASM(41, 3, 'W');
	VGA_write_char_ASM(42, 3, 'E');
	VGA_write_char_ASM(43, 3, 'N');
	VGA_write_char_ASM(44, 3, 'Z');
	VGA_write_char_ASM(45, 3, 'O');
	VGA_write_char_ASM(46, 3, 'N');
	VGA_write_char_ASM(47, 3, 'G');
}

void drawVolume(){

	VGA_write_char_ASM(70, 59, 'V');
	VGA_write_char_ASM(71, 59, 'O');
	VGA_write_char_ASM(72, 59, 'L');
	VGA_write_char_ASM(73, 59, 'U');
	VGA_write_char_ASM(74, 59, 'M');
	VGA_write_char_ASM(75, 59, 'E');
	VGA_write_char_ASM(76, 59, ':');

}

void drawNotes(){
	VGA_write_char_ASM(1, 59, 'N');
	VGA_write_char_ASM(2, 59, 'O');
	VGA_write_char_ASM(3, 59, 'T');
	VGA_write_char_ASM(4, 59, 'E');
	VGA_write_char_ASM(5, 59, ':');
}

void drawNote(int x, char note){
	VGA_write_char_ASM(x, 59, note);
}

int x;
int main() {
	VGA_clear_charbuff_ASM();
	drawTitle();
	drawVolume();
	drawAuthor();
	drawNotes();

	VGA_clear_pixelbuff_ASM();
	int_setup(1, (int []){199});
	HPS_TIM_config_t hps_tim;
	hps_tim.tim = TIM0;
	hps_tim.timeout = 20; //1/48000 = 20.8
	hps_tim.LD_en = 1;
	hps_tim.INT_en = 1;
	hps_tim.enable = 1;

	HPS_TIM_config_ASM(&hps_tim);
		
	char keyPressed = 1;
	// counter for signal
	int t = 0;
	// to store the previous set of drawn points for quicker clearing
	double history[320] = { 0 };
	//double valToDraw = 0;
	char value;
	//charater note to be displayed in the screen: 
	char note;	
	char amplitude = 1;
	double signalSum = 0.0;
	while(1) {
			if(read_slider_switches_ASM()!=0){
				//we check keys
				if(read_ps2_data_ASM(&value)){
					switch(value){
						case 0x1C:
						if(keyPressed == 1){
							notesPlayed[0] = 1;
							colour += 30;
							notes[0] = 'C';
							//
							drawNote(6, 'C');
							//keyPressed = 0;
						}else{
							notesPlayed[0] = 0;
							keyPressed = 1;
							notes[0] = ' ';
						}break;
						case 0x1B:
						if(keyPressed == 1){
							notesPlayed[1] = 1;
							colour += 30;
							notes[1] = 'D';
							//keyPressed = 0;
						}else{
							notesPlayed[1] = 0;
							keyPressed = 1;
							notes[1] = ' ';
						}break;
						case 0x23:
						if(keyPressed == 1){
							notesPlayed[2] = 1;
							colour += 30;
							notes[2] = 'E';
							//keyPressed = 0;
						}else{
							notesPlayed[2] = 0;
							keyPressed = 1;
							notes[2] = ' ';
						}break;
						case 0x2B:
						if(keyPressed == 1){
							notesPlayed[3] = 1;
							colour += 30;
							notes[3] = 'F';
							//keyPressed = 0;
						}else{
							notesPlayed[3] = 0;
							keyPressed = 1;
							notes[3] = ' ';
						}break;
						case 0x3B:
						if(keyPressed == 1){
							notesPlayed[4] = 1;
							colour += 30;
							notes[4] = 'G';
							//keyPressed = 0;
						}else{
							notesPlayed[4] = 0;
							keyPressed = 1;
							notes[4] = ' ';
						}break;
						case 0x42:
						if(keyPressed == 1){
							notesPlayed[5] = 1;
							colour += 30;
							notes[5] = 'A';
							//keyPressed = 0;
						}else{
							notesPlayed[5] = 0;
							keyPressed = 1;
							notes[5] = ' ';
						}break;
						case 0x4B:
						if(keyPressed == 1){
							notesPlayed[6] = 1;
							colour += 30;
							notes[6] = 'B';
							//keyPressed = 0;
						}else{
							notesPlayed[6] = 0;
							keyPressed = 1;
							notes[6] = ' ';
						}break;

						case 0x4C:
						if(keyPressed == 1){
							notesPlayed[7] = 1;
							colour += 30;
							notes[7] = 'C';
							//keyPressed = 0;
						}else{
							notesPlayed[7] = 0;
							keyPressed = 1;
							notes[7] = ' ';
						}break;

						case 0xF0:
							keyPressed = 0;
							break;

						case 0x43: //increase sound with key 'I'
						if(keyPressed ==1){
							if(amplitude <10){
								amplitude++;
							}
						}break;

						case 0x2D: //Decrease sound with key 'R'
						if(keyPressed == 1){
							if(amplitude !=0){
								amplitude--;
							}
						}break;

						default:
							keyPressed = 0;
							note = ' ';
					}
				}
			}

			//display the note played at the bottom left corner	
			int i;
			for(i=0; i<8; i++) {
				drawNote(6+i,notes[i]);
			}

			signalSum = makeSignal(notesPlayed, t);
			signalSum = amplitude * signalSum; 
			// Every 20 microseconds this flag goes high
			if(hps_tim0_int_flag == 1) {
				hps_tim0_int_flag = 0;
				audio_write_data_ASM(signalSum, signalSum);
				t++;
			}
			
			int x = 0;
			double y = 0;
			// To reduce the number of drawing operations
			if((t%10 == 0)){
				//draw volume number in bottom right
				if(amplitude == 10){
					VGA_write_byte_ASM(78, 59, 16);
				} else {
					//volume = 0-9
					VGA_write_byte_ASM(78, 59, amplitude);
				}

				x = (t/10)%320;
				//clear drawn points
				VGA_draw_point_ASM(x, history[x], 0);
				//120 centers the signal on the screen, 500000 is abitrary to make it fit
				y = 120 + signalSum/500000;
				//add new points to history array
				history[x] = y;
				//draw new points
				VGA_draw_point_ASM(x, y, colour);
				colour+=250;
			}
			// Reset the signal
			signalSum = 0;
			// Reset the counter
			if(t==48000){
				t=0;
			}
	}
	return 0;
}
