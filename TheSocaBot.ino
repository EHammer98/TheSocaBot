/*
  #############################################################
  #Firmware:           TheSocaBot                             #
  #Hardware:           Arduino Mega 2560                      #
  #Eerste opzet:       26-11-2019                             #
  #Auteurs: E. Hammer | N. Vollebregt | M. Remmig | O. Cekem  #
  #Laatst gewijzigd:   09-01-2020                             #
  #Versie:             1.0.7                                  #
  #############################################################

  ##WAT JE NIET MAG GEBRUIKEN##
  1.  Alle functies uit Servo.lib
  a.  attach()
  b.  write()
  c.  writeMicroseconds()
  d.  read()
  e.  attached()
  f.  detach()
  2.  Alle functies voor externe sensoren. Bijvoorbeeld:
  a.  De ping sensor
  b.  De Sharp afstand sensor
  c.  De accelerometrie sensoren
  3.  Eenvoudige functies voor bewerkingen
  a.  y = map(x, 1, 50, 50, 1);
  b.  Enz.
*/

//Zie OneDrive: Schemetics>Pins.txt
//LED pin's voor visuele feedback
int LED0 = 2;     //Afstand = gelijk aan threshold waarde
int LED1 = 3;     //IR LED('s)/LDR('s) links nemen iets waar
int LED2 = 4;     //IR LED('s)/LDR('s) rechts nemen iets waar
int LED3 = 5;     //IR LED('s)/LDR('s) alle of alleen voor iets waarnemen
int LED4 = 6;     //Laser wordt gedetecteerd
//Pins voor de ultrasonic afstand sensor
int ultraT = 7;   //Trigger pin voor de ultrasonic sensor
int ultraE = 8;   //Echo pin voor de ultrasonic sensor
//Speaker voor geluid feedback
int speaker = 9;  //Nog nader te bepalen
//Pins voor de servo-motoren
int servoR = 10;  //Servo voor rechts
int servoL = 11;  //Servo voor links
//Pins voor de LDR laser detectie sensoren
int LDR0 = A0;    //LDR voor
int LDR1 = A1;    //LDR rechter hoek voor
int LDR2 = A2;    //LDR rechter hoek achter
int LDR3 = A3;    //LDR linker hoek achter
int LDR4 = A4;    //LDR linker hoek voor
//Pins voor de IR LED's om de leader te detecteren
int IR0 = A5;     //IR links
int IR1 = A6;     //IR midden
int IR2 = A7;     //IR rechts
int IR3 = A8;     //*IR reserve*

//Thresholds
float thresholdDistance = 10.00;  //Drempelwaarde om de afstand mee te vergelijken (in CM)#5
int laserThreshold = 1000;   //Drempelwaarde om de laser mee te detecteren #950
int irThreshold = 512;      //Drempelwaarde om de leader (IR) mee te detecteren #512
int NumReadings = 10;

//Sensoren
int laserDetected = 0;      //0=geen|1=voor|2=rechtsVoor|3=rechtsAchter|4=linksAchter|5=linksVoor
int irDetected = 0;         //0=geen|1=links|2=front|3=right
int distance = 0;           //0=stop|1=checkLDR|2=reverse

void distanceCheck();     // Prototype for checking the distance.
void checkLDR();          //Prototype for detecting a laser function.
void laserDrive();        // Prototype for driving to the laser function.
char checkIR(void);           // Prototype for detecting IR (leader)function.
//void irDrive();           // Prototype for driving to the leader function.
void Drive (int timeL, int timeR);
void ServoStop();         // Prototype for the ServoStop function.
void ServoForward();      // Prototype for the ServoForward function.
void ServoTurnLeft();     // Prototype for the ServoTurnLeft function.
void ServoTurnRight();    // Prototype for the ServoTurnRight function.
void ServoSharpLeft();    // Prototype for the ServoSharpLeft function.
void ServoSharpRight();   // Prototype for the ServoSharpRight function.
void ServoBackward();     // Prototype for the ServoBackward function.

