#include "stepper.h"
#include <AccelStepper.h>

#define XStep A0
#define XDir A1
#define XEn 38

#define YStep 50
#define YDir 51
#define YEn 52

//Serial interupt global variables
const int serialInputCharArrayLenght = 25;
char serialInputCharArray[serialInputCharArrayLenght] = {'\0'};
int serialInputCharArrayCounter = 0;
bool commandComplete = false;

//Command array global variables
char commandID = ' ';
float command[10] = {0};

stepper xAxis(XStep, XDir, XEn, 8, 1.8, false, 2);
stepper yAxis(YStep, YDir, YEn, 8, 1.8, false, 2);
stepper stepperArray[2] = {xAxis, yAxis};



void setup() {
  Serial.begin(115200);
  xAxis.initialize();
}

void loop() {
  if(checkCommand(command) == true)
  {
    for(int ax = 0; ax < sizeof(stepperArray); ax++)
    {
      stepperArray[ax].setTargetAngle(command[ax]);
    }
  }
  stepperArray[0].moveStepsToTargetAngle(1);
}

//Checks if new command has arrived
//Input:  Serial, reference to value, reference to id
//Return: True if new command is available
bool checkCommand(float value[])
{
  if (commandComplete == true)
  {
    char f_commandID = serialInputCharArray[0];
    serialInputCharArray[0] = '0';
    float f_command = atof(serialInputCharArray);
    switch (f_commandID) {
      case 'x':
        value[0] = f_command;
        break;
      case 'y':
        value[1] = f_command;
        break;
    }
    
    
    commandComplete = false;
    clearCharArray(serialInputCharArrayLenght, serialInputCharArray); //Deletes the Serial Buffer Array
    return true;
  }
  return false;
}

void serialEvent()
{
  while (Serial.available() && commandComplete == false) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      commandComplete = true;
      serialInputCharArrayCounter = 0;
      break;
    }
    serialInputCharArray[serialInputCharArrayCounter] = inChar;
    serialInputCharArrayCounter++;
  }
}



void clearCharArray(int len, char arr[])
{
  for (int i = 0; i < len; i++)
  {
    arr[i] = '\0';
  }
  return;
}
