void startGame(){
  clearRegisters();
  startRound();
}

void startRound(){
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = int(random(0, 4)); //generate random value for player1 
  player2Val = int(random(4, 8)); //generate random value for player2 
  for (int i=0; i<8; i++){
    setRegisterPin(i, LOW);
  }
  setRegisterPin(player1Val, HIGH);
  setRegisterPin(player2Val, HIGH);
}

void checkInput(){
  for (int i=0; i<8; i++){
    if (digitalRead(BTN_PINS[i]) == LOW){
      if (i < 4) {
        updateScore(0);
        break;
      }
      else {
        updateScore(1);
        break;
      }
    }
  }
}

void updateScore(int _winner){
  score[_winner]++; //update score values
  if (_winner == 0) { //p1 won this round, update scoreboard
    registers[score[0] + 8] = true;
  }
  else { //p2 won, update scoreboard
    registers[score[1] + 12] = true;
  }
  isRoundStarted = false;
  if (score[_winner] == 4){
    isGameWon = true;
    isGamePlaying = false;
    winnerVal = _winner + 1;
  }
}

void declareWinner(int _winner){
  pourShot(_winner);
  for (int i=0; i<16; i++){
    registers[i] = true;
  }

}

void pourShot(int _winner){
  
}

void setPour(){
}






