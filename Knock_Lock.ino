/*
19-20
Just as in Project 05, you'll need to import the
Servo library and create an instance to use the motor.
21-25
Create constants to name your inputs and outputs.
26-27
Create variables to hold the values from your switch and piezo.
28-29
Set up some constants to use as thresholds for the knock
maximum and minimum levels.
30-31
The locked variable will let you know if the lock is engaged or
not.A boolean is a data type that can only be true (1) or false
(0). You should start with the mechanism unlocked.
The last global variable will hold the number of valid knocks you
have received.
*/
#include <Servo.h>
Servo myServo;
const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;
int knockVal;
int switchVal;
const int quietKnock = 10;
const int loudKnock = 100;
boolean locked = false;
int numberOfKnocks = 0;
/*
44-50
In your setup(), attach the servo to pin 9.
Set the LED pins as outputs and the switch pins as inputs.
51-54
Initialize serial communication with the computer so you can
monitor the knock volume, what the current state of the lock is,
and how many more knocks you have to go.
Turn on the green LED, move the servo to the unlocked position,
and print the current status to the serial monitor indicating the
circuit is in the unlocked position.
*/
void setup() {
  myServo.attach(9);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}
void loop(){
  if(locked = false){
    switchVal = digitalRead(switchPin);
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      myServo.write(90);
      Serial.println("The box is locked!");
      delay(1000);
    }
  } 
  if(locked == true){
    knockVal = analogRead(piezo);
    if(numberOfKnocks < 3 && knockVal > 0) {
      if(checkForKnock(knockVal) == true) {
        numberOfKnocks++;
      }
      Serial.print(3-numberOfKnocks);
      Serial.println(" more knocks to go");
    }
    if(numberOfKnocks >= 3){
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println("The box is unlocked!");
      numberOfKnocks = 0;
    }
  } 
}
boolean checkForKnock(int value){
  if(value > quietKnock && value < loudKnock) {
    digitalWrite(yellowLed, HIGH);
    delay(50);
    digitalWrite(yellowLed, LOW);
    Serial.print("Valid knock of value ");
    Serial.println(value);
    return true;
  }
  else {
    Serial.print("Bad knock value ");
    Serial.println(value);
    return false;
  }
}