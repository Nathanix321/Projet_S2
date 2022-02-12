/**
 * @file main.cpp
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 *        
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include "Timer.h"
#include "accelerometre.h"
#include "memory.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop()
{
  // put your main code here, to run repeatedly:
}




/**
 * Possibiliter de reception
 *  -<1> //wire
 *  -<2> //Padluck
 *  -<3> //Memory
 *  -<4> //Keypad
 *  -<5> //accelerometre
 *  -<6,/a determiner/> //LED
 *  -<7,ON/OFF> //moteur vibrant
 *  
 * Possibiliter de d'envoie
 *  -<1,wire_analog_value> //wire
 *  -<2,padluck_analog_Xvalue,padluck_analog_Yvalue> //Padluck
 *  -<3,memory_analog_value> //Memory
 *  -<4,keypad_digital_value> //Keypad
 *  -<5,accelerometre_analog_Xvalue,accelerometre_analog_Yvalue,accelerometre_analog_Zvalue> //accelerometre
 */