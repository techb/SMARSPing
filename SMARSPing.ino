#include <AFMotor.h>

#define echoPin A4
#define trigPin A5
long duration;
int distance;
int current_distance;

AF_DCMotor motor1(1);
AF_DCMotor motor2(3);

void setup() {
    Serial.begin(9600);

    // turn on motor
    motor1.setSpeed(250);
    motor2.setSpeed(200);

    motor1.run(RELEASE);
    motor2.run(RELEASE);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    moveForward();
    current_distance = getDistance();
    if(current_distance <= 15){
      moveStop();
      delay(200);
      moveBackward();
      delay(500);
      turnRight();
      delay(500);
    }
}


void moveStop(){
    Serial.println("-- Stop --");
    motor1.run(RELEASE);
    motor2.run(RELEASE);
}

void moveBackward(){
    Serial.println("-- Backwards --");
    motor1.run(FORWARD);
    motor2.run(FORWARD);
}

void moveForward(){
    Serial.println("-- Forward --");
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
}

void turnLeft(){
    Serial.println("-- Left --");
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
}

void turnRight(){
    Serial.println("-- Right --");
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
}

// https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}
