/*
Project name: MidiOutController
Created by: Cameron Huebner
First usable date: December 18th, 2015.
Description: This program makes MIDI program changes
*/

#include <EEPROM.h>

int footSwitch = 12;
int led = 7;
int fSState = 0;
int prevFSState = 0;

int globBank = 0;
int maxBanks = 99;

int delayLength = 50;

void setup() {
  //MIDI baud rate:
  Serial.begin(31250);
  
  //globBank = EEPROM.read(0);
  
  pinMode(footSwitch, INPUT); 
  pinMode(led, OUTPUT); 
}

void loop() {  
  fSState = digitalRead(footSwitch); 
  
  if (fSState != prevFSState)
  {
    globBank++;    
    if (globBank == maxBanks)
    {
      globBank = 0;
    }
    
    //Bank change and saving in eeprom
    Serial.write(0xC0);
    Serial.write(globBank);
    EEPROM.write(0, globBank);
    
    reset();
    flashLed();
  }
  delay(1);
}


void reset() {
  prevFSState = fSState; 
  pinMode(led, LOW);
}

void flashLed() {
  pinMode(led, HIGH);
  delay(delayLength);
  pinMode(led, LOW);
  delay(delayLength);
  pinMode(led, HIGH);
  delay(delayLength);
  pinMode(led, LOW);
  delay(delayLength);
  pinMode(led, HIGH);
  delay(delayLength);
}
