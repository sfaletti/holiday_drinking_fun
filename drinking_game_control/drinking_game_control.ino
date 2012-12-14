/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 * Many thanks to DrLuke at Bldr for the shift register code!!!
 */

int SER_Pin = 3;   //pin 14 on the 75HC595
int RCLK_Pin = 2;  //pin 12 on the 75HC595
int SRCLK_Pin = 1; //pin 11 on the 75HC595

byte player1Val, player2Val;
byte score[] = {0,0};
byte winnerVal; // 0=newround, 1=roundstarted, 2=p1wins, 3=p2wins
boolean winnerFlag = false;
unsigned long blinkCounter;

//How many of the shift registers - change this
const int number_of_74hc595s = 4;

//do not touch
const int numOfRegisterPins = number_of_74hc595s * 8;

//initialize button pins
const int BTN_PINS[] = {
  12, 13, 14, 15, 16, 17, 18, 19};

//initialize speaker pin
const int speakerPin = 4;

boolean registers[numOfRegisterPins]; //32 total pins

void setup(){
  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  }  
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  winnerVal = 0;

  blinkCounter = 0;

  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

void loop(){
  switch (winnerVal){
    case 0:
    startRound();
    break;
    case 1:
    //carry on playing this round
    break;
    case 2:
    updateScore(0);
    break;
    case 3:
    updateScore(1);
    break;
  }
  
  if (winnerFlag) {
    
  }
  
  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}






