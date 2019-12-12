/*
  #############################################################
  #Firmware:           TheSocaBot                             #
  #Hardware:           Arduino Mega 2560                      #
  #Eerste opzet:       26-11-2019                             #
  #Auteurs: E. Hammer | N. Vollebregt | M. Remmig | O. Cekem  #
  #Laatst gewijzigd:   03-12-2019                             #
  #Versie:             1.0.3                                  #
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
int thresholdDistance = 5;  //Drempelwaarde om de afstand mee te vergelijken (in CM)
int laserThreshold = 850;   //800
int irThreshold = 0;        //0

//Sensoren
int laserDetected = 0;      //0=geen|1=linksVoor|2=Voor|3=rechtsVoor|4=rechtsAchter|5=linksAchter
int irDetected = 0;         //0=geen|1=links|2=front|3=right
int distance = 0;           //0=stop|1=checkLDR|2=reverse
//Initializeren van de firmware
void setup() {
  Serial.begin(9600); //Start een serieële verbinding
  pinMode(LED0, OUTPUT); //Defineer LED0 als een uitgang
  pinMode(LED1, OUTPUT); //Defineer LED1 als een uitgang
  pinMode(LED2, OUTPUT); //Defineer LED2 als een uitgang
  pinMode(LED3, OUTPUT); //Defineer LED3 als een uitgang
  pinMode(LED4, OUTPUT); //Defineer LED4 als een uitgang
  pinMode(ultraT, OUTPUT); //Defineer ultraT als een uitgang
  pinMode(ultraE, INPUT); //Defineer ultraE als een ingang
  pinMode(speaker, OUTPUT); //Defineer speaker als een uitgang
  pinMode(servoR, OUTPUT); //Defineer servoR als een uitgang
  pinMode(servoL, OUTPUT); //Defineer servoL als een uitgang
  pinMode(LDR0, INPUT); //Defineer LDR0 als een uitgang
  pinMode(LDR1, INPUT); //Defineer LDR1 als een uitgang
  pinMode(LDR2, INPUT); //Defineer LDR2 als een uitgang
  pinMode(LDR3, INPUT); //Defineer LDR3 als een uitgang
  pinMode(LDR4, INPUT); //Defineer LDR4 als een uitgang
  pinMode(IR0, INPUT); //Defineer IR1 als een uitgang
  pinMode(IR1, INPUT); //Defineer IR2 als een uitgang
  pinMode(IR2, INPUT); //Defineer IR3 als een uitgang
  pinMode(IR3, INPUT); //Defineer IR4 als een uitgang
}

void loop() {
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  distanceCheck();
}

void distanceCheck(void) {
  //AFSTAND SENSOR CHECKEN//
  int distanceCM;
  digitalWrite(ultraT, HIGH);               //Pulse starten
  delayMicroseconds(10);
  digitalWrite(ultraT, LOW);                //Pulse stoppen
  delayMicroseconds(10);
  distanceCM = pulseIn(ultraE, HIGH);       //Pulse terug uitlezen
  distanceCM = distanceCM / 58;             //Calculate to CM
  //delay(10);
  if (distanceCM == thresholdDistance) {    //SFC 2.0
    //servoStop();
  } else if (distanceCM > thresholdDistance) { //SFC 2.1
    checkLDR();
  } else if (distanceCM < thresholdDistance) { //SFC 2.2
    //servoReverse();
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
  //LASER DETECTIE
  if (analogRead(LDR0) >= laserThreshold) {
    laserDetected = 1; //Links voor
    laserDrive(); //SFC 5
  } else if (analogRead(LDR1) >= laserThreshold) {
    laserDetected = 2; //Voor
    laserDrive(); //SFC 5
  } else if (analogRead(LDR2) >= laserThreshold) {
    laserDetected = 3; //Rechts voor
    laserDrive(); //SFC 5
  } else if (analogRead(LDR3) >= laserThreshold) {
    laserDetected = 4; //Rechts achter
    laserDrive(); //SFC 5
  } else if (analogRead(LDR4) >= laserThreshold) {
    laserDetected = 5;  //Links achter
    laserDrive(); //SFC 5
  } else {
    laserDetected = 0; //Geen laser
    checkIR(); //SFC 3
  }
  //delay(500);        // delay in between reads for stability
}

void laserDrive() { //SFC 5
  digitalWrite(LED4, HIGH);
  switch (laserDetected) {
    case 0: //SFC 5.0
      loop();
      break;
    case 1:
      Serial.println("LINKSvoor");
      digitalWrite(LED1, HIGH);
      //ServoTurnLeft //Boe-Bot draait naar links
      loop();
      break;
    case 2:
      Serial.println("VOORvoorkant");
      digitalWrite(LED3, HIGH);
      //ServoForward // Boe-Bot gaat naar voren
      loop();
      break;
    case 3:
      Serial.println("RECHTSvoor");
      digitalWrite(LED2, HIGH);
      //ServoTurnRight // Boe-Bot draait naar rechts
      break;
    case 4:
      Serial.println("RECHTSachter");
      digitalWrite(LED2, HIGH);
      //ServoTurnRight // Boe-Bot draait naar rechts
      break;
    case 5:
      Serial.println("LINKSachter");
      digitalWrite(LED1, HIGH);
      //ServoTurnLeft //Boe-Bot draait naar links
      break;
    default:
      loop();
      break;
  }
}

void checkIR() { //SFC 3
  //DEBUG
  Serial.println("IR0: ");
  Serial.println(analogRead(IR0)); //IR links uitlezen
  Serial.println("IR1: ");
  Serial.println(analogRead(IR1)); //IR voor uitlezen
  Serial.println("IR2: ");
  Serial.println(analogRead(IR2)); //IR rechts uitlezen
  //IR DETECTIE
  if (analogRead(IR0) >= irThreshold) {
    irDetected = 1; //Links voor
  } else if (analogRead(IR0) >= irThreshold && analogRead(IR1) >= irThreshold && analogRead(IR2) >= irThreshold) {
    irDetected = 2; //Voor
  } else if (analogRead(IR1) >= irThreshold) {
    irDetected = 2; //Voor
  } else if (analogRead(IR2) >= irThreshold) {
    irDetected = 3; //Rechts voor
  } else {
    irDetected = 0; //Geen IR
  }
  irDrive(); //SFC 4
  //delay(500);        // delay in between reads for stability
}

void irDrive() { //SFC 4
  digitalWrite(LED4, HIGH);
  switch (irDetected) {
    case 0:
      Serial.println("GEEN ir, rondje");
      //servoArround();
      break;
    case 1:
      Serial.println("LINKS");
      digitalWrite(LED1, HIGH);
      //servoSharpLeft
      break;
    case 2:
      Serial.println("RECHTS");
      digitalWrite(LED2, HIGH);
      //servoSharpRight
      break;
    case 3:
      Serial.println("VOOR");
      digitalWrite(LED3, HIGH);
      //servoForward
      break;
    default:
      loop();
      break;
  }
}
