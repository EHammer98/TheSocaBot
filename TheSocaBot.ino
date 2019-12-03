/*
#############################################################
#Firmware:           TheSocaBot                             #
#Hardware:           Arduino Mega 2560                      #
#Eerste opzet:       26-11-2019                             #
#Auteurs: E. Hammer | N. Vollebregt | M. Remmig | O. Cekem  #
#Laatst gewijzigd:   03-12-2019                             #
#Versie:             1.0.2                                  #
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

//Sensoren
int thresholdDistance = 5;  //Drempelwaarde om de afstand mee te vergelijken (in CM)
int laserDetected = 0;      //0=geen|1=linksVoor|2=Voor|3=rechtsVoor|4=rechtsAchter|5=linksAchter
int irDetected = 0;         //0=geen|1=links|2=front|3=right
//Initializeren van de firmware
void setup() {
  Serial.begin(9600); //Start een serieële verbinding
  pinMode(LED0, OUTPUT); //Defineer LED0 als een uitgang
  pinMode(LED1, OUTPUT); //Defineer LED1 als een uitgang
  pinMode(LED2, OUTPUT); //Defineer LED2 als een uitgang
  pinMode(LED3, OUTPUT); //Defineer LED3 als een uitgang
  pinMode(LED4, OUTPUT); //Defineer LED4 als een uitgang
  pinMode(ultraT, OUTPUT); //Defineer ultraT als een uitgang
  pinMode(ultraE, INPUT); //Defineer ultraT als een ingang
  pinMode(ultraT, OUTPUT); //Defineer ultraT als een uitgang
  pinMode(speaker, OUTPUT); //Defineer ultraT als een uitgang
  pinMode(servoR, OUTPUT); //Defineer servoR als een uitgang
  pinMode(servoL, OUTPUT); //Defineer servoL als een uitgang
  pinMode(LDR0, OUTPUT); //Defineer LDR0 als een uitgang
  pinMode(LDR1, OUTPUT); //Defineer LDR1 als een uitgang
  pinMode(LDR2, OUTPUT); //Defineer LDR2 als een uitgang
  pinMode(LDR3, OUTPUT); //Defineer LDR3 als een uitgang
  pinMode(LDR4, OUTPUT); //Defineer LDR4 als een uitgang
  pinMode(IR0, OUTPUT); //Defineer IR1 als een uitgang
  pinMode(IR1, OUTPUT); //Defineer IR2 als een uitgang
  pinMode(IR2, OUTPUT); //Defineer IR3 als een uitgang
  pinMode(IR3, OUTPUT); //Defineer IR4 als een uitgang
}

void loop() {

}
