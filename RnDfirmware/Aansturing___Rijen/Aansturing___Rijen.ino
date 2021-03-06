// Programma Aansturing_BoebotB
// Hierin schrijf ik hoe ik de Servo aanstur zonder Servo.h.

// WriteMicroseconds (1500) = stil.
// pin 11 = left servo.
// pin 10 = right servo (inverted, 1400 = forward).

int servoLeft = 11;
int servoRight = 10;
float sVal0;




void setup() {
  Serial.begin(9600);
  
  // Initialize servoLeft and servoRight.
  pinMode(servoLeft, OUTPUT);
  pinMode(servoRight, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(51, OUTPUT);
}
 

void loop() {



//if(sVal0<15 && sVal0>0){
//  digitalWrite(51,HIGH);
//}
//else{
//  digitalWrite(51,LOW);
//}

UltraDetectie();
Serial.println(sVal0);
if((sVal0<15.59) && (sVal0>0)){
  Drive (1400, 1600);
}
else if(sVal0>15.59){
  Drive (1600, 1400);
}
else if(sVal0==15.59){
  Drive (1500,1500);
}
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
    digitalWrite(servoLeft, LOW);
    delayMicroseconds(timeR-timeL);
    digitalWrite(servoRight, LOW);
  }
  
  // Delay of 20 ms.
  delay(20);
}

void UltraDetectie(){
digitalWrite(7,HIGH);
delayMicroseconds(10);
digitalWrite(7,LOW);
delayMicroseconds(10);

sVal0 = pulseIn(8, HIGH);
sVal0 = sVal0/58;
//delay(10);
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
