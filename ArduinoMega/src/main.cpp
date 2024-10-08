#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"

Motor motor1(38, 40, 6);
Motor motor2(42, 44, 5);
Motor motor3(52, 50, 3);
Motor motor4(46, 48, 4);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{
    Serial.begin(9600);  // For Serial Monitor
    Serial1.begin(9600); // Communication with NodeMCU

    motor1.setSpeed(70);
    motor2.setSpeed(70);
    motor3.setSpeed(70);
    motor4.setSpeed(70);

    servo1.attach(8);
    servo2.attach(9);
    servo3.attach(10);
    servo4.attach(11);

    pinMode(13, OUTPUT); // Built-in LED on Arduino
}

void loop()
{
    servo1.write(90);
    if (Serial1.available())
    {
        String command = Serial1.readStringUntil('\n');
        command.trim();

        if (command == "M1_FORWARD")
        {
            motor1.forward();
            Serial.println("Motor 1 Forward");
        }
        else if (command == "M1_BACKWARD")
        {
            motor1.backward();
            Serial.println("Motor 1 Backward");
        }
        else if (command == "M1_STOP")
        {
            motor1.stop();
            Serial.println("Motor 1 Stopped");
        }
        else if (command.startsWith("M1_SPEED:"))
        {
            String speed = command.substring(command.indexOf(':') + 1);
            motor1.setSpeed(speed.toInt());
            Serial.println("Motor 1 Speed: " + speed);
        }
        else if (command.startsWith("S1_ANGLE:"))
        {
            String angle = command.substring(command.indexOf(':') + 1);
            servo1.write(angle.toInt());
            Serial.println("Servo 1 Angle: " + angle);
        }
        else if (command == "M2_FORWARD")
        {
            motor2.forward();
            Serial.println("Motor 2 Forward");
        }
        else if (command == "M2_BACKWARD")
        {
            motor2.backward();
            Serial.println("Motor 2 Backward");
        }
        else if (command == "M2_STOP")
        {
            motor2.stop();
            Serial.println("Motor 2 Stopped");
        }
        else if (command.startsWith("M2_SPEED:"))
        {
            String speed = command.substring(command.indexOf(':') + 1);
            motor2.setSpeed(speed.toInt());
            Serial.println("Motor 2 Speed: " + speed);
        }
        else if (command.startsWith("S2_ANGLE:"))
        {
            String angle = command.substring(command.indexOf(':') + 1);
            servo2.write(angle.toInt());
            Serial.println("Servo 2 Angle: " + angle);
        }
        else if (command == "M3_FORWARD")
        {
            motor3.forward();
            Serial.println("Motor 3 Forward");
        }
        else if (command == "M3_BACKWARD")
        {
            motor3.backward();
            Serial.println("Motor 3 Backward");
        }
        else if (command == "M3_STOP")
        {
            motor3.stop();
            Serial.println("Motor 3 Stopped");
        }
        else if (command.startsWith("M3_SPEED:"))
        {
            String speed = command.substring(command.indexOf(':') + 1);
            motor3.setSpeed(speed.toInt());
            Serial.println("Motor 3 Speed: " + speed);
        }
        else if (command.startsWith("S3_ANGLE:"))
        {
            String angle = command.substring(command.indexOf(':') + 1);
            servo3.write(angle.toInt());
            Serial.println("Servo 3 Angle: " + angle);
        }
        else if (command == "M4_FORWARD")
        {
            motor4.forward();
            Serial.println("Motor 4 Forward");
        }
        else if (command == "M4_BACKWARD")
        {
            motor4.backward();
            Serial.println("Motor 4 Backward");
        }
        else if (command == "M4_STOP")
        {
            motor4.stop();
            Serial.println("Motor 4 Stopped");
        }
        else if (command.startsWith("M4_SPEED:"))
        {
            String speed = command.substring(command.indexOf(':') + 1);
            motor4.setSpeed(speed.toInt());
            Serial.println("Motor 4 Speed: " + speed);
        }
        else if (command.startsWith("S4_ANGLE:"))
        {
            String angle = command.substring(command.indexOf(':') + 1);
            servo4.write(angle.toInt());
            Serial.println("Servo 4 Angle: " + angle);
        }
        else if (command == "TOGGLE_LED")
        {
            digitalWrite(13, !digitalRead(13)); // Toggle Arduino built-in LED
            Serial.println("LED Toggled on Arduino");
        }
    }
}
