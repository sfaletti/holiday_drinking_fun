void startMelody(){

  tone(speakerPin,262);
  delay(100);
  tone(speakerPin,262);
  delay(100);
  tone(speakerPin,392);
  delay(100);
  tone(speakerPin,523);
  delay(300);
  tone(speakerPin,392);
  delay(100);
  tone(speakerPin,523);
  delay(300);
  noTone(speakerPin);
}

void pointMelody(){

  tone(speakerPin,262);
  delay(100);
  tone(speakerPin,392);
  delay(100);
  tone(speakerPin,523);
  delay(250);
  noTone(speakerPin);
  
}



