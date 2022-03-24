#include "wire.hpp"

Wire::Wire(uint8_t switchPin1)
{
    this->analogPin1 = analogPin1;
}

Wire::~Wire()
{
}
 
int Wire::getCutWires()
{
    format = analogRead(analogPin1);
    int wires = 0;
 
    if(format%2!=0)
    {
      wires |= 1;
    }
    format/=2;
    if(format%2!=0)
    {
       wires |= 2;
    }
    format/=2;
    if(format%2!=0)
    {
      wires |= 4;
    }
    format/=2;
    if(format%2!=0)
    {
      wires |= 8;
    }
    return wires;
}