#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

const char* ssid = "RobotX";
const char* password = "123456789";

ESP8266WebServer server(80);

void sendCommandToArduino(String command) {
    Serial.write(command.c_str());
    Serial.write('\n');  // End the command with a newline for Arduino to read
}

void handleRoot() {
    server.send(200, "text/html", html);
}

// Motor 1
void handleMotor1Forward() {
    sendCommandToArduino("M1_FORWARD");
    server.send(200, "text/plain", "Motor 1 Forward");
}

void handleMotor1Backward() {
    sendCommandToArduino("M1_BACKWARD");
    server.send(200, "text/plain", "Motor 1 Backward");
}

void handleMotor1Stop() {
    sendCommandToArduino("M1_STOP");
    server.send(200, "text/plain", "Motor 1 Stopped");
}

void handleMotor1Speed() {
    String speed = server.arg("speed");
    sendCommandToArduino("M1_SPEED:" + speed);
    server.send(200, "text/plain", "Motor 1 Speed set to " + speed);
}

// Motor 2
void handleMotor2Forward() {
    sendCommandToArduino("M2_FORWARD");
    server.send(200, "text/plain", "Motor 2 Forward");
}

void handleMotor2Backward() {
    sendCommandToArduino("M2_BACKWARD");
    server.send(200, "text/plain", "Motor 2 Backward");
}

void handleMotor2Stop() {
    sendCommandToArduino("M2_STOP");
    server.send(200, "text/plain", "Motor 2 Stopped");
}

void handleMotor2Speed() {
    String speed = server.arg("speed");
    sendCommandToArduino("M2_SPEED:" + speed);
    server.send(200, "text/plain", "Motor 2 Speed set to " + speed);
}

// Motor 3
void handleMotor3Forward() {
    sendCommandToArduino("M3_FORWARD");
    server.send(200, "text/plain", "Motor 3 Forward");
}

void handleMotor3Backward() {
    sendCommandToArduino("M3_BACKWARD");
    server.send(200, "text/plain", "Motor 3 Backward");
}

void handleMotor3Stop() {
    sendCommandToArduino("M3_STOP");
    server.send(200, "text/plain", "Motor 3 Stopped");
}

void handleMotor3Speed() {
    String speed = server.arg("speed");
    sendCommandToArduino("M3_SPEED:" + speed);
    server.send(200, "text/plain", "Motor 3 Speed set to " + speed);
}

// Motor 4
void handleMotor4Forward() {
    sendCommandToArduino("M4_FORWARD");
    server.send(200, "text/plain", "Motor 4 Forward");
}

void handleMotor4Backward() {
    sendCommandToArduino("M4_BACKWARD");
    server.send(200, "text/plain", "Motor 4 Backward");
}

void handleMotor4Stop() {
    sendCommandToArduino("M4_STOP");
    server.send(200, "text/plain", "Motor 4 Stopped");
}

void handleMotor4Speed() {
    String speed = server.arg("speed");
    sendCommandToArduino("M4_SPEED:" + speed);
    server.send(200, "text/plain", "Motor 4 Speed set to " + speed);
}

void handleServo1Angle(){
     String angle = server.arg("angle");
    sendCommandToArduino("S1_ANGLE:" + angle);
    server.send(200, "text/plain", "Seravo 1 Angle" + angle);
}

void handleServo2Angle() {
    String angle = server.arg("angle");
    sendCommandToArduino("S2_ANGLE:" + angle);
    server.send(200, "text/plain", "Servo 2 Angle: " + angle);
}

void handleServo3Angle() {
    String angle = server.arg("angle");
    sendCommandToArduino("S3_ANGLE:" + angle);
    server.send(200, "text/plain", "Servo 3 Angle: " + angle);
}

void handleServo4Angle() {
    String angle = server.arg("angle");
    sendCommandToArduino("S4_ANGLE:" + angle);
    server.send(200, "text/plain", "Servo 4 Angle: " + angle);
}


// Toggle LEDs
void handleToggleLed() {
    sendCommandToArduino("TOGGLE_LED");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // Toggle NodeMCU's built-in LED
    server.send(200, "text/plain", "LED Toggled on NodeMCU");
}

void setup() {
    Serial.begin(9600);  // Communication with Arduino
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("IP Address: ");
    Serial.println(IP);

    pinMode(LED_BUILTIN, OUTPUT);  // NodeMCU built-in LED

    server.on("/", handleRoot);

    // Motor 1
    server.on("/m1/direction/forward", handleMotor1Forward);
    server.on("/m1/direction/backward", handleMotor1Backward);
    server.on("/m1/direction/stop", handleMotor1Stop);
    server.on("/m1/speed", handleMotor1Speed);
     server.on("/s1/direction", handleServo1Angle);

    // Motor 2
    server.on("/m2/direction/forward", handleMotor2Forward);
    server.on("/m2/direction/backward", handleMotor2Backward);
    server.on("/m2/direction/stop", handleMotor2Stop);
    server.on("/m2/speed", handleMotor2Speed);
    server.on("/s2/direction", handleServo2Angle);
    // Motor 3
    server.on("/m3/direction/forward", handleMotor3Forward);
    server.on("/m3/direction/backward", handleMotor3Backward);
    server.on("/m3/direction/stop", handleMotor3Stop);
    server.on("/m3/speed", handleMotor3Speed);
    server.on("/s3/direction", handleServo3Angle);

    // Motor 4
    server.on("/m4/direction/forward", handleMotor4Forward);
    server.on("/m4/direction/backward", handleMotor4Backward);
    server.on("/m4/direction/stop", handleMotor4Stop);
    server.on("/m4/speed", handleMotor4Speed);
    server.on("/s4/direction", handleServo4Angle);
    // Toggle LED
    server.on("/toggle-led", handleToggleLed);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
