#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

Servo servo1;
Servo servo2;
Servo servo3;

const char* blynkauth = "";
const char* ssid = "vinz";
const char* password = "Alvin406";
const char* serverName = "http://192.168.1.4/projectarduino/api.php";

const int lcdColumn = 16;
const int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumn, lcdRows);

int valueServo1 = 0;
int valueServo2 = 0;
int valueServo3 = 0;

/*
 * LCD Pin
 * SDA = 21;
 * scl = 22;
 */

//Ultrasonic Respon To LCD
const int trigPin0 = 16;
const int echoPin0 = 17;

//Ultrasonic 1 Respon To Servo 1
const int pinServo1 = 5;
const int trigPin1 = 19;
const int echoPin1 = 18;

//Ultrasonic 2 Respon To Servo 2
const int pinServo2 = 32;
const int trigPin2 = 33;
const int echoPin2 = 25;

//Ultrasonic 3 Respon To Servo 3
const int pinServo3 = 4;
const int trigPin3 = 26;
const int echoPin3 = 27;

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

//IPAddress local_IP(192, 168, 1, 4);
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress primaryDNS(8, 8, 8, 8);
//IPAddress secondaryDNS(8, 8, 4, 4);

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
//  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

  Serial.println("STATUS: WIFI CONNECTED");
  Serial.print("IP ADDRESS: ");
  Blynk.begin(blynkauth, ssid, password);
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  wadukMainHandler();
}



void sendtoDatabase(long distance) {
  if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
            
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");      
      String postData = "api_key=tPmAT5Ab3j7F9&ketinggianair=";
      String totalPostData = postData+distance;
      int httpResponseCode = http.POST(totalPostData);
      String payload = http.getString();
     
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.println(payload);
      }
      else {
        Serial.print("HTTP Error code: ");
        Serial.println(httpResponseCode);
        Serial.println(payload);
      }        
      // Free resources
      http.end();
    }
}

void displaytoLCD(long distance)
{
  // Prints the distance on the Serial Monitor
  Serial.print("Ketinggian Air: ");
  Serial.print(distance);
  Serial.println("cm");  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ketinggian Air ");
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
  pintuHandlerUltrasonic1(distance0);
  pintuHandlerUltrasonic2(distance0);
  pintuHandlerUltrasonic3(distance0);
}

void pintuHandlerUltrasonic1(long distance0)
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
  Serial.print("Ketinggian Air di Pintu 1: ");
  Serial.print(distance1);
  Serial.println("cm");
  pintuHandlerServo1(distance0, distance1);
}

void pintuHandlerUltrasonic2(long distance0)
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
  Serial.print("Ketinggian Air di Pintu 2: ");
  Serial.print(distance2);
  Serial.println("cm");
  pintuHandlerServo2(distance0, distance2);
}

void pintuHandlerUltrasonic3(long distance0)
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
  Serial.print("Ketinggian Air di Pintu 3: ");
  Serial.print(distance3);
  Serial.println("cm");
  pintuHandlerServo3(distance0, distance3);
}

void pintuHandlerServo1(long ditance0, long distance1)
{
  if (distance0 >= 8) {
    if (distance1 >= 3 && distance1 <= 10)
    {
      sendtoDatabase(distance1);
      for (valueServo1 = 0; valueServo1 <= 90; valueServo1++)
      {
        servo1.write(valueServo1);
        delay(15);
      }    
    }        
  }
  delay(2000);
}


void pintuHandlerServo2(long distance0, long distance2)
{
  if (distance0 >= 8) {
    if (distance2 >= 3 && distance2 <= 10)
    {
      sendtoDatabase(distance2);
      for (valueServo2 = 0; valueServo2 <= 90; valueServo2++)
      {
        servo2.write(valueServo2);
        delay(15);
      }    
    }        
  }
  delay(2000);
}

void pintuHandlerServo3(long distance0, long distance3)
{
  if (distance0 >= 8) {
    if (distance3 >= 3 && distance3 <= 10)
    {
      sendtoDatabase(distance3);
      for (valueServo3 = 0; valueServo3 <= 90; valueServo3++)
      {
        servo3.write(valueServo3);
        delay(15);
      }    
    }        
  }
  delay(2000);
}
