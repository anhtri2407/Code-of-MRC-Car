/*
  Created: 20 Feb 2023
  Author: STEM CLUB - THPT Mạc Đĩnh Chi
  Status: Done
*/

// Include the libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define the motor pins
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

// Variables for the Blynk widget values
int x = 50;
int y = 50;
int Speed;

//Blynk setup
char auth[] = "your-auth-token"; // Enter your Blynk's auth token
char ssid[] = "your-wifi-host"; // Enter your WIFI name
char pass[] = "your-wifi-password"; // Enter your WIFI passowrd

// Get the joystick values
BLYNK_WRITE(V0) {
  x = param[0].asInt(); //x axis
}
BLYNK_WRITE(V1) {
  y = param[0].asInt(); //y axis
}
BLYNK_WRITE(V2) {
  Speed = param.asInt(); //Get the speed values as slider
}

/************** Motor movement functions *****************/
void car_forward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void car_backward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void car_left() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void car_right() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void car_stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Processing input values
void running() {
  if (y > 70) {
    car_forward();
//     Serial.println("Car is forwarding"); // chỉ uncomment khi muốn đọc giá trị
  } else if (y < 30) {
    car_backward();
//     Serial.println("Car is backwarding"); // chỉ uncomment khi muốn đọc giá trị
  } else if (x < 30) {
    car_left();
//     Serial.println("Car is turning left"); // chỉ uncomment khi muốn đọc giá trị
  } else if (x > 70) {
    car_right();
//     Serial.println("Car is turning right"); // chỉ uncomment khi muốn đọc giá trị
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    car_stop();
//     Serial.println("Car is stopping"); // chỉ uncomment khi muốn đọc giá trị
  }
}

// Setup function
void setup() {
  Serial.begin(9600);
  // Set the motor pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

// Main loop
void loop() {
  Blynk.run(); //Call Blynk function
  running(); //Call the main function
}
