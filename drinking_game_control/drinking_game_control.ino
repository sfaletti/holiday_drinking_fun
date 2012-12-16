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
const int START_BTN = 3;
const int SOL_VALVE[] = {
  5, 6};
const int SET_BTN = 9;
const int POUR_SET_BTN = 10;

unsigned long pourStartTime;
int pourTime;

byte player1Val, player2Val;
byte score[] = {
  0,0};
byte winnerVal; // 0=no one, 1=p1, 2=p2

//state flags
boolean winnerFlag = false;
boolean isGamePlaying = false;
boolean isRoundStarted = false;
boolean isGameWon = false;

unsigned long roundStartTime;
int roundLength = 1000 * 5; //round limit: 5 seconds

//initialize button pins
const int BTN_PINS[] = {
  11, 12, 13, 14, 15, 16, 17, 18};

//initialize speaker pin
const int speakerPin = 20;

boolean registers[numOfRegisterPins]; //16 total pins, 8 indicator, 8 scoreboard

void setup(){
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

  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  } 
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(SET_BTN, INPUT_PULLUP);
  pinMode(POUR_SET_BTN, INPUT_PULLUP);
  pinMode(SOL_VALVE[0], OUTPUT);
  pinMode(SOL_VALVE[1], OUTPUT);

  winnerVal = 0;

  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

void loop(){
  if (digitalRead(START_BTN) == HIGH){
    isGamePlaying = true;
    startGame();
  }

  if (isGamePlaying){
    if(!isRoundStarted){
      isRoundStarted = true;
      roundStartTime = millis();
      startRound();
    }
    while (isRoundStarted){ //loop here until somebody hits a button
      //TODO add a time-based limit
      winnerVal = checkInput();
      if (winnerVal > 0){
        isRoundStarted = false;
        updateScore(winnerVal);
        winnerVal = 0;
        break;
      }
      else if (millis() - roundStartTime >= roundLength){
        isRoundStarted = false;
        roundFailed();
        break;
      }
    }
    if (isGameWon){  
      if (millis() - pourStartTime >= pourTime){
        isGameWon = false;
        isRoundStarted = false;
        isGamePlaying = false;
        pourShot(winnerVal-1, false);
      }
      else {
        declareWinner(winnerVal);
        pourShot(winnerVal-1, true);
      }
      writeRegisters();
    }
  }
  else { // isGamePlaying is false 
    //TODO add base "beckoning" state
  }
}















