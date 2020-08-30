#include "protocol.h"


protocol::protocol(HardwareSerial& device, int commandArrayLenght, int baudRate)
{
  _baudRate = baudRate;
  _commandArrayLenght = commandArrayLenght;
}

void protocol::initialize()
{
  _device.begin(_baudRate);  
}
                
bool protocol::newCommand();                                                               
float protocol::readAxis();                                                                
bool protocol::checkModulo(char *arr);
bool protocol::checkForData();
char* protocol::getNewData();
void protocol::updateComandValue(char *arr, bool valid);
