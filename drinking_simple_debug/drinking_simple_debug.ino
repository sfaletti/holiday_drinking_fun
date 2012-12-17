const int SER_Pin = 2;   //pin 14 on the 75HC595
const int RCLK_Pin = 1;  //pin 12 on the 75HC595
const int SRCLK_Pin = 0; //pin 11 on the 75HC595
const int number_of_74hc595s = 2; //total number of shift registers
const int numOfRegisterPins = number_of_74hc595s * 8;
boolean registers[numOfRegisterPins]; //16 total pins, 8 indicator, 8 scoreboard
const int START_BTN = 3;

//initialize button pins
const int BTN_PINS[] = {
  11, 12, 13, 14, 15, 16, 17, 18};

void setup(){
   for (int i=0; i<8; i++){
    pinMode(BTN_PINS[i], INPUT_PULLUP);
  } 
  clearRegisters();
  writeRegisters();
  Serial.begin(9600);
}
void loop(){
  for (int i=0; i<8; i++){
    if (digitalRead(BTN_PINS[i]) == LOW){
      clearRegisters();
      setRegisterPin(i, HIGH);
      break;
    }
  }
  writeRegisters();
}


//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    registers[i] = LOW;
  }
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){
  digitalWrite(RCLK_Pin, LOW);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    int val = registers[i];
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}



