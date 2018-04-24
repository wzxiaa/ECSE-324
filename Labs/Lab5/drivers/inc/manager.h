#ifndef _MAN
#define _MAN

	extern int add_note_asm(int originalNote, int newNote);
	extern int remove_note_asm(int originalNote, int removeNote);
	extern void print_wave_asm(int signal, int row);
	extern float note_to_freq_asm(int note, float *freqs);
#endif