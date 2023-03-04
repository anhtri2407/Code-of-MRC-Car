/*
  Created: 20 Feb 2023
  Author: STEM CLUB - THPT Mạc Đĩnh Chi
  Status: Done
  Bluetooth Module: HC-05
  We can configure our Bluetooth device's name, change the password when HC-05 is in AT command mode (baud speed: 38400)
*/

//include the libraries
// #include <SoftwareSerial.h>

//setup motor pins
#define ENA 5
#define ENB 6
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12

//initialize variables for motors
short M1_Speed = 120; // speed of motor 1 
short M2_Speed = 120; // speed of motor 2
short LeftRotationSpeed = 250;  // Left Rotation Speed
short RightRotationSpeed = 250; // Right Rotation Speed

//setup bluetooth
// SoftwareSerial BTSerial(2, 3); // RX | TX  --->  TX | RX (HC-05) if you don't want to use pin 0 (RX) and pin 1 (TX)
char read_variable;

//main car movements function
void car_forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, M1_Speed);
  analogWrite(ENB, M2_Speed);
}
void car_backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);    
  analogWrite(ENA, M1_Speed);
  analogWrite(ENB, M2_Speed);
}
void car_right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);         
  analogWrite(ENA, LeftRotationSpeed);
  analogWrite(ENB, RightRotationSpeed);
}
void car_left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);       
  analogWrite(ENA, LeftRotationSpeed);
  analogWrite(ENB, RightRotationSpeed);
}
void car_stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); //HC-05 default speed to communicate with serial monitor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  //read bluetooth's variable from serial monitor
//   if (BTSerial.available() > 0){
//     read_variable = BTSerial.read();
//     Serial.println(read_variable);
//   }
  if (Serial.available() > 0) read_variable = Serial.read();
  //processing input values
  switch (read_variable) {
    case 'F': 
      car_forward();
      // Serial.println("Car is Forwarding");
      break;
    case 'B':
      car_backward();
      // Serial.println("Car is Backwarding");
      break;
    case 'L':
      car_left();  
      // Serial.println("Car is turning Left");
      break;
    case 'R':
      car_right();
      // Serial.println("Car is turning Right");
      break;
     case 'S':
      car_stop();
      // Serial.println("Car is turning Right");
      break;
  }
}
