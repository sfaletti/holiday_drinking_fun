/*
 * Holiday Drinking Game
 * Bottle Controller - this code takes input from whatever game is set up
 * and controls the solenoid valves
 * SVA IxD MFA, Physical Computing
 * Fall 2012
 * Steve Faletti, Tyler Davidson
 * December 2012
*/

// solenoid valve control pins and variables
const int SOLOUT_1 = 5;
const int SOLOUT_2 = 6;
int solVal = 0;

//test and calibrate pins
const int TIME_ADJUST_PIN = A0;
int timeVal = 0;
const int TEST_BTN = 8;
const int TEST_LED = 7;
boolean testBtnVal = true;

//timing variable
unsigned long prevMillis;

void setup(){
  Serial.begin(9600);
  pinMode(SOLOUT_1, OUTPUT);
  pinMode(SOLOUT_2, OUTPUT);
  pinMode(TEST_LED, OUTPUT);
  pinMode(TEST_BTN, INPUT_PULLUP);  
  prevMillis = millis();
}

void loop(){
  timeVal = analogRead(TIME_ADJUST_PIN);
  timeVal = map(timeVal, 0, 1023, 0, 5000); // how should we set the pour time? Do we need better feedback?
  testBtnVal = digitalRead(TEST_BTN);
  if (solVal > 0){
    switch (solVal){
    case 1:
      digitalWrite(SOLOUT_1, HIGH);
      delay(timeVal);
      digitalWrite(SOLOUT_1, LOW);
      break;
    case 2:
      digitalWrite(SOLOUT_2, HIGH);
      delay(timeVal);
      digitalWrite(SOLOUT_2, LOW);
      break;
    }
    solVal = 0; //reset solenoid value 
    prevMillis = millis(); //reset timer for next test button press
  }
  else if (!testBtnVal){ //button is pressed
    if (millis()-prevMillis > 30){ //button debounced, run test sequence
      digitalWrite(TEST_LED, HIGH);
      digitalWrite(SOLOUT_1, HIGH);
      delay(timeVal);
      digitalWrite(SOLOUT_1, LOW);
      delay(500);
      digitalWrite(SOLOUT_2, HIGH);
      delay(timeVal);
      digitalWrite(SOLOUT_2, LOW);
      digitalWrite(TEST_LED, LOW);
      prevMillis = millis(); //reset timer for next test button press
    }
  }
  else {
    prevMillis = millis(); //reset timer for next test button press
  }
}

void serialEvent(){
  solVal = Serial.read(); //should be a 1 or 2 to trigger the pouring sequence
  //TODO account for dropped data packets. async communication so only one packet sent
}
