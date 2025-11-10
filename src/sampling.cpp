#include "sampling.hpp"
#include <avr/io.h>

const int buffer_size = 100;

int dataA0[buffer_size];
int dataA1[buffer_size];
int dataA2[buffer_size];
int dataA3[buffer_size];

int data_index = 0;
int channel_index = 0;

bool full_flag = false;

void adc_and_timer_setup()
{
    // -------- ADC Setup ------------
    ADMUX = 0x00; // sets right adjust and pin A0
    ADMUX |= 0x40; // sets VREF to AVcc

    ADCSRA = 0x00;
    ADCSRA |= 0x20; // enables autotrigger
    ADCSRA |= 0x08; // enables ADC interrupts
    ADCSRA |= 0x06; // set prescaler to 64, clk = 250kHz

    ADCSRB |= 0x00;
    ADCSRB |= 0x03; // sets autotrigger source to timer0 compare

    DIDR0 = 0xFF; // disables digital input buffers

    // -------- Timer0 Setup ---------
    TCCR0A = 0x02; // clear timer on compare mode
    TCCR0B = 0x00; // no clock source -> timer disabled
    TCNT0 = 0; // counter set to 0

    OCR0A = 134; // interrupt frequency = 2MHz/135 = 14,8kHz -> 3,7 kHz / channel
    TIMSK0 = 0x02; // enables compare a interrupts
}

void adc_and_timer_enable()
{
    // ------ Conversion Start -------
    SREG |= 0x80; // enables interrupts
    ADCSRA |= 0x80; // enables the ADC
    TCCR0B = 0x02; // enables timer with prescaler set to clk/8 = 2MHz
}

ISR(ADC_vect)
{
    if (full_flag) return;

    int sample;

    sample = ADCL;
    sample += ADCH << 8;

    // stores sample
    switch (channel_index)
    {
        case 0:
        dataA0[data_index] = sample;
        break;
        case 1:
        dataA1[data_index] = sample;
        break;
        case 2:
        dataA2[data_index] = sample;
        break;
        case 3:
        dataA3[data_index] = sample;
        break;
    }

    // updates data index
    if (channel_index == 3) data_index++;

    // updates channel
    channel_index = (channel_index + 1)%4;
    ADMUX &= 0xF0;
    ADMUX |= channel_index;

    if (data_index == buffer_size)
    {
        full_flag = true;
        data_index = 0;
        channel_index = 0;
    }
}

ISR(TIMER0_COMPA_vect)
{
    // nothing to do, just clears the flag
}
