
int Lc = 0; // count left pulses
int Rc = 0; // count right pulses
int Uc = 0;
int Dc = 0;

void setup() {
  Serial.begin(9600);
pinMode(9, OUTPUT); // // joystick pin 1 - left to right
pinMode(6, OUTPUT); 
pinMode(5, OUTPUT); 
pinMode(3, OUTPUT); 

pinMode(12, INPUT_PULLUP); // up
pinMode(11, INPUT_PULLUP); // left
pinMode(10, INPUT_PULLUP); // right
pinMode(8, INPUT_PULLUP); // down


}

// Length of the pulses determines the sensitivity 
// so we convert this to baremetal then 
// maybe place millisecond delays and change the 
// length of them determined by the analog voltage 
// coming from a joystick potentiometer 

void loop() { 
  
  if(!digitalRead(11)){ // left
    if(Lc < 65){ // Dont send too many pulses
      digitalWrite(9, HIGH); // rise 
      digitalWrite(6, HIGH); // rise 
      digitalWrite(9, LOW); // fall 
      digitalWrite(6, LOW); // fall
      ++Lc;
    }
  }
  if(!digitalRead(10)){ // right
    if(Rc < 65){
      digitalWrite(6, HIGH); 
      digitalWrite(9, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(9, LOW); 
      ++Rc;
    }
  }
  if(!digitalRead(8)){ // down
    if(Dc < 65){
      digitalWrite(3, HIGH); 
      digitalWrite(5, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(5, LOW); 
      ++Dc;
    }
  }
  if(!digitalRead(12)){ // up
    if(Uc < 65){
      digitalWrite(5, HIGH); 
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(3, LOW); 
      ++Uc;
    }
}
 
 
  if(digitalRead(11) && digitalRead(10) && digitalRead(8) && digitalRead(12)){
     // To stop going a direction Feed the pulses back 
     //in the opposite direction
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
      ////////////
      if(Rc > 65){
        for(int i=0; i<65; i++){
          digitalWrite(9, HIGH); // rise 
          digitalWrite(6, HIGH); // rise 
          digitalWrite(9, LOW); // fall 
          digitalWrite(6, LOW); // fall 
        }
        Rc = 0;
      }
      else{
        for(int i=0; i<Rc; i++){
          digitalWrite(9, HIGH); // rise 
          digitalWrite(6, HIGH); // rise 
          digitalWrite(9, LOW); // fall 
          digitalWrite(6, LOW); // fall 
        }
        Rc = 0;
      }
///////////////////////////////////////
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
