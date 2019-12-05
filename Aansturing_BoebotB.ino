// Programma Aansturing_BoebotB
// Hierin schrijf ik hoe ik de Servo aanstur zonder Servo.h.

// WriteMicroseconds (1500) = stil.
// pin 11 = left servo.
// pin 10 = right servo (inverted, 1400 = forward).

int servoLeft = 11;
int servoRight = 10;

void Drive (int timeL, int timeR); // Prototype for the drive function for the Boe-Bot.

void setup() {
  Serial.begin(9600);
  
  // Initialize servoLeft and servoRight.
  pinMode(servoLeft, OUTPUT);
  pinMode(servoRight, OUTPUT);
}

void loop() {

  Drive(1600, 1400);

//  servoL.writeMicroseconds(1600);
//  servoR.writeMicroseconds(1400);
//  delay(500);
//  servoL.writeMicroseconds(1400);
//  servoR.writeMicroseconds(1600);
//  delay(500);

}

// Drive function for giving the servo's the correct time to turn on and off based on their given timers. This allows the vehicle to drive with no limits.
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
