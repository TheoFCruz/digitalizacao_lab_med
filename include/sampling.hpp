#ifndef sampling
#define sampling

#include <avr/interrupt.h>
#include <avr/io.h>

// Size of each data buffer
#define BUFFER_SIZE 100

// data arrays for each channel of size buffer_size. double buffering with first index
extern volatile int dataA0[2][BUFFER_SIZE];
extern volatile int dataA1[2][BUFFER_SIZE];
extern volatile int dataA2[2][BUFFER_SIZE];
extern volatile int dataA3[2][BUFFER_SIZE];

extern  int data_index; // next index to store sample
extern  int channel_index; // current channel sampling (0, 1, 2 or 3)
extern volatile int writing_bufer; // current buffer being written to (0 or 1)
extern volatile int reading_buffer; // current buffer being written to (0 or 1)
extern volatile bool ready_flag; // indicates when the arrays are full and ready to send

// self explanatory
void adc_and_timer_setup();
void adc_and_timer_enable();

// interrupt sequences
ISR(ADC_vect);
ISR(TIMER0_COMPA_vect);

#endif
