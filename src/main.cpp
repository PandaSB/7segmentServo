#include <Arduino.h>
#include <Servo.h>

#define NB_SERVO   7
int SaveValue = -1 ; 
int Valeur = 0 ; 
int   ServoPin   [NB_SERVO] = {2,3,4,9,6,7,8} ; 
Servo ServoHandle[NB_SERVO];
int   ServoOn      [NB_SERVO] = { 90, 90, 90, 90, 90, 90, 90} ; 
int   ServoOff     [NB_SERVO] = {  0,  0,  0,180,  0,  0,180} ; 
bool  Segments     [][7] =  {
  {true , true , true , true , true , true , false }, // 0
  {false, true , true , false, false, false, false }, // 1
  {true , true , false, true , true,  false, true }, // 2
  {true , true , true , true , false,  false, true }, // 3
  {false , true , true , false , false,  true, true }, // 4
  {true , false , true , true , false,  true, true }, // 5
  {true , false , true , true , true,  true, true }, // 6
  {true , true , true , false , false,  false, false }, // 7
  {true , true , true , true , true,  true, true }, // 8
  {true , true , true , true , false,  true, true }, // 9
  {false , false , false, false , false,  false, false } // 
}; 


void Set7Segment (int Value , boolean force)
{
  if (( Value != SaveValue ) || (force == true ))
  {
    for ( int i = 0 ; i < NB_SERVO ; i++) 
    {
      int Oldstate = ServoHandle[i].read() ; 
      int NewState = Segments[Value][i] ? ServoOn[i] : ServoOff[i] ; 
      if ((i== 6) && (NewState != Oldstate)) {
        ServoHandle[2].write((ServoOn[2] + ServoOff[2])/2);              // Demande au servo de se déplacer à cette position angulaire
        ServoHandle[4].write((ServoOn[4] + ServoOff[4])/2);              // Demande au servo de se déplacer à cette position angulaire
        delay(100) ; 
      }
      ServoHandle[i].write(NewState);              // Demande au servo de se déplacer à cette position angulaire
      if ((i== 6) && (NewState != Oldstate)) {
        delay(100) ; 
        ServoHandle[2].write(Segments[Value][2] ? ServoOn[2] : ServoOff[2]);              // Demande au servo de se déplacer à cette position angulaire
        ServoHandle[4].write(Segments[Value][4] ? ServoOn[4] : ServoOff[4]);              // Demande au servo de se déplacer à cette position angulaire
      }
    }
  }
  SaveValue = Value ; 
}

void setup() {
  Serial.begin(115200);                       
  while(!Serial){;} 
  for ( int i = 0 ; i < NB_SERVO ; i++) 
  {
    ServoHandle[i].attach(ServoPin[i]);  // attache le servo au pin spécifié sur l'objet myservo

  }
  Set7Segment (0, true ) ; 
  delay (1000) ; 
}

void loop() {
  Set7Segment (Valeur, false ) ; 
  Valeur ++ ; 
  if (Valeur > 9) {Valeur = 0 ; }
  delay (1000) ; 
}