#include "processing.hpp"

#include <Arduino.h>

extern const double adc_resolution = 5.0/1023; // FSR/(2^n - 1)
extern const double current_gain = 1.35*8.0*3.625; // Rs * AmpIso * AmpOps
extern const double voltage_gain = 127.0/6.0; // 6 rms transformer gain

void process_and_print_rms(int* voltage_data, int* current_data, int buffer_size)
{
    // RMS Values
    double current_rms = 0.0;
    double voltage_rms = 0.0;

    for (int i = 0; i < buffer_size; i++)
    {
        current_rms += current_data[i]*current_data[i];
        voltage_rms += voltage_data[i]*voltage_data[i];
    }

    current_rms = sqrt(current_rms/buffer_size)*adc_resolution/current_gain;
    voltage_rms = sqrt(voltage_rms/buffer_size)*adc_resolution/voltage_gain;

    // Active power
    double active_power = 0.0;
}

void process_and_print_waves(int* voltage_data, int* current_data, int* ilum_data, int* temp_data, int buffer_size)
{

}
