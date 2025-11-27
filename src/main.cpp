#include <Arduino.h>
#include <avr/common.h>
#include <avr/io.h>

#include "pins_arduino.h"
#include "processing.hpp"
#include "sampling.hpp"

#define RESET_LED_PIN 9

void setup() {
  Serial.begin(921600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(FLAG_PIN, INPUT);
  pinMode(RESET_LED_PIN, INPUT);

  adc_and_timer_setup();
  adc_and_timer_enable();
}

void loop() {
    if (digitalRead(RESET_LED_PIN)) digitalWrite(LED_BUILTIN, LOW);

    if (ready_flag)
    {
        if (digitalRead(FLAG_PIN))
        {
            process_and_print_rms(
                dataA0[reading_buffer],
                dataA1[reading_buffer],
                BUFFER_SIZE);
        }
        else
        {
            process_and_print_waves(
                dataA0[reading_buffer],
                dataA1[reading_buffer],
                dataA2[reading_buffer],
                dataA3[reading_buffer],
                BUFFER_SIZE);
        }

        noInterrupts();
        ready_flag = false;
        interrupts();
    }
}
