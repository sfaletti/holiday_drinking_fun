void startGame(){
  clearRegisters();
}

void startRound(){
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = int(random(0, 4)); //generate random value for player1 
  player2Val = int(random(4, 8)); //generate random value for player2 
  for (int i=0; i<8; i++){ //clear button lights
    setRegisterPin(i, LOW);
  }
  setRegisterPin(player1Val, HIGH);
  setRegisterPin(player2Val, HIGH);
}

int checkInput(){
  for (int i=0; i<8; i++){
    if (digitalRead(BTN_PINS[i]) == LOW){
      Serial.println("a button was pressed");
      if (i == player1Val || i == player2Val){
        if (i < 4) { //player 1 wins round
          Serial.println("player 1 wins round");
          updateScore(1);
          return 1; //return p1 to winnerVal
        }
        else { //player 2 wins round
        Serial.println("player 2 wins round");
          updateScore(2);
          return 2; //return p2 to winnerVal
        }
      }
    }
    else { //no one has hit yet
      return 0;
    }
  }
}

void updateScore(int _winner){
  score[_winner]++; //update score values
  gameState = 1;
  if (_winner == 1) { //p1 won this round, update scoreboard
    registers[score[0] + 8] = true;
  }
  else if (_winner == 2) { //p2 won, update scoreboard
    registers[score[1] + 12] = true;
  }
  if (score[_winner] == 4){ //whoever won hit 4 points
    gameState = 3;
  }
}

void roundFailed(){

}

void declareWinner(int _winner){
  for (int i=0; i<16; i++){
    registers[i] = true;
  }

}

void pourShot(int valve, boolean openValve){
  digitalWrite(SOL_VALVE[valve], openValve);
}

void setPour(){
}















