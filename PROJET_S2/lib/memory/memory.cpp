/**
 * @file memory.c
 * @author Shawn Miller (mils2203@usherbrooke.ca)
 * @brief
 * @version 0.1
 * @date 2022-02-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "memory.hpp"

uint8_t send_pin;
uint8_t switch_pin;
bool sendFlag;

/**
 * @brief Construct a new Memory:: Memory object
 *
 * @param _gestionLED
 * @param switchReadPin
 * @param sendReadPin
 */
Memory::Memory(ShiftRegister74HC595<1> *_gestionLED, uint8_t switchReadPin, uint8_t sendReadPin)
{
    delete gestionLED;
    gestionLED = _gestionLED;

    pinMode(switchReadPin, INPUT);

    pinMode(sendReadPin, INPUT);
    send_pin = sendReadPin;
    switch_pin = switchReadPin;
    sendFlag = false;
}

/**
 * @brief Destroy the Memory:: Memory object
 *
 */
Memory::~Memory()
{
    delete gestionLED;
}

/**
 * @brief 
 * 
 * @param level 
 */
void Memory::setLevel(uint8_t level)
{
}

/**
 * @brief 
 * 
 * @param number 
 */
void Memory::setNumber(uint8_t number)
{

}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Memory::getSendBTNState()
{
    return sendFlag;
}

/**
 * @brief 
 * 
 * @return uint16_t 
 */
uint16_t Memory::getSwitchState()
{
    return analogRead(switch_pin);
}

/**
 * @brief
 *
 * @param pin
 */
void pciSetup(uint8_t pin)
{
    *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin)); // enable pin
    PCIFR |= bit(digitalPinToPCICRbit(pin));                   // clear any outstanding interrupt
    PCICR |= bit(digitalPinToPCICRbit(pin));                   // enable interrupt for the group
}

/**
 * @brief Construct a new ISR object
 *
 */
ISR(PCINT2_vect)
{
    if (digitalRead(send_pin))
    {
        sendFlag = true;
    }
}
