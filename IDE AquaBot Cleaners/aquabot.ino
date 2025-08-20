#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

#define redLed    A9   
#define greenLed  A8

#define trigPin 14
#define echoPin 9
#define BUTTON_RIGHT   2
#define BUTTON_LEFT    19
#define BUTTON_stop    18
#define BUTTON_stop_machine    4
#define BUTTON_stop_arm    17


#define IR_RIGHT       A14
#define IR_LEFT        A15

//arm
#define m1   A2
#define m2   A3
#define ENABLE_PIN2 6

//for the fornt
#define m11   13
#define m12   12
#define m21   8
#define m22   7
#define ENABLE_PIN 11

//behind
#define m31   A4
#define m32   A5
#define m41   A6
#define m42   A7
#define ENABLE_PIN1 10

const uint8_t MOTOR_SPEED = 400;

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 1);
  lcd.clear();
    /*Display data to the welcome screen*/
  lcd.setCursor(0,0);
  lcd.print("WelcomeAutomatic");
  lcd.setCursor(1,1);
  lcd.print("AQuaBot Cleaners");
  lcd.setCursor(3,2);
  lcd.print("System");
  delay(200);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_stop, INPUT_PULLUP);
  pinMode(BUTTON_stop_machine, INPUT_PULLUP);
  pinMode(BUTTON_stop_arm, INPUT_PULLUP);
  
  /*send loading message to lcd1*/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loading.");
  lcd.setCursor(8, 0);
  for(int i =0;i<16;i++)
      lcd.print(".");
  delay(150);
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("AQuaBot Cleaners");
  lcd.setCursor(3,2);
  lcd.print("System");
  delay(100);
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(ENABLE_PIN2, OUTPUT);

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  pinMode(m31, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m42, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  analogWrite(ENABLE_PIN, MOTOR_SPEED);

  digitalWrite(m31, HIGH);
  digitalWrite(m32, LOW);
  digitalWrite(m41, LOW);
  digitalWrite(m42, HIGH);
  analogWrite(ENABLE_PIN, MOTOR_SPEED);
  lcd.clear();
}

void loop() {
  long duration, distance;
  
  if (digitalRead(BUTTON_RIGHT) == LOW && digitalRead(IR_RIGHT) == LOW && digitalRead(BUTTON_LEFT) == LOW && digitalRead(IR_LEFT) == LOW) {
      lcd.setCursor(0,1);
      lcd.print("No objec Insides");
      digitalWrite(m11, HIGH);
      digitalWrite(m12, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m22, HIGH);
      analogWrite(ENABLE_PIN, MOTOR_SPEED);
      delay(3);
  }
  if (digitalRead(BUTTON_RIGHT) == HIGH || digitalRead(IR_RIGHT) == HIGH) {
    lcd.setCursor(0,1);
    lcd.print("objectDetect InRigh");
    digitalWrite(m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    analogWrite(ENABLE_PIN, MOTOR_SPEED);
    delay(3);
  } 

  // إيقاف الموتور
  if (digitalRead(BUTTON_LEFT) == HIGH || digitalRead(IR_LEFT) == HIGH) {
      lcd.setCursor(0,1);
      lcd.print("objectDetect InLeft");
      digitalWrite(m11, LOW);
      digitalWrite(m12, HIGH);
      digitalWrite(m21, LOW);
      digitalWrite(m22, HIGH);
      analogWrite(ENABLE_PIN, MOTOR_SPEED);
      delay(3);
  }
  if (digitalRead(BUTTON_stop) == HIGH) {
      digitalWrite(m11, LOW);
      digitalWrite(m12, LOW);
      digitalWrite(m21, LOW);
      digitalWrite(m22, LOW);
      analogWrite(ENABLE_PIN, 0);
  }



  if(digitalRead(BUTTON_stop_machine) == HIGH){
      digitalWrite(m31, LOW);
      digitalWrite(m32, LOW);
      digitalWrite(m41, LOW);
      digitalWrite(m42, LOW);
      analogWrite(ENABLE_PIN, 0);
  }
  else if(digitalRead(BUTTON_stop_machine) == LOW){
      digitalWrite(m31, LOW);
      digitalWrite(m32, HIGH);
      digitalWrite(m41, LOW);
      digitalWrite(m42, HIGH);
      analogWrite(ENABLE_PIN, MOTOR_SPEED);
  }

  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 24) {  // This is where the LED On/Off happens
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("objectDetect InFront");
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);

    // turn on green led and turn off red led 
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    delay(3);
    
  }
  if(distance > 24){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Object Detected");
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    // turn on red led and turn off green led 
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    delay(3);

  }
  if(digitalRead(BUTTON_stop_arm)==HIGH){
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);

      while(digitalRead(BUTTON_stop_arm)!=LOW);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
  }

  delay(20);
}
