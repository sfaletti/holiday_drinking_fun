/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 */

const int CLOCK_PIN = 1;
const int REG_PIN = 2;
const int SCORE_PIN = 0;
const int DISP1_PIN = 0;
const int DISP2_PIN = 0;
const int GAME_PIN = 3;

const byte BTN_PINS[] = {
  12, 13, 14, 15, 16, 17, 18, 19};
int player1Val, player2Val;

byte disp1Val = 0;
byte disp2Val = 0;
byte score1Val = B00000000;
byte score2Val = B00001000;
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

  Serial.begin(9600);
}

void loop(){
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = byte(random(0, 4)); //generate random value for player1 
  Serial.print(player1Val);
  Serial.print(", ");
  player2Val = byte(random(4, 8)); //generate random value for player2
  Serial.print(player2Val);
  Serial.print(", ");
  byte gameVal = 1 << player2Val | 1 << player1Val; //save play pins in a byte
  Serial.println(gameVal, BIN);

  // blink player1 and player2 lights using random values
  digitalWrite(REG_PIN, LOW);
//  digitalWrite(CLOCK_PIN, LOW);
  for (byte mask = B00000001; mask > 0; mask <<= 1){
    digitalWrite(CLOCK_PIN, LOW);
    if(gameVal & mask){
      Serial.println("yes");
      digitalWrite(GAME_PIN, HIGH);
    }
    else {
      Serial.println("no");
      digitalWrite(GAME_PIN, LOW);
    }
//    digitalWrite(SCORE_PIN, scoreVal & mask);
//    digitalWrite(DISP1_PIN, disp1Val & mask);
//    digitalWrite(DISP2_PIN, disp2Val & mask);
    digitalWrite(CLOCK_PIN, HIGH);
  }
  digitalWrite(REG_PIN, HIGH); 
  delay(1000);

  //check button input
  switch (winnerVal(player1Val, player2Val)){
  case 0:
    break; //no winner, rerun button scan
  case 1:
    //TODO: player 1 wins
    score1Val <<= 1; //this is wrong
    break;
  case 2:
    //TODO: player 2 wins          
    score2Val <<= 1; //this is wrong
    break;
  }
  scoreVal = score1Val | score2Val; //this is wrong
}

int winnerVal(int _player1, int _player2){ //scrub buttons and check which was pressed
  int winVal;
  for (int i=0; i<8; i++){ 
    if (digitalRead(BTN_PINS[i]) == LOW){ //button is pressed
      if (i == player1Val || i == player2Val){ //check that button pressed equals the target
        if(i < 4){
          winVal = 1; //player1 wins
          break;
        }
        if(i >= 4){
          winVal = 2; //player2 wins
          break;
        }
      }
      else winVal = 0;
    }
  }
  return winVal;
}













