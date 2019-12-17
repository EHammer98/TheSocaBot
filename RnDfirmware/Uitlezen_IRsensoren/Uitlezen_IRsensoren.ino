// Code voor het uitlezen van IR sensoren en aansturen van de bijbehorende leds
// Plus opzet voor aansturing servo's

const int IRpin_l = A3;   // Pins die door de functie gebruikt worden
const int IRpin_m = A4;
const int IRpin_r = A5;
const int LEDpin_l = 3;
const int LEDpin_m = 4;
const int LEDpin_r = 5;
const int NumReadings = 10;
const int CompareValue_IR = 900;

char IRsensorRead(void);

void setup()  // Leds als OUTPUT instellen
{
  pinMode(LEDpin_l, OUTPUT);
  pinMode(LEDpin_m, OUTPUT);
  pinMode(LEDpin_r, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char IRsensorOutput = IRsensorRead();
  //IRcase(IRsensorOutput);
  IRcaseLED(IRsensorOutput);
}


char IRsensorRead(void)
{
  int IRvalue_l[NumReadings];   // een array voor elke IR sensor: (l)inks, (m)idden en (r)echts
  int IRvalue_m[NumReadings];
  int IRvalue_r[NumReadings];
  
  int tot_l = 0;   // totaal van array
  int tot_m = 0;
  int tot_r = 0;
  
  int avg_l = 0;   // gemiddelde van array
  int avg_m = 0;
  int avg_r = 0;
  
  char ReturnValue_IR;   // bitreeks waarvan de 3 LSB veranderen op basis van sensorwaarden
  
  int i;  // teller voor vullen van array

  for (i = 0; i < NumReadings; i++)
  {
    IRvalue_l[i] = analogRead(IRpin_l);
    tot_l = tot_l + IRvalue_l[i];
    IRvalue_m[i] = analogRead(IRpin_m);
    tot_m = tot_m + IRvalue_m[i];
    IRvalue_r[i] = analogRead(IRpin_r);
    tot_r = tot_r + IRvalue_r[i];
    delay(5);
  }
  
  avg_l = tot_l / NumReadings;
  avg_m = tot_m / NumReadings;
  avg_r = tot_r / NumReadings;
  Serial.println(avg_m);
  
  
  if(avg_l < CompareValue_IR) ReturnValue_IR |= 0x01; else ReturnValue_IR &= ~(0x01);
  if(avg_m < CompareValue_IR) ReturnValue_IR |= 0x02; else ReturnValue_IR &= ~(0x02);
  if(avg_r < CompareValue_IR) ReturnValue_IR |= 0x04; else ReturnValue_IR &= ~(0x04);
  
  return ReturnValue_IR;
}

//void IRcase(char w)
//{
//  switch(w)
//  case 0x01:
//  {
//    //stuur scherp links
//  }
//  break;
//
//  case 0x02:
//  {
//    // rij rechtdoor
//  }
//  break;
//  
//  case 0x03:
//  {
//    // stuur langzaam links
//  }
//  break;
//
//  case 0x04:
//  {
//    // stuur scherp rechts
//  }
//  break;
//
//  case 0x06:
//  {
//    // stuur langzaam rechts
//  }
//  break;
//  case 0x07:
//  {
//    // rechtdoor (alle sensoren HIGH)
//  }
//
//  default:
//  {
//    // rondje draaien (leader kwijt)
//  }
//  
//}

void IRcaseLED(char LEDs)
{
  digitalWrite(LEDpin_l, LOW);
  digitalWrite(LEDpin_m, LOW);
  digitalWrite(LEDpin_r, LOW);
  switch(LEDs)
  {
    case 0x01:
    {
      digitalWrite(LEDpin_l, HIGH);
      //Serial.println("links");
    }
    break;
  
    case 0x02:
    {
      digitalWrite(LEDpin_m, HIGH);
      //Serial.println("midden");
    }
    break;

    case 0x03:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      //Serial.println("linksmidden");
    }
    break;
  
    case 0x04:
    {
      digitalWrite(LEDpin_r, HIGH);\
      //Serial.println("rechts");
    }
    break;

    case 0x06:
    {
      digitalWrite(LEDpin_r, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      //Serial.println("rechtsmidden");
    }
    break;

    case 0x07:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      digitalWrite(LEDpin_r, HIGH);
      //Serial.println("midden");
    }
    break;
  }
}