//Initializeren van de firmware
void setup() {
  Serial.begin(9600); //Start een serieële verbinding
  pinMode(LED0, OUTPUT);      //Defineer LED0 als een uitgang
  pinMode(LED1, OUTPUT);      //Defineer LED1 als een uitgang
  pinMode(LED2, OUTPUT);      //Defineer LED2 als een uitgang
  pinMode(LED3, OUTPUT);      //Defineer LED3 als een uitgang
  pinMode(LED4, OUTPUT);      //Defineer LED4 als een uitgang
  pinMode(ultraT, OUTPUT);    //Defineer ultraT als een uitgang
  pinMode(ultraE, INPUT);     //Defineer ultraE als een ingang
  pinMode(speaker, OUTPUT);   //Defineer speaker als een uitgang
  pinMode(servoR, OUTPUT);    //Defineer servoR als een uitgang
  pinMode(servoL, OUTPUT);    //Defineer servoL als een uitgang
  pinMode(LDR0, INPUT);       //Defineer LDR0 als een uitgang
  pinMode(LDR1, INPUT);       //Defineer LDR1 als een uitgang
  pinMode(LDR2, INPUT);       //Defineer LDR2 als een uitgang
  pinMode(LDR3, INPUT);       //Defineer LDR3 als een uitgang
  pinMode(LDR4, INPUT);       //Defineer LDR4 als een uitgang
  pinMode(IR0, INPUT);        //Defineer IR1 als een uitgang
  pinMode(IR1, INPUT);        //Defineer IR2 als een uitgang
  pinMode(IR2, INPUT);        //Defineer IR3 als een uitgang
  pinMode(IR3, INPUT);        //Defineer IR4 als een uitgang
}

void loop() {
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  distanceCheck();
 // delay(500); //DEBUG
}

void distanceCheck(void) {
  //AFSTAND SENSOR CHECKEN//
  float distanceCM;
  digitalWrite(ultraT, HIGH);               //Pulse starten
  delayMicroseconds(10);
  digitalWrite(ultraT, LOW);                //Pulse stoppen
  delayMicroseconds(10);
  distanceCM = pulseIn(ultraE, HIGH);       //Pulse terug uitlezen
  distanceCM = distanceCM / 58;             //Calculate to CM
  Serial.println("Distance:");
  Serial.println(distanceCM);
//  delay(500); //DEBUG
  if (distanceCM == thresholdDistance) {    //SFC 2.0
    ServoStop();
    loop();
  } else if (distanceCM > thresholdDistance) { //SFC 2.1
    checkLDR();
  } else if(distanceCM < thresholdDistance) { //SFC 2.2
    ServoBackward();
    Serial.println("REVERSING....");
   // delay(500); //DEBUG
    loop();
  } 
}


void checkLDR() { //SFC 2.1
  //DEBUG
  Serial.println("LDR0: ");
  Serial.println(analogRead(LDR0)); //Links voor
  Serial.println("LDR1: ");
  Serial.println(analogRead(LDR1)); //Voor
  Serial.println("LDR2: ");
  Serial.println(analogRead(LDR2)); //Rechts voor
  Serial.println("LDR3: ");
  Serial.println(analogRead(LDR3)); //Rechts achter
  Serial.println("LDR4: ");
  Serial.println(analogRead(LDR4)); //Links achter
//  delay(500); //DEBUG
  //LASER DETECTIE
  if (analogRead(LDR0) >= laserThreshold) {
    laserDetected = 1; //voor
    laserDrive(); //SFC 5
  } else if (analogRead(LDR1) >= laserThreshold) {
    laserDetected = 2; //Rechts voor
    laserDrive(); //SFC 5
  } else if (analogRead(LDR2) >= laserThreshold) {
    laserDetected = 3; //Rechts achter
    laserDrive(); //SFC 5
  } else if (analogRead(LDR3) >= laserThreshold) {
    laserDetected = 4; //Links achter
    laserDrive(); //SFC 5
  } else if (analogRead(LDR4) >= laserThreshold) {
    laserDetected = 5;  //Links voor
    laserDrive(); //SFC 5
  } else {
      laserDetected = 0; //Geen laser
      char IRsensorOutput = checkIR();
      irDrive(IRsensorOutput); //SFC 3
  }
  //delay(500);        // delay in between reads for stability
}

void laserDrive() { //SFC 5
  digitalWrite(LED4, HIGH);
  switch (laserDetected) {
    case 0: //SFC 5.0
      break;
    case 1:
      Serial.println("VOOR");
      digitalWrite(LED3, HIGH);
      ServoForward(); // Boe-Bot gaat naar voren
      break;
    case 2:
      Serial.println("RECHTSvoor");
      digitalWrite(LED2, HIGH);
      ServoTurnRight(); // Boe-Bot draait naar rechts    
      break;
    case 3:
      Serial.println("RECHTSachter");
      digitalWrite(LED2, HIGH);
      ServoTurnRight(); // Boe-Bot draait naar rechts   
      break;
    case 4:
      Serial.println("LINKSachter");
      digitalWrite(LED1, HIGH);
      ServoTurnLeft(); //Boe-Bot draait naar links    
      break;
    case 5:
      Serial.println("LINKSvoor");
      digitalWrite(LED1, HIGH);
      ServoTurnLeft(); //Boe-Bot draait naar links
      break;
  }
  //delay(500); //DEBUG
}

