void startRound(){
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = int(random(0, 4)); //generate random value for player1 
  player2Val = int(random(4, 8)); //generate random value for player2 
  for (int i=0; i<8; i++){ //first 8 registers are for button lights
    setRegisterPin(i, LOW);
  }
  clearRegisters();
  setRegisterPin(player1Val, HIGH);
  setRegisterPin(player2Val, HIGH);
  winnerVal = 1; //round started
}

void updateScore(int _winner){
  score[_winner]++; //update score values
  if (_winner == 0) { //p1 won this round, update scoreboard
    registers[score[0] + 8] = true;
  }
  else { //p2 won, update scoreboard
    registers[score[1] + 12] = true;
  }
  if (score[_winner] == 4){
    winnerFlag(_winner+1);
}

void declareWinner(int _winner){
  pourShot(_winner, true);
  for (int i=0; i<16; i++){
    registers[i] = true;
  }
}

void pourShot(int _winner, boolean on){
  //TODO get solenoid control code in here, no delays
}



