/*
 * Holiday Drinking Game
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
 */

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

const int SLCRK_PIN = 1;
const int RCLK_PIN = 2;
const int SCORE_PIN = 0;
const int DISP1_PIN = 0;
const int DISP2_PIN = 0;
const int SER_PIN = 3;

const byte BTN_PINS[] = {
  12, 13, 14, 15, 16, 17, 18, 19};
int player1Val, player2Val;

byte disp1Val = 0;
byte disp2Val = 0;
byte score1Val = B00000000;
byte score2Val = B00001000;
byte scoreVal = 0;


void setup(){
//  for (int i=0; i<8; i++){
//    pinMode(BTN_PINS[i], INPUT_PULLUP);
//  }  
  pinMode(SLCRK_PIN, OUTPUT);
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(SCORE_PIN, OUTPUT);
  pinMode(DISP1_PIN, OUTPUT);
  pinMode(DISP2_PIN, OUTPUT);

  pinMode(5, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop(){
  if (digitalRead(5) == LOW){
    randomSeed(analogRead(21)); //seed random value generator from open pin
    player1Val = int(random(0, 4)); //generate random value for player1 
    Serial.print(player1Val);
    Serial.print(", ");
    player2Val = int(random(4, 8)); //generate random value for player2
    Serial.print(player2Val);
    Serial.println();
  }
  clearRegisters();

  setRegisterPin(2, HIGH);
  setRegisterPin(5, HIGH);

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

  digitalWrite(RCLK_PIN, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SLCRK_PIN, LOW);

    int val = registers[i];

    digitalWrite(SER_PIN, val);
    digitalWrite(SLCRK_PIN, HIGH);

  }
  digitalWrite(RCLK_PIN, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}












