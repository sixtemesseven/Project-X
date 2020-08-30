#ifndef Stepper_h
#define Stepper_h

#include "Arduino.h"


class stepper
{
  public:
    stepper(int stepPin, int dirPin, int enPin, int mircrostep, float movePerFullStep, bool endstop, int stepTime);
    void endstop(int stopPinStart, int stopPinStop);
    void initialize();
    float getPosition(); // Get position im [mm] 
    float getAngle(); //Get postition in degree (-180 to 180)

    void manuStep(int steps, bool dir); //Rotates steps in direction
    float rotateByDegrees(float deg); //Rotates an angle, returns position angle
    void rotateToAngle(float deg);

    float setTargetAngle(float deg);
    void moveStepsToTargetAngle(int steps);

  private:    
    int getStepCounter(); //Get Global step counter
    int _stepPin, _dirPin, _enPin;
    double _movePerStep;
    bool _endstop;
    int _stopPinStart = 0; 
    int _stopPinStop = 0;
    bool _endstopsEn = false;
    long long int _stepCount = 0;
    int _stepTime;
    float _targetAngle = 0;
    float _currentAngle = 0;
    float _deadZone = 0.1;
};

#endif
