#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <BlynkSimpleEsp32.h>
Servo servo1;
Servo servo2;
Servo servo3;

#define BLYNK_TEMPLATE_ID "TMPL6i43gn9Q0"
#define BLYNK_TEMPLATE_NAME "baru"
#define BLYNK_AUTH_TOKEN "mUOKGfGRJ8gt9Xu3nxDQ3fDCD-s7wT7b"

const char* ssid = "Random";
const char* password = "abcd12345";
const char* serverName = "http://192.168.43.204/projectarduino/api.php";

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
float distance0;
float ketinggianAir0;
float kedalamanWadah0 = 18.9;

//Long Distance from Pintu 1
long duration1;
float distance1;
float ketinggianAir1;
float kedalamanWadah1 = 9.4; //9.5

//Long Distance from Pintu 2
long duration2;
float distance2;
float ketinggianAir2;
float kedalamanWadah2 = 9.4; //9.4

//Long Distance from Pintu 3
long duration3;
float distance3;
float ketinggianAir3;
float kedalamanWadah3 = 9.5; //9.5

//IPAddress local_IP(192, 168, 1, 12);
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
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  wadukMainHandler();
}



void sendtoDatabase(float distance) {
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

void displaytoLCD(float distance)
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
  ketinggianAir0 = kedalamanWadah0- distance0;
  displaytoLCD(ketinggianAir0);
  Blynk.virtualWrite(V6,ketinggianAir0);

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
  ketinggianAir1 = kedalamanWadah1 - distance1;
  // Prints the distance on the Serial Monitor
  Serial.print("Ketinggian Air di Pintu 1: ");
  Serial.print(ketinggianAir1);
  Serial.println("cm");
  Blynk.virtualWrite(V3,ketinggianAir1);
  
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
  ketinggianAir2 = kedalamanWadah2 - distance2;
  // Prints the distance on the Serial Monitor
  Serial.print("Ketinggian Air di Pintu 2: ");
  Serial.print(ketinggianAir2);
  Serial.println("cm");
  Blynk.virtualWrite(V4,ketinggianAir2);
  
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
  ketinggianAir3 = kedalamanWadah3 - distance3;
  // Prints the distance on the Serial Monitor
  Serial.print("Ketinggian Air di Pintu 3: ");
  Serial.print(ketinggianAir3);
  Serial.println("cm");
  Blynk.virtualWrite(V5,ketinggianAir3);

  pintuMainHandler(ketinggianAir0, ketinggianAir1, ketinggianAir2, ketinggianAir3);
  delay(1000);
}

void pintuHandlerServo1(float ketinggianAir0, float ketinggianAir1)
{
  sendtoDatabase(ketinggianAir0);
  for (valueServo1 = 0; valueServo1 <= 90; valueServo1++)
  {
    servo1.write(valueServo1);
    delay(15);
  }
}


void pintuHandlerServo2(float ketinggianAir0, float ketinggianAir2)
{
  sendtoDatabase(ketinggianAir0);
  for (valueServo2 = 0; valueServo2 <= 90; valueServo2++)
  {
    servo2.write(valueServo2);
    delay(15);
  }    
}

void pintuHandlerServo3(float ketinggianAir0, float ketinggianAir3)
{
  sendtoDatabase(ketinggianAir0);
  for (valueServo3 = 0; valueServo3 <= 90; valueServo3++)
  {
    servo3.write(valueServo3);
    delay(15);
  }    
}

void pintuMainHandler(float ketinggianAir0, float ketinggianAir1, float ketinggianAir2, float ketinggianAir3)
{
  if (ketinggianAir0 >= 8.0)
  {
    if (ketinggianAir1 <= 1.0 && ketinggianAir2 <= 1.0 && ketinggianAir3 <= 1.0)
    {
        pintuHandlerServo1(ketinggianAir0, ketinggianAir1);               
        pintuHandlerServo2(ketinggianAir0, ketinggianAir2);               
        pintuHandlerServo3(ketinggianAir0, ketinggianAir3);               
    }
    else
    {
      if (ketinggianAir1 < ketinggianAir2)
      {
        if (ketinggianAir1 < ketinggianAir3)
        {
            if (ketinggianAir0 >= 8.0) 
            {
              if (ketinggianAir1 <= 10.0)
              {
                    pintuHandlerServo1(ketinggianAir0, ketinggianAir1);        
              }        
            }
        }
        else
        {
            if (ketinggianAir0 >= 8.0) 
            {
              if (ketinggianAir3 <= 10.0)
              {
                   pintuHandlerServo3(ketinggianAir0, ketinggianAir3);        
              }        
            }
        }
      }
      else
      {
        if (ketinggianAir2 < ketinggianAir3)
        {
            if (ketinggianAir0 >= 8.0) 
            {
              if (ketinggianAir1 <= 10.0)
              {
                    pintuHandlerServo2(ketinggianAir0, ketinggianAir2);        
              }        
            }
        }
        else
        {
            if (ketinggianAir0 >= 8.0) 
            {
              if (ketinggianAir3 <= 10.0)
              {
                    pintuHandlerServo3(ketinggianAir0, ketinggianAir3);        
              }        
            }
        }      
      }
    }      
  }
}
