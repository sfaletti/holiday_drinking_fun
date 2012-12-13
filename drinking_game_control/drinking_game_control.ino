/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 */

const int CLOCK_PIN = 0;
const int REG_PIN = 0;
const int SCORE_PIN = 0;
const int DISP1_PIN = 0;
const int DISP2_PIN = 0;
const int GAME_PIN = 0;

const byte BTN_PINS[] = {
  12, 13, 14, 15, 16, 17, 18, 19};
int player1Val, player2Val;

byte disp1Val = 0;
byte disp2Val = 0;
byte score1Val, score2Val;
byte scoreVal = 0;


void setup(){
  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  }  
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(REG_PIN, OUTPUT);
  pinMode(SCORE_PIN, OUTPUT);
  pinMode(DISP1_PIN, OUTPUT);
  pinMode(DISP2_PIN, OUTPUT);
}

void loop(){
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = byte(random(0, 4)); //generate random value for player1 
  player2Val = byte(random(4, 8)); //generate random value for player2
  byte gameVal = 1 << player1Val | 1 << player2Val; //save play pins in a byte

  

  // blink player1 and player2 lights using random values
  digitalWrite(REG_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  for (byte mask = 00000001; mask > 0; mask <<= 1){
    digitalWrite(GAME_PIN, gameVal & mask);
    digitalWrite(SCORE_PIN, scoreVal & mask);
    digitalWrite(DISP1_PIN, disp1Val & mask);
    digitalWrite(DISP2_PIN, disp2Val & mask);
    digitalWrite(CLOCK_PIN, HIGH);
  }
  digitalWrite(REG_PIN, HIGH); //

  //check button input
  switch (winnerVal(player1Val, player2Val)){
  case 0:
    break; //no winner, rerun button scan
  case 1:
    //TODO: player 1 wins
    break;
  case 2:
    //TODO: player 2 wins
    break;
  }
}

int winnerVal(int _player1, int _player2){ //scrub buttons and check which was pressed
  int winVal;
  for (int i=0; i<8; i++){ 
    if (digitalRead(BTN_PINS[i]) == LOW){ //button is pressed
      if (i == player1Val || i == player2Val){ //check that button pressed equals the target
        if(i < 4){
          winVal = 1; //player1 wins
          score1Val ++;
          break;
        }
        if(i >= 4){
          winVal = 2; //player2 wins
          score2Val ++;
          break;
        }
      }
      else winVal = 0;
    }
  }
  return winVal;
}











