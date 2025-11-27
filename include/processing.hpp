#ifndef processing
#define processing

#define FLAG_PIN 8 // pin that defines which information is printed

// contants for the calculations
extern const float adc_resolution; // voltage relative to the LSB
extern const float current_gain; // total current gain in the circuit
extern const float voltage_gain; // total voltage gain in the circuit

// variable to store energy
extern float energy;

// functions to process the adc samples, one for energy and rms values and one for the instant waves
void process_and_print_rms(
    volatile int* voltage_data,
    volatile int* current_data,
    int buffer_size);
void process_and_print_waves(
    volatile int* voltage_data,
    volatile int* current_data,
    volatile int* ilum_data,
    volatile int* temp_data,
    int buffer_size);

#endif
