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

/**
 * @brief Construct a new Keypad:: Keypad object
 * 
 * @param switchPin1 
 * @param switchPin2 
 * @param switchPin3 
 * @param switchPin4 
 */
Keypad::Keypad(uint8_t switchPin1, uint8_t switchPin2, uint8_t switchPin3, uint8_t switchPin4)
{
        pinMode(switchPin1, INPUT);
        pinMode(switchPin2, INPUT);
        pinMode(switchPin3, INPUT);
        pinMode(switchPin4, INPUT);

        this->switchPin1 = switchPin1;
        this->switchPin2 = switchPin2;
        this->switchPin3 = switchPin3;
        this->switchPin4 = switchPin4;
}

/**
 * @brief Destroy the Keypad:: Keypad object
 * 
 */
Keypad::~Keypad()
{
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
int Keypad::detecterTouche()
{
        bool value_switchPin1 = digitalRead(switchPin1);
        bool value_switchPin2 = digitalRead(switchPin2);
        bool value_switchPin3 = digitalRead(switchPin3);
        bool value_switchPin4 = digitalRead(switchPin4);

        if (value_switchPin1 == HIGH)
                return 1;
        else if (value_switchPin2 == HIGH)
                return 2;
        else if (value_switchPin3 == HIGH)
                return 3;
        else if (value_switchPin4 == HIGH)
                return 4;
        else
                return 0;
}