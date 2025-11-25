#ifndef processing
#define processing

// contants for the calculations
extern const double adc_resolution; // voltage relative to the LSB
extern const double current_gain; // total current gain in the circuit
extern const double voltage_gain; // total voltage gain in the circuit

// functions to process the adc samples, one for energy and rms values and one for the instant waves
void process_and_print_rms(int* voltage_data, int* current_data, int* ilum_data, int* temp_data);
void process_and_print_waves(int* voltage_data, int* current_data, int* ilum_data, int* temp_data);

#endif
