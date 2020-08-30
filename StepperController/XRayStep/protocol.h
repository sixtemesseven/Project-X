#ifndef Protocol_h
#define Protocol_h

#include "Arduino.h"


class protocol
{
  public:
    protocol(HardwareSerial& device, int _commandArrayLenght, int baudRate);   
    bool newCommand();                                                                
    float readAxis();                                                                
    void initialize();

  private:  
    //Variables  
    int _commandArrayLenght = 4;
    float _commandedValues[25] = {0};                                         
    char _commandIdentification[25] ={'X','Y','Z','H'};                       
    bool _newCommandFlag = false;       
    HardwareSerial& _device;                                    
    
    //Functions
    bool checkModulo(char *arr);
    bool checkForData();
    char* getNewData();
    void updateComandValue(char *arr, bool valid);
    int _baudRate = 9600;
};

#endif
