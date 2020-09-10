// Classe
// Defines a control that uses interrupts
class Control {

  private:
  
    int pin;
    int offset;
    int interrupt;
    int maxMagnitude;
    volatile float magnitude = 0.00;
    volatile int pulseTime = 0;
  
  public:
  
    Control(int pin, int offset, int maxMagnitude) {
      this->pin = pin;
      this->offset = offset;
      this->maxMagnitude = maxMagnitude;
      this->interrupt = digitalPinToInterrupt(this->pin);
    }

    int returnPin() {
      return(this->pin);
    }

    int returnOffset() {
      return(this->offset);
    }

    int returnInterrupt() {
      return(this->interrupt);
    }

    int returnPulseTime() {
      return(this->pulseTime);
    }

    int returnMagnitude() {
      return(this->magnitude);
    }

    void setPulseTime(int newTime) {
      this->pulseTime = newTime;
    }

    void setMagnitude(int newMagnitude) {
      this->magnitude = newMagnitude*100/this->maxMagnitude;
    }
};

// Variables
Control pitch(2, 1460, 144);
Control roll(3, 1460, 144);

// Main Functions
void setup() {

  // Attach interrupts
  attachInterrupt(pitch.returnInterrupt(), pitchCalc, CHANGE);
  attachInterrupt(roll.returnInterrupt(), rollCalc, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // This is all just serial stuff in here
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.print("Pitch: ");
  Serial.println(pitch.returnMagnitude());
  Serial.print("Roll: ");
  Serial.println(roll.returnMagnitude());
  delay(50);
}

// Other functions
// Aliases
void pitchCalc() {calc(pitch);}
void rollCalc() {calc(roll);}

// Calculate pulse time and thus magnitude
void calc(Control &control) {

  if(digitalRead(control.returnPin()) == HIGH) {
    control.setPulseTime(micros());
  } else {
    control.setMagnitude(micros() - control.returnPulseTime() - control.returnOffset());
    control.setPulseTime(0);
  }
}
