#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int lcdColumn = 16;
const int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumn, lcdRows);

int valueServo1 = 0;
int valueServo2 = 0;
int valueServo3 = 0;

const int pinServo0 = 33;
const int trigPin0 = 22;
const int echoPin0 = 23;

const int pinServo1 = 33;
const int trigPin1 = 22;
const int echoPin1 = 23;

const int pinServo2 = 33;
const int trigPin2 = 22;
const int echoPin2 = 23;

const int pinServo3 = 33;
const int trigPin3 = 22;
const int echoPin3 = 23;

long duration0;
int distance0;

long duration1;
int distance1;

long duration2;
int distance2;

long duration3;
int distance3;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Initializing...");

  lcd.init();
  lcd.backlight();

  pinMode(trigPin0, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin0, INPUT); // Sets the echoPin as an Input
  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  servo1.attach(pinServo1);

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  servo2.attach(pinServo2);

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  servo3.attach(pinServo3);
}
void loop() {
  displaytoLCD();
  pintuHandler1();
  pintuHandler2();
  pintuHandler3();
}

void displaytoLCD()
{
  digitalWrite(trigPin0, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin0, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration0 = pulseIn(echoPin0, HIGH);
  // Calculating the distance
  distance0 = duration0 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Kedalaman Air: ");
  Serial.print(distance0);
  Serial.println("cm");  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kedalaman Air ");
  lcd.setCursor(0, 1);
  lcd.print(distance0);
  lcd.print("cm");
}

void pintuHandler1()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Kedalaman Air di Pintu 1: ");
  Serial.print(distance1);
  Serial.println("cm");

  if (distance1 >= 8 && distance1 <= 10)
  {
    for (valueServo1 = 0; valueServo1 <= 180; valueServo1++)
    {
      servo1.write(valueServo1);
      delay(5);
    }    
  }  
}

void pintuHandler2()
{
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Kedalaman Air di Pintu 2: ");
  Serial.print(distance2);
  Serial.println("cm");

  if (distance2 >= 8 && distance2 <= 10)
  {
    for (valueServo2 = 0; valueServo2 <= 180; valueServo2++)
    {
      servo2.write(valueServo2);
      delay(5);
    }    
  }  
}

void pintuHandler3()
{
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Kedalaman Air di Pintu 3: ");
  Serial.print(distance3);
  Serial.println("cm");

  if (distance3 >= 8 && distance3 <= 10)
  {
    for (valueServo3 = 0; valueServo3 <= 180; valueServo3++)
    {
      servo3.write(valueServo1);
      delay(5);
    }    
  }  
}
