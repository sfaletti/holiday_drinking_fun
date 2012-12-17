/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 * Many thanks to DrLuke at Bldr for the shift register code!!!
 */

#include <EEPROM.h>

const int SER_Pin = 2;   //pin 14 on the 75HC595
const int RCLK_Pin = 1;  //pin 12 on the 75HC595
const int SRCLK_Pin = 0; //pin 11 on the 75HC595
const int number_of_74hc595s = 2; //total number of shift registers
const int numOfRegisterPins = number_of_74hc595s * 8;
boolean registers[numOfRegisterPins]; //16 total pins, 8 indicator, 8 scoreboard
const int START_BTN = 3;
const int START_LIGHT = 19;
const int SOL_VALVE[] = {
  6, 5};
const int PURGE_BTN = 9;
const int POUR_SET_BTN = 10;

int pourTime;

byte player1Val, player2Val;
byte score[] = {
  0,0};
byte winnerVal; // 0=no one, 1=p1, 2=p2

//state flags
boolean winnerFlag = false;
boolean isGameStarting = false;
boolean isRoundStarting = false;
boolean isRoundPlaying = false;
boolean isGameWon = false;
boolean startState = true;

int gameState = 0;
boolean isRoundWon = false;

unsigned long prevMillis;
unsigned long purgeMillis;
int roundLength = 1000 * 5; //round limit: 5 seconds

//initialize button pins
const int BTN_PINS[] = {
  11, 12, 13, 14, 15, 16, 17, 18};

//initialize speaker pin
const int speakerPin = 20;

void setup(){
  Serial.begin(9600);
  if (word(EEPROM.read(0), EEPROM.read(1)) <= 0){ //set EEPROM to 1 second if it's blank
    int time = 1000;
    byte msb = highByte(time);
    byte lsb = lowByte(time);
    EEPROM.write(0, msb);
    EEPROM.write(1, lsb); 
  }
  byte _msb = EEPROM.read(0); //msb of pourTime
  byte _lsb = EEPROM.read(1); //lsb of pourTime
  pourTime = word(_msb, _lsb); //put the pour time in memory
  pourTime = 6000;

  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  } 
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(PURGE_BTN, INPUT_PULLUP);
  pinMode(POUR_SET_BTN, INPUT_PULLUP);
  pinMode(SOL_VALVE[0], OUTPUT);
  pinMode(SOL_VALVE[1], OUTPUT);
  pinMode(START_LIGHT, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  winnerVal = 0;

  //reset all register pins
  clearRegisters();
  writeRegisters();
  prevMillis = 0;
}               

void loop(){

  boolean startVal = digitalRead(START_BTN);
  if (startVal == LOW){
    if (millis() - prevMillis >= 1000){ //new game started
      Serial.println("start game");
      gameState = 1;
      digitalWrite(START_LIGHT, HIGH);
      startGame();
    }
  }
  else if (digitalRead(PURGE_BTN) == LOW){
    if (millis() - purgeMillis >= 1000){ //start purging
      gameState = 0;
      digitalWrite(SOL_VALVE[0], HIGH);
      digitalWrite(SOL_VALVE[1], HIGH);
      digitalWrite(START_LIGHT, HIGH);
      tone(speakerPin, 400, 200);
      delay(10000);
      digitalWrite(SOL_VALVE[0], LOW);
      digitalWrite(SOL_VALVE[1], LOW); 
      digitalWrite(START_LIGHT, LOW);
    }  
  }
  else if(startVal == HIGH){
    prevMillis = millis();
    purgeMillis = millis();
    switch(gameState){
    case 0:
      //      for(int i=0; i<16; i++){
      //        setRegisterPin(i, HIGH);
      //      }
      break;
    case 1: //new round started
      Serial.println("round started");
      gameState = 2;
      startRound();
      break;
    case 2: //playing round
      checkInput();
      break;
    case 3: //game won
      gameState = 0;
      digitalWrite(START_LIGHT, LOW);
      break;
    }
  }
  writeRegisters();  
}


































