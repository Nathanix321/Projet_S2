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
#ifndef WIRE_H_
#define WIRE_H_
 
#include <Arduino.h>

#define INCREMENTVOLTAGE 65.9835
 
class Wire 
{
public:
    Wire(uint8_t analogPin1);
 
    ~Wire();
 
    int getCutWires();
    int formatvoltage(float voltage);
 
private:
    int format;
    uint8_t analogPin1;
};

#endif /* WIRE_H_ */
