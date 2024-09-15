#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "RobotX";
const char* password = "123456789";

ESP8266WebServer server(80);

void sendCommandToArduino(String command) {
    Serial.write(command.c_str());
    Serial.write('\n');  // End the command with a newline for Arduino to read
}

void handleRoot() {
 String html = "<!DOCTYPE html>"
              "<html>"
              "<head>"
              "<title>Motor Control</title>"
              "<meta charset=\"UTF-8\">"
              "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
              "<style>"
              "body {"
              "    font-family: Arial, sans-serif;"
              "}"
              ".container {"
              "    max-width: 800px;"
              "    margin: 0 auto;"
              "    padding: 20px;"
              "}"
              ".card {"
              "    border: 1px solid #ccc;"
              "    border-radius: 5px;"
              "    padding: 20px;"
              "}"
              ".card-header {"
              "    font-weight: bold;"
              "    margin-bottom: 10px;"
              "}"
              ".btn {"
              "    padding: 10px 20px;"
              "    font-size: 16px;"
              "    border-radius: 5px;"
              "    cursor: pointer;"
              "    background-color: #3498db;"
              "    color: #fff;"
              "    border: none;"
              "}"
              ".btn-group {"
              "    display: flex;"
              "    gap: 10px;"
              "}"
              ".form-group {"
              "    margin-bottom: 15px;"
              "}"
              ".form-group label {"
              "    display: block;"
              "    margin-bottom: 5px;"
              "}"
              ".input-group {"
              "    display: flex;"
              "    align-items: center;"
              "    border: 1px solid #ccc;"
              "    border-radius: 5px;"
              "    overflow: hidden;"
              "}"
              ".input-group input {"
              "    border: none;"
              "    padding: 10px;"
              "    flex-grow: 1;"
              "}"
              ".input-group span {"
              "    background-color: #e9ecef;"
              "    padding: 10px;"
              "    border-right: 1px solid #ccc;"
              "}"
              ".input-group .btn {"
              "    border-radius: 0;"
              "    margin: 0;"
              "    height: 100%;"
              "}"
              ".mb-3 {"
              "    margin-bottom: 0.5em;"
              "}"
              "</style>"
              "</head>"
              "<body>"
              "<!-- All Motors Control -->"
              "<div class=\"container\">"
              "<div class=\"card\">"
              "<div class=\"card-header\">"
              "<h2>All Motors</h2>"
              "</div>"
              "<div class=\"card-body\">"
              "<div class=\"btn-group mb-3\">"
              "<button class=\"btn\" onclick=\"controlAllMotors('forward')\">All Motors Forward</button>"
              "<button class=\"btn\" onclick=\"controlAllMotors('backward')\">All Motors Backward</button>"
              "<button class=\"btn\" onclick=\"controlAllMotors('stop')\">All Motors Stop</button>"
              "</div>"
              "<div class=\"form-group\">"
              "<label for=\"allSpeed\">Speed:</label>"
              "<div class=\"input-group\">"
              "<span>Speed</span>"
              "<input type=\"number\" id=\"allSpeed\" placeholder=\"0-255\" min=\"0\" max=\"255\">"
              "<button class=\"btn\" onclick=\"setAllMotorsSpeed()\">Set All Motors Speed</button>"
              "</div>"
              "</div>"
              "<button class=\"btn\" onclick=\"fetch('/toggle-led')\">Toggle LED</button>"
              "</div>"
              "</div>"
              "</div>"
              "<!-- Motor Controls -->"
              "<div id=\"motorsContainer\" class=\"container\"></div>"
              "<script>"
              "const numberOfMotors = 4;"
              "const motorsContainer = document.getElementById('motorsContainer');"
              "function createMotorControls(motorNumber) {"
              "    return `"
              "        <div class=\"card\">"
              "            <div class=\"card-header\">"
              "                <h2>Motor ${motorNumber}</h2>"
              "            </div>"
              "            <div class=\"card-body\">"
              "                <div class=\"btn-group mb-3\">"
              "                    <button class=\"btn\" onclick=\"controlMotor(${motorNumber}, 'forward')\">Motor ${motorNumber} Forward</button>"
              "                    <button class=\"btn\" onclick=\"controlMotor(${motorNumber}, 'backward')\">Motor ${motorNumber} Backward</button>"
              "                    <button class=\"btn\" onclick=\"controlMotor(${motorNumber}, 'stop')\">Motor ${motorNumber} Stop</button>"
              "                </div>"
              "                <div class=\"form-group\">"
              "                    <label for=\"speed${motorNumber}\">Speed:</label>"
              "                    <div class=\"input-group\">"
              "                        <span>Speed</span>"
              "                        <input type=\"number\" id=\"speed${motorNumber}\" placeholder=\"0-255\" min=\"0\" max=\"255\">"
              "                        <button class=\"btn\" onclick=\"setMotorSpeed(${motorNumber})\">Set Speed</button>"
              "                    </div>"
              "                </div>"
              "            </div>"
              "        </div>"
              "    `;"
              "}"
              "for (let i = 1; i <= numberOfMotors; i++) {"
              "    motorsContainer.innerHTML += createMotorControls(i);"
              "}"
              "function controlAllMotors(action) {"
              "    fetch(`/m1/direction/${action}`);"
              "    fetch(`/m2/direction/${action}`);"
              "    fetch(`/m3/direction/${action}`);"
              "    fetch(`/m4/direction/${action}`);"
              "}"
              "function setAllMotorsSpeed() {"
              "    const speed = document.getElementById('allSpeed').value;"
              "    fetch(`/m1/speed?speed=${speed}`);"
              "    fetch(`/m2/speed?speed=${speed}`);"
              "    fetch(`/m3/speed?speed=${speed}`);"
              "    fetch(`/m4/speed?speed=${speed}`);"
              "}"
              "function controlMotor(motor, action) {"
              "    fetch(`/m${motor}/direction/${action}`);"
              "}"
              "function setMotorSpeed(motor) {"
              "    const speed = document.getElementById(`speed${motor}`).value;"
              "    fetch(`/m${motor}/speed?speed=${speed}`);"
              "}"
              "</script>"
              "</body>"
              "</html>";

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

    // Motor 2
    server.on("/m2/direction/forward", handleMotor2Forward);
    server.on("/m2/direction/backward", handleMotor2Backward);
    server.on("/m2/direction/stop", handleMotor2Stop);
    server.on("/m2/speed", handleMotor2Speed);

    // Motor 3
    server.on("/m3/direction/forward", handleMotor3Forward);
    server.on("/m3/direction/backward", handleMotor3Backward);
    server.on("/m3/direction/stop", handleMotor3Stop);
    server.on("/m3/speed", handleMotor3Speed);

    // Motor 4
    server.on("/m4/direction/forward", handleMotor4Forward);
    server.on("/m4/direction/backward", handleMotor4Backward);
    server.on("/m4/direction/stop", handleMotor4Stop);
    server.on("/m4/speed", handleMotor4Speed);

    // Toggle LED
    server.on("/toggle-led", handleToggleLed);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
