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
#ifndef MEMORY_H_
#define MEMORY_H_

#include <Arduino.h>
#include <ShiftRegister74HC595.h>

#define SEGMENT_ID 0
#define BARGRAPH_ID 1

#define SEGMENT_MASQUE   0b10000000
#define NIVEAU_MASQUE    0b11100000

#define SEGMENT_INITIALE 0b01111111
#define SEGMENT_0        0b01000000
#define SEGMENT_1        0b01111001
#define SEGMENT_2        0b00100100
#define SEGMENT_3        0b00110000
#define SEGMENT_4        0b00011001
#define SEGMENT_5        0b00010010
#define SEGMENT_6        0b00000011
#define SEGMENT_7        0b01111000
#define SEGMENT_8        0b00000000
#define SEGMENT_9        0b00010000

#define NIVEAU_1         0b00000001
#define NIVEAU_2         0b00000011
#define NIVEAU_3         0b00000111
#define NIVEAU_4         0b00001111
#define NIVEAU_5         0b00011111

void pciSetup(uint8_t pin);


class Memory 
{
public:
    Memory(ShiftRegister74HC595<2> &_gestionLED, uint8_t analogReadPin, uint8_t sendReadPin);
    Memory();
    ~Memory();

    void MemoryInit();
    void setLevel(uint8_t level);
    void setNumber(uint8_t number);
    bool getSendBTNState();
    void setSendBTNState(bool state);
    uint16_t getSwitchState();
    

private:
    ShiftRegister74HC595<2> gestionLED;

};







#endif /* MEMORY_H_ */