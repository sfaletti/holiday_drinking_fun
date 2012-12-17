void startGame(){
  clearRegisters();
  score[0] = 0;
  score[1] = 0;
}

void startRound(){
  isRoundWon = false;
  delay(random(1000, 3000));
  randomSeed(analogRead(21)); //seed random value generator from open pin
  player1Val = int(random(0, 4)); //generate random value for player1
  Serial.print("p1: ");
  Serial.println(player1Val); 
  player2Val = int(random(4, 8)); //generate random value for player2 
  Serial.print("p2: ");
  Serial.println(player2Val);
  for (int i=0; i<8; i++){ //clear button lights
    setRegisterPin(i, LOW);
  }
  setRegisterPin(player1Val, HIGH);
  setRegisterPin(player2Val, HIGH);
}

void checkInput(){
  for (int i=0; i<8; i++){
    if (digitalRead(BTN_PINS[i]) == LOW && !isRoundWon){
      if (i == player1Val || i == player2Val){
        for (int i=0; i<8; i++){
          setRegisterPin(i, LOW);
        }
        isRoundWon = true;
        if (i < 4) { //player 1 wins round
          Serial.println("player 1 wins round");
          winnerVal = 1;
          gameState = 1;
          updateScore(winnerVal);
          break; 
        }
        else { //player 2 wins round
          Serial.println("player 2 wins round");
          winnerVal = 2;
          gameState = 1;
          updateScore(winnerVal);
          break;
        }
      }
    }
    else { //no one has hit yet
      winnerVal = 0;
    }
  }
}

void updateScore(int _winner){
  score[_winner-1]++; //update score values
  if (_winner == 1) { //p1 won this round, update scoreboard
    registers[score[0] + 7] = true;
  }
  else if (_winner == 2) { //p2 won, update scoreboard
    registers[score[1] + 11] = true;
  }
  if (score[_winner-1] == 4){ //whoever won hit 4 points
    gameState = 3;
    declareWinner(_winner);
  }
}

void declareWinner(int _winner){
  clearRegisters();
  for (int o=0; o<5; o++){
    if (_winner == 1){
      for (int i=0; i<4; i++){
        setRegisterPin(i, HIGH);
      }
      for (int i=8; i<12; i++){
        setRegisterPin(i, HIGH);
      }
    }
    else if(_winner == 2){
      for (int i=4; i<8; i++){
        setRegisterPin(i, HIGH);
      }
      for (int i=12; i<16; i++){
        setRegisterPin(i, HIGH);
      }
    }
    writeRegisters();
    delay(400);
    clearRegisters();
    writeRegisters();
    delay(400);
  }
  pourShot(_winner-1);
}

void pourShot(int valve){
  digitalWrite(SOL_VALVE[valve], HIGH);
  delay(pourTime);
  digitalWrite(SOL_VALVE[valve], LOW);
}

void setPour(){ //TODO
}























