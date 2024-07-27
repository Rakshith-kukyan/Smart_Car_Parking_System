#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>

// Replace with your network credentials
const char* ssid = "vivo 1820";
const char* password = "qwerty1234";

// Replace with your Blynk auth token
const char* auth = "MxSO2oAwNspAJodgMYIdHS8epD0-PSgk";

// Pins for your sensors
const int sensorPin1 = 34;
const int sensorPin2 = 35;
const int sensorPin3 = 36;
const int sensorPinen = 33;
const int sensorPinex = 39;

// Pin for the servo motors
const int servoPin1 = 16;
const int servoPin2 = 17;

// Variables to store sensor values
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;
int a,b,c;

// Servo objects
Servo servoGate1;
Servo servoGate2;

int pos1=0;
int pos2=0;

// Timer object
BlynkTimer timer;

void setup()
{
  // Serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, ssid, password);

  // Set interval for sensor readings
  timer.setInterval(1000L, sensorReadings);

  // Attach servos to the pins
  servoGate1.attach(servoPin1);
  servoGate2.attach(servoPin2);

  servoGate1.write(0);
  delay(500);
  servoGate2.write(0);
  delay(500);

}

void loop()
{
  // Run Blynk tasks
  Blynk.run();

  // Run timer tasks
  timer.run();
}

void sensorReadings()
{
  // Read sensor values
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPinen);
  sensorValue5 = analogRead(sensorPinex);

  // Print sensor values
  Serial.print("Sensor 1: ");
  Serial.println(sensorValue1);
  Serial.print("Sensor 2: ");
  Serial.println(sensorValue2);
  Serial.print("Sensor 3: ");
  Serial.println(sensorValue3);
  Serial.print("Entrance Sensor: ");
  Serial.println(sensorValue4);
  Serial.println(digitalRead(sensorPinen));
  Serial.print("Exit Sensor: ");
  Serial.println(sensorValue5);
  Serial.println(digitalRead(sensorPinex));

  if ((sensorValue4 < 1000) && ((sensorValue1 > 1000) || (sensorValue2 > 1000) || (sensorValue1 > 1000)))
  {
    for (pos1 = 0; pos1 <= 90; pos1 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoGate1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }
    delay(1500);
    for (pos1 = 90; pos1 >= 0; pos1 -= 1) { // goes from 180 degrees to 0 degrees
    servoGate1.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);
    }
  }

  if (sensorValue5 < 1000)
  {
    for (pos2 = 0; pos2 <= 90; pos2 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoGate2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }
    delay(1500);
    for (pos2 = 90; pos2 >= 0; pos2 -= 1) { // goes from 180 degrees to 0 degrees
    servoGate2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);
    }
  }
  if (sensorValue1 < 1000){
    a=0;
  }
  else{
    a=4000;
  }
  if (sensorValue2 < 1000){
    b=0;
  }
  else{
    b=4000;
  }
  if (sensorValue3 < 1000){
    c=0;
  }
  else{
    c=4000;
  }
  // Send sensor values to Blynk
  Blynk.virtualWrite(V4, a);
  Blynk.virtualWrite(V5, b);
  Blynk.virtualWrite(V6, c);
}
