#include <stdio.h>
#include "./drivers/inc/audio.h"

#define SAMPLE 48000
/*Number of 1's and 0's to write
48000/(2*100)*/
int main() {
	int i = 0; //counter for 1's
	int j = 0; //counter for 0's
	while(1) {
		while(i<240) {
			//if i has not hit 240,
			//we keep on writing 1
			if(audio(0x00FFFFFF)) {
				i++;
			}
		}
		//if j has not hit 240,
		//we keep on writing 0
		while(j<240) {
			if(audio(0x00000000)) {
				j++;
			}
		}
		//reset i and j, and cycle
		if(i == 240 && j == 240){
			i = 0;
			j = 0;
		}
	}
	return 0;
}
