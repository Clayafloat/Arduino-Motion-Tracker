#include <NewPing.h>

const int TRIG = 8;
const int ECHO = 7;
const int BUTTON = 2;
const int LED = 6;
const int GO_LED = 3;
const int TMPPIN = A5;

double VELOCITY = 0; // Initialized in setup

double TEMP = 0; // Celcius, initialized in setup
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long totalMillis = 0;
double previousDistance = 0.0;
double equilibrium = 0.0;

int switchState = 0;

NewPing sonar(TRIG, ECHO, 200);

void setup() 
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(GO_LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  for (int i = 0; i < 99; ++i)
  {
     TEMP += tempC();
  }

  TEMP /= 100; // Find avg temp from 100 readings
  VELOCITY = 331.5 + (0.6 * TEMP);
  Serial.print(TEMP);
  Serial.println(" C");
}

void loop() 
{
  currentMillis = millis();
  
  if (digitalRead(BUTTON) == HIGH)
  {
    switchState = 1 - switchState;

    if (switchState == 1)
    {
      Serial.println("COMMAND: start_recording");
      equilibrium = distance();
      digitalWrite(LED, HIGH);
      delay(100);
    }
    else if (switchState == 0)
    {
      Serial.println("COMMAND: stop_recording");
      totalMillis = 0.0;
      digitalWrite(LED, LOW);
      delay(100);
    }
  }

  double distanceD = distance();

  if (switchState == 1 && distanceD != previousDistance)
  {
    previousDistance = distanceD;
    totalMillis += currentMillis - previousMillis;
    double displacement = equilibrium - distanceD;
    Serial.print(totalMillis);
    Serial.print(" ");
    Serial.print(displacement, 3);
    Serial.print(" ");
    Serial.println(distanceD, 3);

    if (displacement >= 0.038 && displacement <= 0.042) // If mass is extended roughly 4cm away, give go signal
    {
      digitalWrite(GO_LED, HIGH);
    }
    else
    {
      digitalWrite(GO_LED, LOW);
    }
  }
  
  previousMillis = currentMillis;
  
  delay(45);
}

float tempC() 
{
  float raw = analogRead(TMPPIN);
  float percent = raw / 1024.0;
  float volts = percent * 5.0;
  return 100.0 * (volts - 0.5);
}

double distance()
{
  double microseconds = 0;
  double distance = 0.0;
  
  microseconds = (double) sonar.ping_median(3) / 1000.0 / 1000.0 / 2.0;
  distance = VELOCITY * microseconds;
  
  return distance;
}

