// Notes to self:
// Don't change this piece of shit.
// It works as it should.

// 25535 --> 65535 = 20ms
// 25535 --> 28535 = 1.5ms  Stop
// 25535 --> 28735 = 1.6ms  Forward
// 25535 --> 28335 = 1.4ms  Backward

// Pins
const int test_left = PD2; // PB5 = Digital PWM 13
const int test_right = PD3; // PB4 = Digital PWM 12

// Counter and compare values
const uint16_t t1_load = 25535;   // from 25535 to 65535 it should take 20 ms.
const uint16_t Stop = 28535;     // Stop timer for the servo       1.5ms
const uint16_t Forward = 28735;  // Forward timer for the servo    1.6ms
const uint16_t Backward = 28335; // Backward timer for the servo   1.4ms

void setup() {
  // Set pin to be output
  DDRD |= (1 << test_left);
  DDRD |= (1 << test_right);

  // Start the output pins high.
  PORTD |= (1 << test_left);
  PORTD |= (1 << test_right);

  // Reset Timer1 Control Reg A
  TCCR1A = 0;
  TCCR1B = 0;

  // Set to prescaler of 8
  TCCR1B &= ~(1 << CS12);
  TCCR1B |= (1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = Stop;
  OCR1B = Stop;

  // Enable Timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A); // Enable Compare Match A
  TIMSK1 |= (1 << OCIE1B); // Enable Compare Match B
  TIMSK1 |= (1 << TOIE1); // Enable Overflow

  // Enable global interrupts
  sei();
}

void loop() {
  delay(5000); // Pretend we're doing something interesting here. This should not matter as we are making interrupts.
}

// When timer1 reaches COMPA (OCR1A value), put test_left low (left servo).
ISR(TIMER1_COMPA_vect) {
  PORTD &= ~(1 << test_left); // Set test_left low.
}

// When timer1 reaches COMPB (OCR1B value), put test_right low (right servo).
ISR(TIMER1_COMPB_vect) {
  PORTD &= ~(1 << test_right); // Set test_right low.
}

// When timer1 reaches OVERFLOW, put both test left and right high, also put the timer correct.
ISR(TIMER1_OVF_vect) {
  PORTD ^= ( (1 << test_left) | (1 << test_right) ); // Set test_left and test_right high.
  TCNT1 = t1_load; // Reset timer to the right time.
}

// In the following servo functions only the compare values will be changed depending on what function is called.
// Function to stay put.
void ServoStop(){
  OCR1A = Stop;
  OCR1B = Stop;
}

// Function to drive forward.
void ServoForward(){
  OCR1A = Forward;
  OCR1B = Backward;
}

// Function to turn left.
void ServoTurnLeft(){
  OCR1A = Stop;
  OCR1B = Backward;
}

// Function to turn right.
void ServoTurnRight(){
  OCR1A = Forward;
  OCR1B = Stop;
}

// Function to turn sharp left.
void ServoSharpLeft(){
  OCR1A = Forward;
  OCR1B = Backward;
}

// Function to turn sharp right.
void ServoSharpRight(){
  OCR1A = Forward;
  OCR1B = Backward;
}

// Function to drive backward.
void ServoBackward(){
  OCR1A = Backward;
  OCR1B = Forward;
}



