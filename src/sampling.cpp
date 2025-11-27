#include "sampling.hpp"

#include <Arduino.h>
#include <avr/io.h>

volatile int dataA0[2][BUFFER_SIZE];
volatile int dataA1[2][BUFFER_SIZE];
volatile int dataA2[2][BUFFER_SIZE];
volatile int dataA3[2][BUFFER_SIZE];

int data_index = 0;
int channel_index = 0;
volatile int writing_bufer = 0;
volatile int reading_buffer = 1;
volatile bool ready_flag = false;

void adc_and_timer_setup()
{
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);

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

    OCR0A = 250e3/(SAMP_FREQ*4) - 1; // interrupt frequency = 250kHz/50 = 5kHz -> 1.25kHz / channel
    TIMSK0 = 0x02; // enables compare a interrupts
}

void adc_and_timer_enable()
{
    // ------ Conversion Start -------
    SREG |= 0x80; // enables interrupts
    ADCSRA |= 0x80; // enables the ADC
    TCCR0B = 0x03; // enables timer with prescaler set to clk/64 = 250kHz
}

ISR(ADC_vect)
{
    int sample;

    sample = ADCL;
    sample += ADCH << 8;

    // stores sample
    switch (channel_index)
    {
        case 0:
        dataA0[writing_bufer][data_index] = sample;
        break;
        case 1:
        dataA1[writing_bufer][data_index] = sample;
        break;
        case 2:
        dataA2[writing_bufer][data_index] = sample;
        break;
        case 3:
        dataA3[writing_bufer][data_index] = sample;
        break;
    }

    // updates data index
    if (channel_index == 3) data_index++;

    // updates channel
    channel_index = (channel_index + 1)%4;
    ADMUX &= 0xF0;
    ADMUX |= channel_index;

    if (data_index == BUFFER_SIZE)
    {
        if (ready_flag) // the serial hasnt finished
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }

        ready_flag = true;
        data_index = 0;
        channel_index = 0;
        reading_buffer = writing_bufer;
        writing_bufer = (writing_bufer + 1)%2;
    }
}

ISR(TIMER0_COMPA_vect)
{
    // nothing to do, just clears the flag
}