char checkIR(void) { //SFC 3
  //DEBUG
  Serial.println("IR0: ");
  Serial.println(analogRead(IR0)); //IR links uitlezen
  Serial.println("IR1: ");
  Serial.println(analogRead(IR1)); //IR voor uitlezen
  Serial.println("IR2: ");
  Serial.println(analogRead(IR2)); //IR rechts uitlezen
 // delay(500);
  //IR DETECTIE
    int IRvalue_l = 0; // een array voor elke IR sensor: (l)inks, (m)idden en (r)echts
  int IRvalue_m = 0;
  int IRvalue_r = 0;
  
// Inverteert de waardes van de sensoren zodat detectie = hoge waarde
  IRvalue_l = 1024 - analogRead(IR0);
  IRvalue_m = 1024 - analogRead(IR1);
  IRvalue_r = 1024 - analogRead(IR2);
  
 char ReturnValue_IR;
 
if(IRvalue_l > irThreshold || IRvalue_m > irThreshold || IRvalue_r > irThreshold)
  {
    if(IRvalue_l > irThreshold) ReturnValue_IR |= 0x01; else ReturnValue_IR &= ~(0x01);
    if(IRvalue_m > irThreshold) ReturnValue_IR |= 0x02; else ReturnValue_IR &= ~(0x02);
    if(IRvalue_r > irThreshold) ReturnValue_IR |= 0x04; else ReturnValue_IR &= ~(0x04);
  }
  return ReturnValue_IR;
}
void irDrive(char LEDs)
{
  switch(LEDs)
  {
    case 0x01:
    {
      Serial.println("LINKS");
      digitalWrite(LED1, HIGH);
      ServoSharpLeft();
    }
    break;
  
    case 0x02:
    {
     Serial.println("VOOR");
      digitalWrite(LED3, HIGH);
      ServoForward();
    }
    break;

    case 0x03:
    {
      Serial.println("LINKS");
      digitalWrite(LED1, HIGH);
      ServoSharpLeft();
    }
    break;
  
    case 0x04:
    {
      Serial.println("RECHTS");
      digitalWrite(LED2, HIGH);
      ServoSharpRight();
    }
    break;

    case 0x06:
    {
      Serial.println("RECHTS");
      digitalWrite(LED2, HIGH);
      ServoSharpRight();
    }
    break;

    case 0x07:
    {
      Serial.println("VOOR");
      digitalWrite(LED3, HIGH);
      ServoForward();
    }
    default:
      Serial.println("GEEN ir, rondje");
      ServoTurnLeft();
    break;
  }
//  delay(500); // DEBUG
}

// Drive function for giving the servo's the correct time to turn on and off based on their given timers. This allows the vehicle to drive with no limits.
// The values given should be between 1000-2000 in order to work properly.
void Drive (int timeL, int timeR){
  
  // If the time is equal then there is no need to do timeL - timeR.
  if(timeL == timeR){
    digitalWrite(servoL, HIGH);
    digitalWrite(servoR, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoR, LOW);
    digitalWrite(servoL, LOW);
  }
  
  // If timeL is greater than timeR then turn servoR low faster.
  else if(timeL > timeR){
    digitalWrite(servoL, HIGH);
    digitalWrite(servoR, HIGH);
    delayMicroseconds(timeR);
    digitalWrite(servoR, LOW);
    delayMicroseconds(timeL-timeR);
    digitalWrite(servoL, LOW);
  }

  // If timeR is greater than timeR then turn servoL low faster.
  else if(timeL < timeR){
    digitalWrite(servoL, HIGH);
    digitalWrite(servoR, HIGH);
    delayMicroseconds(timeL);
    digitalWrite(servoL, LOW);
    delayMicroseconds(timeR-timeL);
    digitalWrite(servoR, LOW);
  }
  
  // Delay of 20 ms.
  delay(22);
}

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

// Function to drive backward.
void ServoBackward(){
  Drive (1400, 1600);
}
