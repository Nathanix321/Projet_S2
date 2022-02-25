/**
 * @file memory.h
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MEMORY_H_
#define MEMORY_H_

#include <Arduino.h>
#include "ShiftRegister74HC595.h"

class Memory
{ // The class
private:

ShiftRegister74HC595<1> * gestionLED;

void pciSetup(uint8_t pin);

public: // Access specifier
  Memory(ShiftRegister74HC595<1> *_gestionLED, uint8_t switchReadPin, uint8_t sendReadPin);
  ~Memory();

  void setLevel(uint8_t level);
  void setNumber(uint8_t number);
  bool getSendBTNState();
  uint16_t getSwitchState();

};






#endif /* MEMORY_H_ */