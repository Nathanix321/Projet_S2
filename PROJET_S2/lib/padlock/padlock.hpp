/**
 * @file padlock.hpp
 * @author Gabriel Rioux (you@domain.com)
 * @brief Ficher h de la classe du padlock
 * @version 0.1
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PADLOCK_H_
#define PADLOCK_H_
#include <Arduino.h>

#define VAL_POT_BAS 400
#define VAL_POT_HAUT 600
/**
 * Définition de la classe Padlock 
 * 
 */
class Padlock
{
public:

Padlock(uint8_t inputX, uint8_t intputY);
~Padlock();
//int getPinX();
//int getPinY();
uint8_t getPosition();
private:
uint8_t analogPinX;
uint8_t analogPinY;

};

#endif