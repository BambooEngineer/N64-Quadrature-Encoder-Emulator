#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int Lc = 0; // count pulses variables
int Rc = 0; 
int Uc = 0;
int Dc = 0;

int HL = 0; // Sensitivity Variables
int HR = 0;
int VL = 0;
int VR = 0;

//have to make sure the amount of pulses sent increases as the joystick gets farther from the deadzone. 
//if its outside of the deadzone: 
                 //map(  ( Position - Deadzone Max ) , min 0, max joystick range, 0, 65 ) ( This was a brain storm )

int map(int x, int in_min, int in_max, int out_min, int out_max) { // x is the joystick pos subtract by Deadzone min or max, in min and max requires experimentation( 0-1000 ? )
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;  // 1300 and 2400 are the deadzone boundaries, 0-65 are min and max outputs, 
}



int main() {
    stdio_init_all();
    adc_init();

    gpio_init(1); // CONTROL MODE SWITCH
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
    gpio_set_dir(2, 0); // CONTROL MODE SWITCH
    gpio_set_dir(18, 1); // O
    gpio_set_dir(19, 1);
    gpio_set_dir(20, 1);
    gpio_set_dir(21, 1); // Left to right ---> 21 - 18
	gpio_pull_up(2); // if gpio 2 is grounded then the DPAD is deselected as a joystick
    adc_init();

    
    adc_gpio_init(26); // X & Y pots
    adc_gpio_init(27);

    // sleep_us();
    // gpio_put();
    // gpio_get();
/////////////////////////////////////////////////////////////////

while(1){

    adc_select_input(0);
    uint V = adc_read(); // Actually Vertical 

    adc_select_input(1);
    uint H = adc_read(); // Actually Horizontal 

    //if(!(PINB &(0b000100)) || H < 461){
        if((!gpio_get(10) && gpio_get(2)) || V < 1300){
            HL = map(1300-V, 1300, 667, 0, 65); 
            HL = map(HL, 133, 65, 0, 65);                   
            if(Lc < HL || (Lc < 65 && gpio_get(2))){ // Dont send too many pulses     
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
        if((!gpio_get(11) && gpio_get(2)) || V > 2400){
            HR = map(V-2400, 100, 900, 0, 65); 
            if(Rc < HR || (Rc < 65 && gpio_get(2))){
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
        if((!gpio_get(13) && gpio_get(2)) || H < 1300){
            //HL = 1300-V;
            VL = map(1300-H, 1300, 667, 0, 65); // this is spitting out all left to little left = 65-133
            VL = map(VL, 133, 65, 0, 65); // needed 2 maps 
            //printf("joystick x: %d \n", HL);
            if(Dc < VL || (Dc < 65 && gpio_get(2))){ 
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
    if((!gpio_get(12) && gpio_get(2)) || H > 2400){
        VR = map(H-2400, 100, 900, 0, 65); // this is spitting out all left to little left = 65-133
        //HR = map(HL, 1, 900, 0, 65);
       // printf("joystick x: %d \n", HR); // a little right to all right = 1-900
            if(Uc < VR || (Uc < 65 && gpio_get(2))){
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
        if(gpio_get(10) && (V > 1300 && V < 2400)){
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
        if(gpio_get(11) && (V > 1300 && V < 2400)){
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
        if(gpio_get(13) && (H > 1300 && H < 2400)){
            if(Dc > 65){
                for(int i=0; i<65; i++){
                    gpio_put(19, 1); 
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
                gpio_put(19, 1); 
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
        if(gpio_get(12) && (H > 1300 && H < 2400)){
            if(Uc > 65){
                for(int i=0; i<65; i++){
                    gpio_put(18, 1); 
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
                gpio_put(18, 1); 
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