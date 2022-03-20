/**
 * @file keypad.h
 * @author Alexandre Falardeau (alexandre.falardeau@usherbrooke.ca)
 * @author Justin Houde (justin.houde@usherbrooke.ca)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "KeyPad.hpp"

Keypad :: Keypad(uint8_t switchPin1, uint8_t switchPin2, uint8_t switchPin3, uint8_t switchPin4)
{
  this->switchPin1 = switchPin1;
  this->switchPin2 = switchPin2;
  this->switchPin3 = switchPin3;
  this->switchPin4 = switchPin4;
}

Keypad::~Keypad()
{
}

int Keypad :: detecterTouche()
{
   if (switchPin1 == HIGH)
   {
           return 1;
   }

   else if (switchPin2 == HIGH)
   {
           return 2;
   }

   else if (switchPin3 == HIGH)
   {
           return 3;
   }

   else if (switchPin4 == HIGH)
   {
           return 4;
   }
   
   else
        return 0;


}