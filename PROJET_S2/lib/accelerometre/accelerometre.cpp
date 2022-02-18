/**
 * @file accelerometre.c
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @brief
 * @version 0.1
 * @date 2022-02-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "accelerometre.hpp"

/**
 * @brief Construct a new Accelerometre:: Accelerometre object
 * 
 */
Accelerometre::Accelerometre(){

}

/**
 * @brief Construct a new Accelerometre:: Accelerometre object
 * 
 * @param A_xPin 
 * @param A_yPin 
 * @param A_zPin 
 */
Accelerometre::Accelerometre(uint8_t A_xPin, uint8_t A_yPin, uint8_t A_zPin)
{
    pinX = A_xPin;
    pinY = A_yPin;
    pinZ = A_zPin;

    pinMode(pinX, INPUT);
    pinMode(pinY, INPUT);
    pinMode(pinZ, INPUT);
}
/**
 * @brief Destroy the Accelerometre:: Accelerometre object
 * 
 */
Accelerometre::~Accelerometre()
{
}

/**
 * @brief get voltage of the X axe
 * 
 * @return voltage 
 */
int Accelerometre::getX_value()
{
    return analogRead(pinX);
}

/**
 * @brief get voltage of the Y axe
 * 
 * @return voltage 
 */
int Accelerometre::getY_value()
{
    return analogRead(pinY);
}

/**
 * @brief get voltage of the Z axe
 * 
 * @return voltage 
 */
int Accelerometre::getZ_value()
{
    return analogRead(pinZ);
    
}