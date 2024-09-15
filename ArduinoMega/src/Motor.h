#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int pin1, pin2, enablePin;
    int speed;
    
public:
    Motor(int p1, int p2, int en);
    void forward();
    void backward();
    void stop();
    void setSpeed(int s);
};

#endif
