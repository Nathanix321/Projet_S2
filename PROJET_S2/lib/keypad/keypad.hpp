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

#ifndef KEYPAD_H_
#define KEYPAD_H_

//H22-S2-PROJET-P09
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Keypad
{
public:
    Keypad(uint8_t switchPin1, uint8_t switchPin2, uint8_t switchPin3, uint8_t switchPin4);
    Keypad();
    ~Keypad();

    int detecterTouche();

private:
    int switchPin1;
    int switchPin2;
    int switchPin3;
    int switchPin4;

    bool value_switchPin1;
    bool value_switchPin2;
    bool value_switchPin3;
    bool value_switchPin4;

};

#endif /* KEYPAD_H_ */
