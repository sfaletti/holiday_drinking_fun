void setup(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  digitalWrite(5, HIGH);
  delay(6000);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(6000);
  digitalWrite(6, LOW);
  
}
