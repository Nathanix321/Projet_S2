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

bool flagAccelerometre;
uint16_t comptTimer;

/**
 * @brief Construct a new Accelerometre:: Accelerometre object
 *
 */
Accelerometre::Accelerometre()
{
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

  flagAccelerometre = false;
  comptTimer = 0;

  _accelerometreTimerInit();
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

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool Accelerometre::getStateFlag()
{
  return flagAccelerometre;
}

/**
 * @brief
 *
 * @param state
 */
void Accelerometre::setStateFlag(bool state)
{
  flagAccelerometre = state;
}

/**
 * @brief initialisation du timer0 pour l'accelerometre
 *
 */
void Accelerometre::_accelerometreTimerInit()
{
  comptTimer = 0;
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01) + (1 << CS00); // F_CPU/64 Hz -> 4us
  OCR0A = 250;                         // compare match a tous les 1ms
  TIMSK0 = (1 << OCIE0A);              // active interupt A
}

/**
 *	@brief Fonction d'interuption du TIMER 0 qui compte jusq'a 100ms
 *	@param compare le vecteur OCR0A
 *	@param n/a
 *	@return n/a
 */
ISR(TIMER0_COMPA_vect)
{
  comptTimer++;
  if (comptTimer >= 100)
  {
    comptTimer -= 100;
    flagAccelerometre = true;
  }
  //Serial.println(comptTimer);
}