#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int p1, int p2, int en) : pin1(p1), pin2(p2), enablePin(en), speed(0) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
}

void Motor::forward() {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(enablePin, speed);
}

void Motor::backward() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(enablePin, speed);
}

void Motor::stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    analogWrite(enablePin, 0);
}

void Motor::setSpeed(int s) {
    speed = constrain(s, 0, 255);
    analogWrite(enablePin, speed);
}
