#include <WiFiS3.h>
#include <Servo.h>

const char* ssid = ""; // Your wifi name
const char* password = ""; // Your wifi password
const char* host = ""; // Your host server ip address
const int port = ; // Your host server port number

const int servoPin = 9;
Servo servo;
const int trigPin = 10;
const int echoPin = 11;

WiFiClient client;  // Declare the client globally to maintain the connection

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi....");
  }
  Serial.println("Connected to WiFi");

  // Connect to the server
  if (client.connect(host, port)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection to server failed");
  }
}

float duration, distance;

void report(int deg) {
  if (client.connected()) {  // Check if the connection is still active
    servo.write(deg);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;

    if (distance <= 100.0 && distance > 3.0) {
      String message = String(distance) + " @" + String(deg)+ "°";
      client.print(message);
      Serial.println("Data sent to server: " + message);
      delay(500);  // Delay to control data sending rate
    } 
    else {
      delay(500);  // Delay if distance is out of range
    }
  } 
  else {
    Serial.println("Disconnected from server, attempting to reconnect...");
    client.connect(host, port);  // Attempt to reconnect
  }
}

void loop() {
  for (int i = 0; i < 180; i+=2){
    report(i);
  }
  for (int i = 178; i > 0; i-=2){
    report(i);
  }
}