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
bool stateSWFlag;

/**
 * @brief Construct a new Memory:: Memory object
 *
 * @param _gestionLED
 * @param switchReadPin
 * @param sendReadPin
 */
Memory::Memory(ShiftRegister74HC595<2> &_gestionLED, uint8_t analogReadPin, uint8_t sendReadPin)
{
    gestionLED = _gestionLED;

    pinMode(analogReadPin, INPUT);

    pinMode(sendReadPin, INPUT);
    send_pin = sendReadPin;
    switch_pin = analogReadPin;
    stateSWFlag = false;
}

/**
 * @brief Destroy the Memory:: Memory object
 *
 */
Memory::~Memory()
{
}

/**
 * @brief affiche les possibilite possible pour le 7 segment et le bargraph
 * 
 */
void Memory::MemoryInit()
{
    setNumber(0);
    delay(250);

    setNumber(1);
    delay(250);

    setNumber(2);
    delay(250);

    setNumber(3);
    delay(250);

    setNumber(4);
    delay(250);

    setNumber(5);
    delay(250);

    setNumber(6);
    delay(250);

    setNumber(7);
    delay(250);

    setNumber(8);
    delay(250);

    setNumber(9);
    delay(250);

    setNumber(10);
    delay(250);

    setLevel(1);
    delay(250);

    setLevel(2);
    delay(250);

    setLevel(3);
    delay(250);

    setLevel(4);
    delay(250);

    setLevel(5);
    delay(250);

    setLevel(1);
    delay(250);
}

/**
 * @brief set le 7 segment selon le niveau en parametre
 *
 * @param level
 */
void Memory::setNumber(uint8_t number)
{
    uint8_t *DigitalValue = gestionLED.getAll();

    if (number == 0)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_0);
    else if (number == 1)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_1);
    else if (number == 2)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_2);
    else if (number == 3)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_3);
    else if (number == 4)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_4);
    else if (number == 5)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_5);
    else if (number == 6)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_6);
    else if (number == 7)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_7);
    else if (number == 8)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_8);
    else if (number == 9)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_9);
    else if (number == 10)
        DigitalValue[SEGMENT_ID] = ((SEGMENT_MASQUE & DigitalValue[SEGMENT_ID]) | SEGMENT_INITIALE);

    gestionLED.setAll(DigitalValue);
}

/**
 * @brief set le bar graph selon le niveau en parametre
 *
 * @param number
 */
void Memory::setLevel(uint8_t level)
{
    uint8_t *DigitalValue = gestionLED.getAll();

    if (level == 1)
        DigitalValue[BARGRAPH_ID] = ((NIVEAU_MASQUE & DigitalValue[BARGRAPH_ID]) | NIVEAU_1);
    else if (level == 2)
        DigitalValue[BARGRAPH_ID] = ((NIVEAU_MASQUE & DigitalValue[BARGRAPH_ID]) | NIVEAU_2);
    else if (level == 3)
        DigitalValue[BARGRAPH_ID] = ((NIVEAU_MASQUE & DigitalValue[BARGRAPH_ID]) | NIVEAU_3);
    else if (level == 4)
        DigitalValue[BARGRAPH_ID] = ((NIVEAU_MASQUE & DigitalValue[BARGRAPH_ID]) | NIVEAU_4);
    else if (level == 5)
        DigitalValue[BARGRAPH_ID] = ((NIVEAU_MASQUE & DigitalValue[BARGRAPH_ID]) | NIVEAU_5);

    gestionLED.setAll(DigitalValue);
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool Memory::getSendBTNState()
{
    return stateSWFlag;
}

/**
 * @brief
 *
 * @param state
 */
void Memory::setSendBTNState(bool state)
{
    stateSWFlag = state;
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
        stateSWFlag = true;
    }
    else
        stateSWFlag = false;
}
