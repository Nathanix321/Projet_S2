/**
 * @file accelerometre.h
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @brief
 * @version 0.1
 * @date 2022-02-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ACCELEROMETRE_H_
#define ACCELEROMETRE_H_

#include <Arduino.h>

class Accelerometre
{ // The class
private:
  uint8_t pinX;
  uint8_t pinY;
  uint8_t pinZ;

  void _accelerometreTimerInit();

public: // Access specifier
  Accelerometre();
  Accelerometre(uint8_t A_xPin, uint8_t A_yPin, uint8_t A_zPin);
  ~Accelerometre();
  int getX_value();
  int getY_value();
  int getZ_value();
  bool getStateFlag();
  void setStateFlag(bool state);
};

#endif /* ACCELEROMETRE_H_ */