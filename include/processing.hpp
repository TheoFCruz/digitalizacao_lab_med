#ifndef processing
#define processing

// Functions to process the adc samples, one for energy and rms values and one for the instant waves
void process_and_print_rms(int* voltage_data, int* current_data, int* ilum_data, int* temp_data);
void process_and_print_waves(int* voltage_data, int* current_data, int* ilum_data, int* temp_data);

#endif
