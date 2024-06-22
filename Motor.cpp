#include "Motor.h"
volatile long  Motor::_encoderPulses= 0;

Motor*Motor::_instance = nullptr;
Motor::Motor(int motorPinA, int motorPinB, int encoderPinA, int encoderPinB):_motorPinA(motorPinA),_motorPinB(motorPinB),_encoderPinA(encoderPinA),_encoderPinB(encoderPinB),_lastValidRPM(0),_lastCalculationTime(0){_instance = this;}

  
void Motor::encoderISR(){
  if(digitalRead(_instance->_encoderPinB) == HIGH){
    _encoderPulses++;
  }else{_encoderPulses--;}
}

void Motor::setupMotor() {
  pinMode(_motorPinA, OUTPUT);
  pinMode(_motorPinB, OUTPUT);
  pinMode(_encoderPinA, INPUT_PULLUP);
  pinMode(_encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_encoderPinA), Motor::encoderISR, CHANGE);
}


float Motor::calculateRPM() {
  

  unsigned long currentTime = millis();
  unsigned long timeDifference = currentTime - _lastCalculationTime;
  if (timeDifference >= 1000) {
    noInterrupts();
    long pulses = _encoderPulses;
    _encoderPulses = 0;
    interrupts();
    _lastValidRPM = (pulses / 30.0) * 60.0;
    _lastCalculationTime = currentTime;
     
  } 
    return _lastValidRPM ;

 
}