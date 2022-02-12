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


/**
 * @brief Initialise les pins de l'accelerometres
 * 
 */
void accelerometreInit();

/**
 * @brief Get the X value object
 * 
 * @return double 
 */
double getX_value();

/**
 * @brief Get the Y value object
 * 
 * @return double 
 */
double getY_value();

/**
 * @brief Get the Z value object
 * 
 * @return double 
 */
double getZ_value();




#endif /* ACCELEROMETRE_H_ */