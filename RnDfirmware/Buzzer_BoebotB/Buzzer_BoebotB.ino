const int buzzer = 9; // Pin 9 for buzzer.
int distance = 30; // Random value for testing purposes, pretending to have distance.
int frequency; // Frequency variable.

void setup() {
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  // Reset distance, testing purposes.
  if(distance == 0){
    distance = 31;
  }
  
  // Increase the time of the sound when driving backward, testing purposes.
  else if(distance == 1){
    delay(500);
  }
  
  // Increase the time of the sound when not driving, testing purposes.
  else if(distance == 10){
    delay(500);
  }
  
  // Count down.
  distance--;

  // Run the function.
  playSound();

  // Delay for testing purposes.
  delay(100);
  
}

// Function playSound is just a copy of distance checking, but the driving is replaced with sounds.
// Just copy paste the tone and frequency lines in the function and you're good to go. 
void playSound(){
  if((distance >= 10) && (distance <= 12)){
    // Stop servos.
    frequency = 1350; // High tone when standing still.
    tone(buzzer, frequency);
  }
  else if(distance < 10){
    // Drive backward
    frequency = 700; // Lower tone when going backward.
    tone(buzzer, frequency);
  }
  // No sound when driving forward.
  else if(distance > 12){
    noTone(buzzer);
  }
}

