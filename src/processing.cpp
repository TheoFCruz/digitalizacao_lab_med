#include "processing.hpp"
#include "sampling.hpp"

#include <Arduino.h>

const float adc_resolution = 5.0/1023; // FSR/(2^n - 1)
const float current_gain = 1.35*8.0*(3.2/1.5); // Rs * AmpIso * AmpOps
const float voltage_gain = (6.0/127.0)*(4.8/17.2); // 6 rms transformer gain
// const float current_gain = 1; // Rs * AmpIso * AmpOps
// const float voltage_gain = 1; // 6 rms transformer gain

float energy = 0.0;

void process_and_print_rms(
    volatile int* voltage_data,
    volatile int* current_data,
    int buffer_size)
{
    // Offset value
    float current_offset = 0.0;
    float voltage_offset = 0.0;
    for (int i = 0; i < buffer_size; i++)
    {
        current_offset += current_data[i];
        voltage_offset += voltage_data[i];
    }
    current_offset = current_offset/buffer_size;
    voltage_offset = voltage_offset/buffer_size;

    // RMS Values and active power
    float current_rms = 0.0;
    float voltage_rms = 0.0;

    float active_power = 0.0;

    for (int i = 0; i < buffer_size; i++)
    {
        current_rms += (float)(current_data[i]-current_offset)*(float)(current_data[i]-current_offset);
        voltage_rms += (float)(voltage_data[i]-voltage_offset)*(float)(voltage_data[i]-voltage_offset);

        active_power += (float)(current_data[i]-current_offset)*(float)(voltage_data[i]-voltage_offset);
    }

    current_rms = sqrt(current_rms/buffer_size)*adc_resolution/current_gain;
    voltage_rms = sqrt(voltage_rms/buffer_size)*adc_resolution/voltage_gain;

    active_power = (active_power/buffer_size)*adc_resolution*adc_resolution/(current_gain*voltage_gain);


    // Energy
    float time_interval = (float)buffer_size/SAMP_FREQ;
    energy += time_interval*active_power;

    // Prints on serial monitor
    Serial.print("V_rms: ");
    Serial.print(voltage_rms);
    Serial.print(" V\n");

    Serial.print("I_rms: ");
    Serial.print(current_rms*1000);
    Serial.print(" mA\n");

    Serial.print("P: ");
    Serial.print(active_power);
    Serial.print(" W\n");

    Serial.print("E: ");
    Serial.print(energy);
    Serial.print(" J\n\n");
}

void process_and_print_waves(
    volatile int* voltage_data,
    volatile int* current_data,
    volatile int* ilum_data,
    volatile int* temp_data,
    int buffer_size)
{
    float voltage_value = 0.0;
    float current_value = 0.0;
    float ilum_value = 0.0;
    float temp_value = 0.0;

    for (int i = 0; i < buffer_size; i++)
    {
        voltage_value = (voltage_data[i]*adc_resolution)/voltage_gain;
        current_value = (current_data[i]*adc_resolution)/current_gain;
        ilum_value = ilum_data[i]*adc_resolution;
        temp_value = temp_data[i]*adc_resolution;


        char str_bfr[24];
        char v_buf[6], i_buf[6], il_buf[6], t_buf[6];

        dtostrf(voltage_value, 4, 1, v_buf);
        dtostrf(current_value*1000, 4, 1, i_buf);
        dtostrf(ilum_value, 4, 1, il_buf);
        dtostrf(temp_value, 4, 1, t_buf);

        // snprintf(str_bfr, sizeof(str_bfr),
        //     "%s\t%s\t%s\t%s\n",
        //     v_buf, i_buf, il_buf, t_buf);

        if (digitalRead(WAVES_PIN))
        {
            snprintf(str_bfr, sizeof(str_bfr),
                "%s\t%s\n",
                v_buf, i_buf);
        }
        else
        {
            snprintf(str_bfr, sizeof(str_bfr),
                "%s\t%s\n",
                il_buf, t_buf);
        }

        Serial.print(str_bfr);
    }
}
