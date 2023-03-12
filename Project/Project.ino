#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Otto.h> //-- Otto Library
Otto Otto;  //This is Otto!

#define LeftLeg 2
#define RightLeg 3
#define LeftFoot 4
#define RightFoot 5
#define Buzzer  13
#define Orientation 1 
#define DIN A3 
#define CS A2
#define CLK A1 

double angle_rad = PI / 180.0;
double angle_deg = 180.0 / PI;
int YL;
int YR;
int RL;
int RR;
double charRead;
void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
  Serial.begin(9600);
  YL = EEPROM.read(0);
  if (YL > 128) YL -= 256;
  YR = EEPROM.read(1);
  if (YR > 128) YR -= 256;
  RL = EEPROM.read(2);
  if (RL > 128) RL -= 256;
  RR = EEPROM.read(3);
  if (RR > 128) RR -= 256;
  Otto.home();
  Serial.println("OTTO REMOTE AND DANCE PROGRAM");
  Serial.println("PRESS w for walk forward.");
  Serial.println("PRESS s for walk backward.");
  Serial.println("PRESS a for turn left.");
  Serial.println("PRESS d for turn right.");
  Serial.println("PRESS q for stay.");
  Serial.println("PRESS x for bend.");
  Serial.println("PRESS z for shake legs.");
  Serial.println("PRESS e for moonwalk.");
  Serial.println("PRESS r for crusaito.");
  Serial.println("PRESS f for flapping.");
  Serial.println("PRESS c for swing.");
  Serial.println("PRESS t for swing 2");
  Serial.println("PRESS g for jitter.");
  Serial.println("PRESS b for updown.");
  Serial.println("PRESS y for ascending turn.");
  Serial.println("PRESS h for jump.");
  Serial.println("PRESS n for be happy.");
  Serial.println("PRESS u for ballet.");
  Serial.println("PRESS j for mixed 1");
  Serial.println("PRESS m for mixed 2");
  Serial.println("PRESS k for half tiptoe & waits too long");
  Serial.println("PRESS o for left foot tapping");
  Serial.println("PRESS l for stand like surfing");
}

void loop() {

  if ((Serial.available()) > (0)) {
    charRead = Serial.read();
  }
  if (((charRead) == ('w' ))) {
    Otto.walk(2,1000,1); //Steps, Speed, Move Forward
  }
  if (((charRead) == ('s' ))) {
    Otto.walk(2,1000,-1); //Steps, Speed, Move Backward
  }
  else if (((charRead) == ('a'))){
    Otto.turn(2,1000,1); //Turn Left, 3 Steps
  }
  else if (((charRead) == ('d'))){
    Otto.turn(2,1000,-1); //Turn Right
  }
  else if(((charRead) == ('q'))){
    Otto.home(); //Stay Home Position
  }
  else if(((charRead) == ('x'))){
    Otto.bend(1,500,1); //Left Foot
    Otto.bend(1,2000,-1); //Right Foot
  }
  else if(((charRead) == ('z'))){
    Otto.shakeLeg(1,1500,1); //Left Foot
    Otto.home();
    delay(100);
    Otto.shakeLeg(1,2000,-1); //Right Foot
  }
  else if(((charRead) == ('e'))){
    Otto.moonwalker(3,1000,25,1); //Left to Right
    Otto.moonwalker(3,1000,25,-1);  //Right to Left
  }
  else if(((charRead) == ('r'))){
    Otto.crusaito(2,1000,20,1); //Left Foot
    Otto.crusaito(2,1000,20,-1); //Right Foot    
  }
  else if(((charRead) == ('f'))){
    Otto.flapping(2,1000,20,1); //Forwards
    Otto.flapping(2,1000,20,-1); //Backwards
  }
  else if(((charRead) == ('c'))){
    Otto.swing(2,1000,20); //Swing
  }
  else if(((charRead) == ('t'))){
    Otto.tiptoeSwing(2,1000,20); //Swing but Another Movement
  }
  else if(((charRead) == ('g'))){
    Otto.jitter(2,1000,20); //Jitter move
  }
  else if(((charRead) == ('b'))){
    Otto.updown(2,1500,20); //Updown
  }
  else if(((charRead) == ('y'))){
    Otto.ascendingTurn(2,1000,50);
  }
  else if(((charRead) == ('h'))){
    Otto.jump(1,500); //It Does not Really Jump LOL
  }
  else if(((charRead) == ('n'))){
    Otto.playGesture(OttoHappy);
  }
  else if(((charRead) == ('u'))){
    Otto.playGesture(OttoSad); //Tiptoe Like a Ballerina;
  }
  else if(((charRead) == ('j'))){
    Otto.playGesture(OttoVictory); //Mixed Things
  }
  else if(((charRead) == ('m'))){
    Otto.playGesture(OttoAngry); //Mixed Things
  }
  else if(((charRead) == ('k'))){
    Otto.playGesture(OttoSleeping); //Half Tiptoe & Waits Too Long
  }
  else if(((charRead) == ('o'))){
    Otto.playGesture(OttoFretful); //Left Foot Tapping
  }
  else if(((charRead) == ('l'))){
    Otto.playGesture(OttoFail); //Stands Like Surfing
  }
}

void calib_homePos() {
  int servoPos[4];
  servoPos[0] = 90;
  servoPos[1] = 90;
  servoPos[2] = 90;
  servoPos[3] = 90;
  Otto._moveServos(500, servoPos);
  Otto.detachServos();
}
