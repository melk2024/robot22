//Bahir Dar Institute of Technology - BiT
//This is the code written for the project
//Project title: Landmine detection and disposal robot
//Authorized by: ICE Group
//Date :
//Submitted to: Faculty of Electrical and Computer Engineering

#include <Servo.h>
#include <AFMotor.h>
#include <NewPing.h>
#define trigger 42
#define echo 44
#define MAX_DISTANCE 200

NewPing sonar(trigger, echo, MAX_DISTANCE);
float distance = 0;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo Myservo;
int inputByte;
int state = LOW;
int value;
int ind1 = 22;
int buz = 52;

void setup() {
  pinMode(buz, OUTPUT);
  pinMode(ind1, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  Myservo.attach (9);
  Serial.begin(9600);
  Myservo.write(90);
  delay(100);
}

void loop() {
  while (Serial.available() > 0) {
    inputByte = Serial.read();
    //Serial.println(inputByte);
    if (inputByte == 'Z') {
      value = digitalRead(ind1);
//      if (value != state) {
//        state = value;
//      }
      if (value = LOW) {
        distance = sonar.ping_cm();
        Serial.println(distance);
        if (distance <= 50 || distance != 0 ) {
          rstop();
          // to prevent collision of robot
          Myservo.write(0);
          distance = sonar.ping_cm();
          Serial.println(distance);
          if (distance >= 50) {
            turnleft();
          }
          else {
            Myservo.write(180);
            distance = sonar.ping_cm();
            Serial.println(distance);
            if (distance >= 50) {
              turnright();
            }
            else {
              Myservo.write(90);
              mbackward();

            }
          }
        }
        else {
          Myservo.write(90);
          mforward();
        }
      }
      else {
         digitalWrite(buz, HIGH);
        rstop();
      }
    }
    else if (inputByte == 'z') {
       digitalWrite(buz, LOW);
      rstop();
    }
    else if (inputByte == 'Y') {
      mforward();
    }
    else if (inputByte == 'y') {
      mbackward();
    }
    else if (inputByte == 'X') {
      turnleft();
    }
    else if (inputByte == 'x') {
     turnright();
    }
    else {
      }
  }
}

void turnleft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void turnright() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void mforward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD);
}
void mbackward() {
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
void rstop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
