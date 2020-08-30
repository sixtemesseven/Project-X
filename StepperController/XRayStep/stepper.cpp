#include "Arduino.h"
#include "stepper.h"


stepper::stepper(int stepPin, int dirPin, int enPin, int mircrostep, float movePerFullStep, bool endstop, int stepTime)
{
   _stepTime = stepTime;
   _stepPin = stepPin;
   _dirPin = dirPin;
   _enPin = enPin;
   _movePerStep = movePerFullStep/mircrostep; //Calculate movement per step impulse
   _endstop = endstop; //Endstop Flat
}

void stepper::initialize()
{
   pinMode(_stepPin, OUTPUT);
   pinMode(_dirPin, OUTPUT);
   pinMode(_enPin, OUTPUT);
}

//Enable Endstops if available
void stepper::endstop(int stopPinStart, int stopPinStop)
{
  _stopPinStart = stopPinStart;
  _stopPinStop = stopPinStop;
  pinMode(_stopPinStart, OUTPUT);
  pinMode(_stopPinStop, OUTPUT);
  _endstopsEn = true;
  return;
}

//Return the step counter
int stepper::getStepCounter()
{
  return _stepCount;
}

float stepper::getPosition()
{
  return _stepCount * _movePerStep;
}

float stepper::getAngle()
{
  float pos = _stepCount * _movePerStep;
  int rotations = (int)(pos / 360);
  pos -= rotations*360;
  if(pos < 0)
  {
    pos += 360;
  }
  return pos;
}

void stepper::rotateToAngle(float deg)
{
  float current = getAngle();
  float moveDeg = current-deg;
  rotateByDegrees(moveDeg);  
  return;
}
  
float stepper::rotateByDegrees(float deg)
{
  int DoSteps = (int)(deg / _movePerStep);
  int dir = false;
  if(DoSteps < 0) 
  {
    dir = true;
  };

  manuStep(abs(DoSteps), dir);
  return getAngle();
}

//Update target Angle
float stepper::setTargetAngle(float deg)
{
  _targetAngle = deg;
}

void stepper::moveStepsToTargetAngle(int steps)
{
  float angle = getAngle();
  bool Direction;
  if((angle - _deadZone) > _targetAngle)
  {
    manuStep(steps, false);
  }
  if((angle + _deadZone) < _targetAngle)
  {
    manuStep(steps, true);
  }
  return;
}

//Do a simple manual step
void stepper::manuStep(int steps, bool dir)
{
  //Set direction
  digitalWrite(_dirPin, LOW);
  int counterDir = -1;
  if(dir == true)
  {
    digitalWrite(_dirPin, HIGH);
    counterDir = 1;
  }
  //Enable Stepper
  digitalWrite(_enPin, LOW); //Enable is inverted
  digitalWrite(_stepPin, LOW);
  //Stepper Loop
  for(int i = 0; i < steps; i++)
  {
    _stepCount += counterDir; //Update global step counter
    //Stepper Commands
    digitalWrite(_stepPin, HIGH);
    delay((int)(_stepTime/2));
    digitalWrite(_stepPin, LOW);
    delay((int)(_stepTime/2));
  }
  //Disable steppper
  digitalWrite(_enPin, HIGH);
  return;
}
