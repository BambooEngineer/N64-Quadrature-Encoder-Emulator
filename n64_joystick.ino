//#include <avr/io.h>
//#include <util/delay.h>

int Lc = 0; // count pulses variables
int Rc = 0; 
int Uc = 0;
int Dc = 0;

void setup() {
  Serial.begin(9600);
pinMode(9, OUTPUT); // // joystick pin 1 - left to right
pinMode(6, OUTPUT); // connections on the n64 controller PCB where the joystick plugs into
pinMode(5, OUTPUT); 
pinMode(3, OUTPUT); 

pinMode(12, INPUT); // Buttons
pinMode(11, INPUT); // 
pinMode(10, INPUT); // 
pinMode(8, INPUT); // 


}

void loop() { 
  
  if(!digitalRead(10)){ // left
    if(Lc < 65){ // Dont send too many pulses
      digitalWrite(9, HIGH); // rise      9 leading 6
      digitalWrite(6, HIGH); // rise 
      digitalWrite(9, LOW); // fall 
      digitalWrite(6, LOW); // fall
      ++Lc;
    }
  }
  if(!digitalRead(11)){ // right
    if(Rc < 65){
      digitalWrite(6, HIGH);  // 6 leading 9
      digitalWrite(9, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(9, LOW); 
      ++Rc;
    }
  }
  if(!digitalRead(12)){ // down
    if(Dc < 65){
      digitalWrite(3, HIGH);  // 3 leading 5
      digitalWrite(5, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW); 
      ++Dc;
    }
  }
  if(!digitalRead(8)){ // up
    if(Uc < 65){
      digitalWrite(5, HIGH); // 5 leading 3
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(3, LOW); 
      ++Uc;
    }
}
     // To stop going a direction Feed the pulses back in the opposite direction
     if(digitalRead(10)){ // D10
        if(Lc > 65){
          for(int i=0; i<65; i++){
            digitalWrite(6, HIGH);  
          digitalWrite(9, HIGH);
          digitalWrite(6, LOW); 
          digitalWrite(9, LOW);
          }
          Lc = 0;
        }
        else{
          for(int i=0; i<Lc; i++){
            digitalWrite(6, HIGH);  
          digitalWrite(9, HIGH);
          digitalWrite(6, LOW); 
          digitalWrite(9, LOW);
          }
          Lc = 0;
        }
     }
      ////////////
      if(digitalRead(11)){ 
        if(Rc > 65){
          for(int i=0; i<65; i++){
            digitalWrite(9, HIGH);  
          digitalWrite(6, HIGH);
          digitalWrite(9, LOW); 
          digitalWrite(6, LOW);
          }
          Rc = 0;
        }
        else{
          for(int i=0; i<Rc; i++){
            digitalWrite(9, HIGH);  
          digitalWrite(6, HIGH);
          digitalWrite(9, LOW); 
          digitalWrite(6, LOW);
          }
          Rc = 0;
        }
      }
///////////////////////////////////////
    if(digitalRead(12)){ 
      if(Dc > 65){
        for(int i=0; i<65; i++){
          digitalWrite(5, HIGH);  
          digitalWrite(3, HIGH);
          digitalWrite(5, LOW); 
          digitalWrite(3, LOW); 
        }
        Dc = 0;
      }
      else{
        for(int i=0; i<Dc; i++){
          digitalWrite(5, HIGH); 
          digitalWrite(3, HIGH);
          digitalWrite(5, LOW); 
          digitalWrite(3, LOW); 
        }
        Dc = 0;
      }
    }
    if(digitalRead(8)){  
      if(Uc > 65){
        for(int i=0; i<65; i++){
          digitalWrite(3, HIGH); 
          digitalWrite(5, HIGH); 
          digitalWrite(3, LOW); 
          digitalWrite(5, LOW); 
        }
        Uc = 0;
      }
      else{
        for(int i=0; i<Uc; i++){
          digitalWrite(3, HIGH); 
          digitalWrite(5, HIGH); 
          digitalWrite(3, LOW); 
          digitalWrite(5, LOW); 
        }
        Uc = 0;
      }
    }
      
      
  
  
 // if(!digitalRead(10)) Serial.println("HI");
  

}
