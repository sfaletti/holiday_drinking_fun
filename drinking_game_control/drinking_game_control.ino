/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 */

const byte BTN_PINS[] = {
  12, 13, 14, 15, 16, 17, 18, 19};
int winPin = 0; //0=no winner, 1=player1 wins, 2=player2 wins
int player1Val, player2Val;

void setup(){
  for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  }  
}

void loop(){
  randomSeed(analogRead(21)); //seed random value generator
  player1Val = int(random(0, 4)); //generate random value for player1 
  player2Val = int(random(4, 8)); //generate random value for player2

  //TODO blink player1 and player2 lights using random values

  for (int i=0; i<8; i++){ //scrub buttons and check which was pressed
    if (digitalRead(BTN_PINS[i]) == LOW){ //button is pressed
      if (i == player1Val || i == player2Val){ //check that button pressed equals the target
        if(i < 4){
          winPin = 1; //player1 wins
          break;
        }
        if(i >= 4){
          winPin = 2; //player2 wins
          break;
        }
      }
      else winPin = 0;
    }
  }
  switch (winPin){
  case 0:
    //TODO: no winner, rerun button scan
    break;
  case 1:
    //TODO: player 1 wins
    break;
  case 2:
    //TODO: player 2 wins
    break;
  }
}






