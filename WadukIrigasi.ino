#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>

Servo servo1;
Servo servo2;
Servo servo3;

const char* ssid = "";
const char* password = "";

String postData = "";
String payload = "";

const int lcdColumn = 16;
const int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumn, lcdRows);

int valueServo1 = 0;
int valueServo2 = 0;
int valueServo3 = 0;

//Ultrasonic Respon To LCD
const int trigPin0 = 22;
const int echoPin0 = 23;

//Ultrasonic 1 Respon To Servo 1
const int pinServo1 = 33;
const int trigPin1 = 22;
const int echoPin1 = 23;

//Ultrasonic 2 Respon To Servo 2
const int pinServo2 = 33;
const int trigPin2 = 22;
const int echoPin2 = 23;

//Ultrasonic 3 Respon To Servo 3
const int pinServo3 = 33;
const int trigPin3 = 22;
const int echoPin3 = 23;

//Long Distance From Waduk
long duration0;
int distance0;

//Long Distance from Pintu 1
long duration1;
int distance1;

//Long Distance from Pintu 2
long duration2;
int distance2;

//Long Distance from Pintu 3
long duration3;
int distance3;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Initializing...");

  lcd.init();
  lcd.backlight();

  pinMode(trigPin0, OUTPUT); // Sets the trigPin as an Output Ultrasonic 1
  pinMode(echoPin0, INPUT); // Sets the echoPin as an Input Ultrasonic 1
  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output Ultrasonic 2
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input Ultrasonic 2
  servo1.attach(pinServo1);

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output Ultrasonic 3
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input Ultrasonic 3
  servo2.attach(pinServo2);

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output Ultrasonic 4
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input Ultrasonic 4
  servo3.attach(pinServo3);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("STATUS: WIFI CONNECTED");
  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  wadukMainHandler();
  pintuHandlerUltrasonic1();
  pintuHandlerUltrasonic2();
  pintuHandlerUltrasonic3();
}

void sendtoDatabase(long distance) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    int httpCode;

    Serial.println("Sending Data...");
    postData = "ketinggianair="+distance;
    payload = "";
    
    http.begin("http://localhost/projectarduino/api.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    httpCode = http.POST(postData);
    payload = http.getString();

    Serial.print("httpCode: ");
    Serial.println(httpCode);
    Serial.print("payload: ");
    Serial.println("payload");

    http.end();
  }
}

void displaytoLCD(long distance)
{
  // Prints the distance on the Serial Monitor
  Serial.print("Kedalaman Air: ");
  Serial.print(distance);
  Serial.println("cm");  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kedalaman Air ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("cm");  
}

void wadukMainHandler()
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
  displaytoLCD(distance0);
}

void pintuHandlerUltrasonic1()
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
  pintuHandlerServo1();
}

void pintuHandlerUltrasonic2()
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
  pintuHandlerServo2();
}

void pintuHandlerUltrasonic3()
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
  pintuHandlerServo3();
}

void pintuHandlerServo1()
{
  if (distance1 >= 8 && distance1 <= 10)
  {
    for (valueServo1 = 0; valueServo1 <= 180; valueServo1++)
    {
      servo1.write(valueServo1);
      delay(5);
    }    
  }    
}


void pintuHandlerServo2()
{
  if (distance2 >= 8 && distance2 <= 10)
  {
    for (valueServo2 = 0; valueServo2 <= 180; valueServo2++)
    {
      servo2.write(valueServo2);
      delay(5);
    }    
  }    
}

void pintuHandlerServo3()
{
  if (distance3 >= 8 && distance3 <= 10)
  {
    for (valueServo3 = 0; valueServo3 <= 180; valueServo3++)
    {
      servo3.write(valueServo1);
      delay(5);
    }    
  }    
}
