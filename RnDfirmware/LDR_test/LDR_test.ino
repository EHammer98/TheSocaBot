//Pins voor de LDR laser detectie sensoren
int LDR0 = A0;            //LDR linker hoek voor
int LDR1 = A1;            //LDR rechter hoek voor
int LDR2 = A2;            //LDR Voor
int LDR3 = A3;            //LDR rechter hoek achter
int LDR4 = A4;            //LDR linker hoek achter
int LED0 = 2;             //Afstand = gelijk aan threshold waarde
int LED1 = 3;             //IR LED('s)/LDR('s) links nemen iets waar
int LED2 = 4;             //IR LED('s)/LDR('s) rechts nemen iets waar
int LED3 = 5;             //IR LED('s)/LDR('s) alle of alleen voor iets waarnemen
int LED4 = 6;             //Laser wordt gedetecteerd
int laserThreshold = 850; //800
//Sensoren
int laserDetected = 0; //0=geen|1=linksVoor|2=Voor|3=rechtsVoor|4=rechtsAchter|5=linksAchter

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(LDR0, INPUT); //Defineer LDR0 als een uitgang
  pinMode(LDR1, INPUT); //Defineer LDR1 als een uitgang
  pinMode(LDR2, INPUT); //Defineer LDR2 als een uitgang
  pinMode(LDR3, INPUT); //Defineer LDR3 als een uitgang
  pinMode(LDR4, INPUT); //Defineer LDR4 als een uitgang
  pinMode(LED0, OUTPUT); //Defineer LED0 als een uitgang
  pinMode(LED1, OUTPUT); //Defineer LED1 als een uitgang
  pinMode(LED2, OUTPUT); //Defineer LED2 als een uitgang
  pinMode(LED3, OUTPUT); //Defineer LED3 als een uitgang
  pinMode(LED4, OUTPUT); //Defineer LED4 als een uitgang
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  // read the input on analog pin 0:
  Serial.println("LDR0: ");
  Serial.println(analogRead(LDR0));
  Serial.println("LDR1: ");
  Serial.println(analogRead(LDR1));
  Serial.println("LDR2: ");
  Serial.println(analogRead(LDR2));
  Serial.println("LDR3: ");
  Serial.println(analogRead(LDR3));
  Serial.println("LDR4: ");
  Serial.println(analogRead(LDR4));
  
  if (analogRead(LDR0) >= laserThreshold){
    laserDetected = 1;
     laserDrive();
  }else if (analogRead(LDR1) >= laserThreshold){
    laserDetected = 2;
      laserDrive();
  }else if (analogRead(LDR2) >= laserThreshold){
    laserDetected = 3;
      laserDrive();
  }else if (analogRead(LDR3) >= laserThreshold){
    laserDetected = 4;
      laserDrive();
  }else if (analogRead(LDR4) >= laserThreshold){
    laserDetected = 5;
      laserDrive();
  }else{
    laserDetected = 0;
  }
  delay(500);        // delay in between reads for stability
}

void laserDrive(){
      digitalWrite(LED4, HIGH);
  switch(laserDetected){
    case 0:
      loop();
      break;
    case 1:
      Serial.println("LINKSvoor");
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      Serial.println("VOORvoorkant");
      digitalWrite(LED3, HIGH);
      break;
    case 3:
      Serial.println("RECHTSvoor");
      digitalWrite(LED2, HIGH);
      break;
    case 4:
      Serial.println("RECHTSachter");
      digitalWrite(LED2, HIGH);
      break;
    case 5:
      Serial.println("LINKSachter");
      digitalWrite(LED1, HIGH);
      break;
    default:
      loop();
      break;
}
}
