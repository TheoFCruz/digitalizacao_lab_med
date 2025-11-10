#ifndef sampling
#define sampling

#include <avr/interrupt.h>
#include <avr/io.h>

// size of the data buffers for pooling
extern const int buffer_size;

// data arrays for each channel of size buffer_size
extern int dataA0[];
extern int dataA1[];
extern int dataA2[];
extern int dataA3[];

extern int data_index; // next index to store sample
extern int channel_index; // current channel sampling (0, 1, 2 or 3)

// indicates when the arrays are full and ready to send
extern bool full_flag;

// self explanatory
void adc_and_timer_setup();
void adc_and_timer_enable();

// interrupt sequences
ISR(ADC_vect);
ISR(TIMER0_COMPA_vect);

#endif
