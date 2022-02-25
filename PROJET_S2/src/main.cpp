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
#include <accelerometre.hpp>
#include <ShiftRegister74HC595.h>
#include <memory.hpp>


#define MODULE_WIRES 1
#define MODULE_PADLOCK 2
#define MODULE_MEMORY 3
#define MODULE_KEYPAD 4
#define MODULE_ACCELEROMETRE 5

/**     Etat Transition          **/
// variable
bool commandeValid;
int idModule;
bool BombeStateFlag;
bool BombeState;
bool LEDStateFlag;
uint8_t LEDState;

// constante
enum etatTransition
{
  START,
  COMMANDE,
  MEMORY_LED,
  LED,
  BOMBE,
  END,

} EtatTransition;

/**     memory         **/
uint8_t memoryLevel;
uint8_t memoryNumber;

/**     accelerometre         **/
#define ACCELEROMETRE_X_PIN A3
#define ACCELEROMETRE_Y_PIN A4
#define ACCELEROMETRE_Z_PIN A5
Accelerometre accelerometre(ACCELEROMETRE_X_PIN, ACCELEROMETRE_Y_PIN, ACCELEROMETRE_Z_PIN);

/**     loop         **/
enum etatModule
{
  INIT,
  WIRE,
  PADLOCK,
  MEMORY,
  KEYPAD

} EtatModule;

// fonction
bool etatTransitionModule(char rxData);
bool sendData(int module, int *tabData, int tabSize);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  sei();

  // etatTransition
  EtatTransition = START;
  commandeValid = false;
  idModule = 0;
  LEDStateFlag = false;
  LEDState = 0;

  // bombe
  BombeStateFlag = false;

  // memory
  memoryLevel = 0;
  memoryNumber = 10; // 10 = aucun chiffre afficher

  // loop
  EtatModule = INIT;
}

void loop()
{
  switch (EtatModule)
  {
  case INIT:
    /* code */
    break;
  case WIRE:
    if (commandeValid)
    {

    }
    break;
  case PADLOCK:
    if (commandeValid)
    {

    }
    break;
  case MEMORY:
    if (commandeValid)
    {

    }
    break;
  case KEYPAD:
    if (commandeValid)
    {

    }
    break;
  }

  if (accelerometre.getStateFlag())
  {
    accelerometre.setStateFlag(false);

    int tabValue[3]; // valeur pouvant aller de 0 a 1023
    tabValue[0] = accelerometre.getX_value();
    tabValue[1] = accelerometre.getY_value();
    tabValue[2] = accelerometre.getZ_value();

    sendData(MODULE_ACCELEROMETRE, tabValue, 3);
  }

  if (BombeStateFlag)
  {
    BombeStateFlag = false;

    delay(5000);

    EtatModule = INIT;
  }
}

/**
 * Possibiliter de reception
 *  -<0> //initialiser le board
 *  -<1> //wire
 *  -<2> //Padlock
 *  -<3,number,level,> //Memory
 *  -<4> //Keypad
 *  -<6,etat_LED_module,> //LED 0b1000 = module 4/0b0100 = module 3/0b0010 = module 2/0b0001 = module 1
 *  -<7,etat_moteur,> //moteur vibrant 0 = OFF/1 = ON
 *
 * Possibiliter de d'envoie
 *  -<1,cut_wire,> //wire
 *  -<2,padluck_Xvalue,padloc_Yvalue,> //Padlock
 *  -<3,memory_analog_value,> //Memory
 *  -<4,keypad_digital_value,> //Keypad
 *  -<5,accelerometre_analog_Xvalue,accelerometre_analog_Yvalue,accelerometre_analog_Zvalue,> //accelerometre
 */

/**
 * @brief lorsqu'une commande est recus, serialEvent est automatiquement appelee
 *
 */
void serialEvent()
{
  while (Serial.available())
  {
    etatTransitionModule((char)Serial.read());
  }
}

/**
 * @brief fonction qui traite la donnee recus
 *
 * @param rxData
 * @return true
 * @return false
 */
bool etatTransitionModule(char rxData)
{
  switch (EtatTransition)
  {
  case START:
    if (rxData == '<')
    {
      EtatTransition = COMMANDE;
    }
    else
    {
      EtatTransition = START;
      // Serial.print("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }
    break;

  case COMMANDE:
    if (('1' <= rxData) && (rxData <= '7'))
    {
      idModule = rxData - '0';
      Serial.print(rxData);

      if ((0 <= idModule) && (idModule <= 4) && (idModule != 3))
      {
        EtatTransition = END;
      }
    }
    else if (rxData == ',')
    {
      if (idModule == 3)
      {
        EtatTransition = MEMORY_LED;
      }
      else if (idModule == 6)
      {
        EtatTransition = LED;
      }
      else if (idModule == 7)
      {
        EtatTransition = BOMBE;
      }
    }
    else
    {
      EtatTransition = END;
      // Serial.print("COMMANDE NOT AVAILABLE\n\r");
      commandeValid = false;
    }
    break;

  case MEMORY_LED:
    int indexData = 0;

    if ((indexData++ == 0) && ((rxData >= '0') && (rxData <= '9')))
      memoryNumber = rxData - '0';
    else if ((indexData++ == 1) && ((rxData >= '1') && (rxData <= '4')))
      memoryLevel = rxData - '0';
    else if ((indexData++ == 2) && (rxData == ','))
    {
      EtatTransition = END;
    }
    else
      EtatTransition = END;

    break;

  case LED:

    char tabLEDData[2];
    uint8_t index = 0;

    if ((rxData >= '0') && (rxData <= '9'))
      tabLEDData[index++] = rxData;
    else if (rxData == ',')
    {
      LEDState = atoi(tabLEDData);
      LEDStateFlag = true;
      EtatTransition = END;
    }
    break;

  case BOMBE:
    if ((rxData == '0') || (rxData == '1'))
    {
      BombeState = rxData - '0';
      BombeStateFlag = true;
    }
    else if (rxData == ',')
      EtatTransition = END;
    else
    {
      BombeStateFlag = false;

      // Serial.println("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }

    break;

  case END:
    if (rxData == '>')
    {
      commandeValid = true;
    }
    else
    {
      // Serial.println("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }
    EtatTransition = START;
    break;
  }

  return 0;
}

/**
 * @brief fonction qui envoie une commande par le port serie
 *
 * @param module
 * @param tabData
 * @param tabSize
 * @return true
 * @return false
 */
bool sendData(int module, int *tabData, int tabSize)
{

  char txData[30];
  int index = 0;

  txData[index++] = '<';
  txData[index++] = module + '0';

  for (int i = 0; i < tabSize; i++)
  {
    txData[index++] = ',';
    char tempTab[10];
    int sizeTempTab = sprintf(tempTab, "%d", tabData[i]);

    for (int j = 0; j < sizeTempTab; j++)
    {
      txData[index++] = tempTab[j];
    }
  }

  txData[index++] = ',';
  txData[index++] = '>';
  txData[index] = '\0';

  Serial.println(txData);

  return 0;
}