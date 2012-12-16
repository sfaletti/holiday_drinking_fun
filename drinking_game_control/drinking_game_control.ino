#include <EEPROM.h>

/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 * Many thanks to DrLuke at Bldr for the shift register code!!!
 */

const int SER_Pin = 2;   //pin 14 on the 75HC595
const int RCLK_Pin = 1;  //pin 12 on the 75HC595
const int SRCLK_Pin = 0; //pin 11 on the 75HC595
const int number_of_74hc595s = 2; //total number of shift registers
const int numOfRegisterPins = number_of_74hc595s * 8;
const int START_BTN = 4;
const int SOLOUT_1 = 5;
const int SOLOUT_2 = 6;
const int SET_BTN = 9;

byte pourTime = EEPROM.read(0);

byte player1Val, player2Val;
byte score[] = {
  0,0};
byte winnerVal; // 0=newround, 1=roundstarted, 2=p1wins, 3=p2wins
boolean winnerFlag = false;
boolean isGamePlaying = false;
boolean isRoundStarted = false;
boolean isGameWon = false;

//initialize button pins
const int BTN_PINS[] = {
  11, 12, 13, 14, 15, 16, 17, 18};

//initialize speaker pin
const int speakerPin = 3;

boolean registers[numOfRegisterPins]; //16 total pins, 8 indicator, 8 scoreboard

void setup(){
  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  } 
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(SET_BTN, INPUT_PULLUP);
  pinMode(SOLOUT_1, OUTPUT);
  pinMode(SOLOUT_2, OUTPUT);

  winnerVal = 0;

  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

void loop(){
  if (digitalRead(START_BTN == HIGH) && !isGamePlaying){
    startGame();
    isGamePlaying = true;
  }

  if (isGamePlaying && !isRoundStarted) {
    startRound();
    isRoundStarted = true;
  }

  while (isGamePlaying && isRoundStarted) {
    checkInput();
  }

  if (isGameWon){  
    declareWinner(winnerVal - 1);
  }

  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
}







