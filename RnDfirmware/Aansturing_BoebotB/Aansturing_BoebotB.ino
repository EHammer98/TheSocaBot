// Programma Aansturing_BoebotB
// Hierin schrijf ik hoe ik de Servo aanstuur zonder Servo.h.
// Onurcan Cekem
// 28/11/2019

// WriteMicroseconds (1500) = stay put.
// pin 11 = left servo.
// pin 10 = right servo (inverted, 1400 = forward).

int ServoLeft = 11;
int servoRight = 10;

void Drive (int timeL, int timeR); // Prototype for the Drive function for the Boe-Bot.
void ServoStop(); // Prototype for the ServoStop function.
void ServoForward(); // Prototype for the ServoForward function.
void ServoTurnLeft(); // Prototype for the ServoTurnLeft function.
void ServoTurnRight(); // Prototype for the ServoTurnRight function.
void ServoSharpLeft(); // Prototype for the ServoSharpLeft function.
void ServoSharpRight(); // Prototype for the ServoSharpRight function.

void setup() {
  Serial.begin(9600);
  
  // Initialize ServoLeft and servoRight.
  pinMode(ServoLeft, OUTPUT);
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
    digitalWrite(ServoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoRight, LOW);
    digitalWrite(ServoLeft, LOW);
  }
  
  // If timeL is greater than timeR then turn servoR low faster.
  else if(timeL > timeR){
    digitalWrite(ServoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeR);
    digitalWrite(servoRight, LOW);
    delayMicroseconds(timeL-timeR);
    digitalWrite(ServoLeft, LOW);
  }

  // If timeR is greater than timeR then turn servoL low faster.
  else if(timeL < timeR){
    digitalWrite(ServoLeft, HIGH);
    digitalWrite(servoRight, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoRight, LOW);
    delayMicroseconds(timeR-timeL);
    digitalWrite(ServoLeft, LOW);
  }
  
  // Delay of 20 ms.
  delay(20);
}

// Working basic function.
//void Drive (int t){
//  digitalWrite(ServoLeft, HIGH);
//  digitalWrite(servoRight, HIGH);
//  delayMicroseconds(t);
//  digitalWrite(ServoLeft, LOW);
//  digitalWrite(servoRight, LOW);
//  delay(20);
//}

// Function to stay put.
void ServoStop(){
  Drive (1500, 1500);
}

// Function to drive forward.
void ServoForward(){
  Drive (1600, 1400);
}

// Function to turn left.
void ServoTurnLeft(){
  Drive (1500, 1400);
}

// Function to turn right.
void ServoTurnRight(){
  Drive (1600, 1500);
}

// Function to turn sharp left.
void ServoSharpLeft(){
  Drive (1600, 1600);
}

// Function to turn sharp right.
void ServoSharpRight(){
  Drive (1400, 1400);
}
