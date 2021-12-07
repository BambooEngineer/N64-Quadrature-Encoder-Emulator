#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int Lc = 0; // count pulses variables
int Rc = 0; 
int Uc = 0;
int Dc = 0;

//int H;
//int V;

int main() {
    stdio_init_all();
    adc_init();

    gpio_init(10); // inputs - DPAD
	gpio_init(11);
	gpio_init(12);
	gpio_init(13);
	gpio_init(18);// outputs - JOYSTICK PORT
	gpio_init(19);
	gpio_init(20);
	gpio_init(21);

	
	gpio_set_dir(10, 0); // I DPAD
    gpio_set_dir(11, 0);
    gpio_set_dir(12, 0);
    gpio_set_dir(13, 0);
    gpio_set_dir(18, 1); // O
    gpio_set_dir(19, 1);
    gpio_set_dir(20, 1);
    gpio_set_dir(21, 1); // Left to right ---> 21 - 18
	//gpio_pull_up(18);
    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26); // X & Y pots
    adc_gpio_init(27);

    // sleep_us();
    // gpio_put();
    // gpio_get();
///////////////////////////////////////////////////////////////
    //adc_select_input(0);
      //  uint adc_x_raw = adc_read();
      //  adc_select_input(1);
      //  uint adc_y_raw = adc_read();

    //while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        //const float conversion_factor = 3.3f / (1 << 12);
        //uint16_t result = adc_read();
        //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        //sleep_ms(500);
   // }
/////////////////////////////////////////////////////////////////

while(1){

    adc_select_input(0);
    uint H = adc_read();
    //printf("joystick x: %d \n", adc_x_raw);

    adc_select_input(1);
    uint V = adc_read();
    //printf("joystick y: %d \n", adc_y_raw);
    //sleep_ms(100);

    //if(!(PINB &(0b000100)) || H < 461){
        if(!gpio_get(10) || H < 1300){
        if(Lc < 65){ // Dont send too many pulses
        gpio_put(21, 1); 
        sleep_us(4);  
        gpio_put(20, 1);  
        sleep_us(4);
        gpio_put(21, 0); 
        sleep_us(4);
        gpio_put(20, 0); 
        sleep_us(4);
        ++Lc;
        }
        
    }
    //if(!(PINB &(0b001000)) || H > 600){ // D11
        if(!gpio_get(11) || H > 2400){
        if(Rc < 65){
        gpio_put(20, 1); // 
        sleep_us(4);
                gpio_put(21, 1);
                sleep_us(4);
                gpio_put(20, 0); // 
                sleep_us(4);
                gpio_put(21, 0); // 
                sleep_us(4);
        ++Rc;
        }
        
    }
    //if(!(PINB &(0b010000)) || V < 430){ //  D12
        if(!gpio_get(13) || V < 1300){
        if(Dc < 65){
        gpio_put(18, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(19, 1);
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
        ++Dc;
        }
        
    }
    //if(!(PINB &(0b000001)) || V > 530){ // D8
    if(!gpio_get(12) || V > 2400){
        if(Uc < 65){
        gpio_put(19, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(18, 1);
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
        ++Uc;
        }
        
    } 
    /////////////////////////////////////////////////////////////
        // To stop going a direction Feed the pulses back 
        //in the opposite direction
        //if(PINB &(0b000100) && (H > 430 && H < 530)){ // D10
        if(gpio_get(10) && (H > 1300 && H < 2400)){
            if(Lc > 65){
            for(int i=0; i<65; i++){
                gpio_put(20, 1); // 
                sleep_us(4);
                gpio_put(21, 1);
                sleep_us(4);
                gpio_put(20, 0); // 
                sleep_us(4);
                gpio_put(21, 0); // 
                sleep_us(4);
            }
            Lc = 0;
            }
            else{
            for(int i=0; i<Lc; i++){
                gpio_put(20, 1); // 
                sleep_us(4);
                gpio_put(21, 1);
                sleep_us(4);
                gpio_put(20, 0); // 
                sleep_us(4);
                gpio_put(21, 0); // 
                sleep_us(4);
            }
            Lc = 0;
            }
        }
        ////////////
        //if(PINB &(0b001000) && (H > 430 && H < 530)){ // D8
        if(gpio_get(11) && (H > 1300 && H < 2400)){
            if(Rc > 65){
            for(int i=0; i<65; i++){
                gpio_put(21, 1); 
        sleep_us(4);  
        gpio_put(20, 1);  
        sleep_us(4);
        gpio_put(21, 0); 
        sleep_us(4);
        gpio_put(20, 0); 
        sleep_us(4);
            }
            Rc = 0;
            }
            else{
            for(int i=0; i<Rc; i++){
                gpio_put(21, 1); 
        sleep_us(4);  
        gpio_put(20, 1);  
        sleep_us(4);
        gpio_put(21, 0); 
        sleep_us(4);
        gpio_put(20, 0); 
        sleep_us(4);
            }
            Rc = 0;
            }
        }
    ///////////////////////////////////////
        //if(PINB &(0b010000) && (V > 461 && V < 600)){ // D12
        if(gpio_get(13) && (V > 1300 && V < 2400)){
        if(Dc > 65){
            for(int i=0; i<65; i++){
            gpio_put(19, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(18, 1);
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
            }
            Dc = 0;
        }
        else{
            for(int i=0; i<Dc; i++){
            gpio_put(19, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(18, 1);
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
            }
            Dc = 0;
        }
        }
        //if(PINB &(0b000001) && (V > 461 && V < 600)){ // D11 
        if(gpio_get(12) && (V > 1300 && V < 2400)){
        if(Uc > 65){
            for(int i=0; i<65; i++){
            gpio_put(18, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(19, 1);
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
            }
            Uc = 0;
        }
        else{
            for(int i=0; i<Uc; i++){
            gpio_put(18, 1); // 3 leading 5
        sleep_us(4);
            gpio_put(19, 1);
            sleep_us(4);
            gpio_put(18, 0); 
            sleep_us(4);
            gpio_put(19, 0); 
            sleep_us(4);
            }
            Uc = 0;
        }
        }


    }

}