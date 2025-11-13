#include <Arduino.h>
#include <avr/common.h>
#include <avr/io.h>

#include "HardwareSerial.h"
#include "sampling.hpp"

void setup() {
  Serial.begin(921600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  adc_and_timer_setup();
  adc_and_timer_enable();
}

void loop() {
    if (ready_flag)
    {
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            Serial.print(dataA0[reading_buffer][i]); Serial.print("\t");
            Serial.print(dataA1[reading_buffer][i]); Serial.print("\t");
            Serial.print(dataA2[reading_buffer][i]); Serial.print("\t");
            Serial.print(dataA3[reading_buffer][i]); Serial.print("\n");
        }

        noInterrupts();
        ready_flag = false;
        interrupts();
    }
}
