#ifndef Motor_h
#define Motor_h

#include"Arduino.h"

class Motor{
  public:
    Motor(int motorPinA, int motorPinB, int encoderPinA, int encoderPinB);
    void setupMotor();
    float calculateRPM();
    static void encoderISR();
  private:
    int _motorPinA, _motorPinB, _encoderPinA, _encoderPinB;
    static volatile long _encoderPulses;
    float _lastValidRPM;
    unsigned long _lastCalculationTime;
    static Motor*_instance;
    

};

#endif