const int led0 = 2;
const int led1 = 3;
const int led2 = 4;
const int led3 = 5;
const int led4 = 6;
const int led5 = 11;
const int led6 = 12;
const int led7 = 13;

const int trigger = 9;
const int echo = 8;

int _delay = 250;

int ledArray[] = { led0, led1, led2, led3, led4, led5, led6, led7};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for(int i = 0; i < 8; i++)
  {
    pinMode(ledArray[i], OUTPUT);
  }
}


// turn on an LED
void turnOn(int led)
{
  digitalWrite(led, HIGH);
}

// turn on an LED
void turnOff(int led)
{
  digitalWrite(led, LOW);
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

long measureDistance()
{
  long duration, cm;
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  return cm;
}

void writeValue(int number)
{
  Serial.println(number);
  String binArray = String(number, BIN);
  
  Serial.println(binArray);
  
  for(int i = 0; i < binArray.length(); i++)
  {
    int state = int(binArray[i]);

    switch(state)
    {
      case '1':
        turnOn(ledArray[i]);
        break;
      default:
        turnOff(ledArray[i]);
        break;
    }
  }
}


void loop() {
  int cm;
  cm = measureDistance();

  if(cm >= 5) _delay = cm * 5;

  writeValue(cm);
  delay(_delay);
}

