#include "processing.hpp"

#include <Arduino.h>

void process_and_print_rms(int* voltage_data, int* current_data, int buffer_size)
{
    const double resolution = 5.0/1023;

    // RMS Values
    double current_rms = 0.0;
    double voltage_rms = 0.0;

    for (int i = 0; i < buffer_size; i++)
    {
        current_rms += current_data[i]*current_data[i];
        voltage_rms += voltage_data[i]*voltage_data[i];
    }

    current_rms = sqrt(resolution*current_rms/buffer_size);
    voltage_rms = sqrt(resolution*voltage_rms/buffer_size);

    // Active power

}

void process_and_print_waves(int* voltage_data, int* current_data, int* ilum_data, int* temp_data, int buffer_size)
{

}
