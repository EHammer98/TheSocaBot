// Programma Aansturing_BoebotB
// Hierin schrijf ik hoe ik de Servo aanstuur zonder Servo.h.
// Onurcan Cekem
// 28/11/2019

// WriteMicroseconds (1500) = stil.
// pin 11 = left servo.
// pin 10 = right servo (inverted, 1400 = forward).

int servoLeft = 11;
int servoRight = 10;

void Drive (int timeL, int timeR); // Prototype for the Drive function for the Boe-Bot.
void Stilstaan(); // Prototype for the Stilstaan function.
void Rechtdoor(); // Prototype for the Rechtdoor function.
void Links(); // Prototype for the Links function.
void Rechts(); // Prototype for the Rechts function.
void ScherpLinks(); // Prototype for the ScherpLinks function.
void ScherpRechts(); // Prototype for the ScherpRechts function.

void setup() {
  Serial.begin(9600);
  
  // Initialize servoLeft and servoRight.
  pinMode(servoLeft, OUTPUT);
  pinMode(servoRight, OUTPUT);
}

void loop() {

  Drive(1600, 1400);


}

// Drive function for giving the servo's the correct time to turn on and off based on their given timers. This allows the vehicle to drive with no limits.
// The values given should be between 1000-2000 in order to work properly.
void Drive (int timeL, int timeR){
  
  // If the time is equal then there is no need to do timeL - timeR.
  if(timeL == timeR){
    digitalWrite(servoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoRight, LOW);
    digitalWrite(servoLeft, LOW);
  }
  
  // If timeL is greater than timeR then turn servoR low faster.
  else if(timeL > timeR){
    digitalWrite(servoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeR);
    digitalWrite(servoRight, LOW);
    delayMicroseconds(timeL-timeR);
    digitalWrite(servoLeft, LOW);
  }

  // If timeR is greater than timeR then turn servoL low faster.
  else if(timeL < timeR){
    digitalWrite(servoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoRight, LOW);
    delayMicroseconds(timeR-timeL);
    digitalWrite(servoLeft, LOW);
  }
  
  // Delay of 20 ms.
  delay(20);
}

// Working basic function.
//void Drive (int t){
//  digitalWrite(servoLeft, HIGH);
//  digitalWrite(servoRight, HIGH);
//  delayMicroseconds(t);
//  digitalWrite(servoLeft, LOW);
//  digitalWrite(servoRight, LOW);
//  delay(20);
//}

// Function to stay put.
void Stilstaan(){
  Drive (1500, 1500);
}

// Function to drive forward.
void Rechtdoor(){
  Drive (1600, 1400);
}

// Function to turn left.
void Links(){
  Drive (1500, 1400);
}

// Function to turn right.
void Rechts(){
  Drive (1600, 1500);
}

// Function to turn sharp left.
void ScherpLinks(){
  Drive (1600, 1600);
}

// Function to turn sharp right.
void ScherpRechts(){
  Drive (1400, 1400);
}
