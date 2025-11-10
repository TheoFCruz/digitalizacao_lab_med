#include <Arduino.h>
#include <avr/common.h>
#include <avr/io.h>

#include "sampling.hpp"

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

  adc_and_timer_setup();
  adc_and_timer_enable();
}

void loop() {

}
