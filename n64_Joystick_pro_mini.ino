#include <avr/io.h>
#include <util/delay.h>

int Lc = 0; // count pulses variables
int Rc = 0; 
int Uc = 0;
int Dc = 0;

void setup() {
  Serial.begin(9600);
DDRB |= (1<<DDB1); // // joystick pin 1 - left to right
DDRD |= (1<<DDD6); // on the n64 controller PCB
DDRD |= (1<<DDD5);
DDRD |= (1<<DDD3);

DDRB &= ~(1<<DDB4); // up
DDRB &= ~(1<<DDB3); // left
DDRB &= ~(1<<DDB2); // right
DDRB &= ~(1<<DDB0); // down


}

void loop() { 
  
  //if(!(PINB &(0b000100))){ // D10
  if(!(PINB &(0b000100))){
    if(Lc < 65){ // Dont send too many pulses
      PORTB |= 1<<1; 
      _delay_us(4);  // when converting to baremetal the code ran too fast for the n64 controller to see the pulses
      PORTD |= 1<<6; // so delays are needed to make the pulses the length of a call for digitalWrite()
      _delay_us(4);
      PORTB &= ~(1<<1); 
      _delay_us(4);
      PORTD &= ~(1<<6); 
      _delay_us(4);
      ++Lc;
    }
    
  }
  if(!(PINB &(0b001000))){ // D11
    
    if(Rc < 65){
      PORTD |= 1<<6; // 
      _delay_us(4);
            PORTB |= 1<<1; 
            _delay_us(4);
            PORTD &= ~(1<<6); // 
            _delay_us(4);
            PORTB &= ~(1<<1); // 
            _delay_us(4);
      ++Rc;
    }
    
  }
  if(!(PINB &(0b010000))){ //  D12
    
    if(Dc < 65){
      PORTD |= 1<<3; // 3 leading 5
      _delay_us(4);
          PORTD |= 1<<5;
          _delay_us(4);
          PORTD &= ~(1<<3);  
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
      ++Dc;
    }
    
  }
  if(!(PINB &(0b000001))){ // D8
    if(Uc < 65){
      PORTD |= 1<<5; // 5 leading 3
      _delay_us(4);
          PORTD |= 1<<3;
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
          PORTD &= ~(1<<3);
          _delay_us(4);
      ++Uc;
    }
    
   } 
     // To stop going a direction Feed the pulses back 
     //in the opposite direction
     if(PINB &(0b000100)){ // D10
        if(Lc > 65){
          for(int i=0; i<65; i++){
            PORTD |= 1<<6; // 
            _delay_us(4);
            PORTB |= 1<<1;
            _delay_us(4);
            PORTD &= ~(1<<6); // 
            _delay_us(4);
            PORTB &= ~(1<<1); // 
            _delay_us(4);
          }
          Lc = 0;
        }
        else{
          for(int i=0; i<Lc; i++){
            PORTD |= 1<<6; // 
            _delay_us(4);
            PORTB |= 1<<1; 
            _delay_us(4);
            PORTD &= ~(1<<6); // 
            _delay_us(4);
            PORTB &= ~(1<<1); // 
            _delay_us(4);
          }
          Lc = 0;
        }
     }
      ////////////
      if(PINB &(0b001000)){ // D8
        if(Rc > 65){
          for(int i=0; i<65; i++){
            PORTB |= 1<<1; 
            _delay_us(4);
            PORTD |= 1<<6;
            _delay_us(4);
            PORTB &= ~(1<<1); 
            _delay_us(4);
            PORTD &= ~(1<<6);
            _delay_us(4);
          }
          Rc = 0;
        }
        else{
          for(int i=0; i<Rc; i++){
            PORTB |= 1<<1; 
            _delay_us(4);
            PORTD |= 1<<6;
            _delay_us(4);
            PORTB &= ~(1<<1); 
            _delay_us(4);
            PORTD &= ~(1<<6); 
            _delay_us(4);
          }
          Rc = 0;
        }
      }
///////////////////////////////////////
    if(PINB &(0b010000)){ // D12
      if(Dc > 65){
        for(int i=0; i<65; i++){
          PORTD |= 1<<5; // 5 leading 3
          _delay_us(4);
          PORTD |= 1<<3;
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
          PORTD &= ~(1<<3);
          _delay_us(4);
        }
        Dc = 0;
      }
      else{
        for(int i=0; i<Dc; i++){
          PORTD |= 1<<5; // 5 leading 3
          _delay_us(4);
          PORTD |= 1<<3;
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
          PORTD &= ~(1<<3);
          _delay_us(4);
        }
        Dc = 0;
      }
    }
    if(PINB &(0b000001)){ // D11 
      if(Uc > 65){
        for(int i=0; i<65; i++){
          PORTD |= 1<<3; // 3 leading 5
          _delay_us(4);
          PORTD |= 1<<5; // 
          _delay_us(4);
          PORTD &= ~(1<<3);  
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
        }
        Uc = 0;
      }
      else{
        for(int i=0; i<Uc; i++){
          PORTD |= 1<<3; // 3 leading 5
          _delay_us(4);
          PORTD |= 1<<5; // 
          _delay_us(4);
          PORTD &= ~(1<<3);  
          _delay_us(4);
          PORTD &= ~(1<<5); 
          _delay_us(4);
        }
        Uc = 0;
      }
    }
  
      
      
  
  
 // if(!digitalRead(10)) Serial.println("HI");
  

}
