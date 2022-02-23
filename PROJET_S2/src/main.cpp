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

#define MODULE_WIRES 1
#define MODULE_PADLOCK 2
#define MODULE_MEMORY 3
#define MODULE_KEYPAD 4
#define MODULE_ACCELEROMETRE 5

/**     Etat Transition          **/
// variable
bool commandeValid;
int id;
// constante
enum etatTransition
{
  START,
  COMMANDE,
  LED,
  BOMBE,
  END,

} EtatTransition;

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
  id = 0;


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
    /* code */
    break;
  case PADLOCK:
    /* code */
    break;
  case MEMORY:
    /* code */
    break;
  case KEYPAD:
    /* code */
    break;
  }

  if(accelerometre.getStateFlag()){
    accelerometre.setStateFlag(false);

    int tabValue[3];//valeur pouvant aller de 0 a 1023
    tabValue[0] = accelerometre.getX_value();
    tabValue[1] = accelerometre.getY_value();
    tabValue[2] = accelerometre.getZ_value();

    sendData(MODULE_ACCELEROMETRE,tabValue,3); 
  }
}

/**
 * Possibiliter de reception
 *  -<1> //wire
 *  -<2> //Padlock
 *  -<3> //Memory
 *  -<4> //Keypad
 *  -<6,/a determiner/> //LED
 *  -<7,ON/OFF> //moteur vibrant
 *
 * Possibiliter de d'envoie
 *  -<1,cut_wire> //wire
 *  -<2,padluck_Xvalue,padloc_Yvalue> //Padlock
 *  -<3,memory_analog_value> //Memory
 *  -<4,keypad_digital_value> //Keypad
 *  -<5,accelerometre_analog_Xvalue,accelerometre_analog_Yvalue,accelerometre_analog_Zvalue> //accelerometre
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
      Serial.print("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }
    break;

  case COMMANDE:
    if (('1' <= rxData) && (rxData <= '7'))
    {
      id = rxData - '0';
      Serial.print(rxData);

      if ((1 <= id) && (id <= 5))
      {
        EtatTransition = END;
      }
    }
    else if (rxData == ',')
    {
      if (id == 6)
      {
        EtatTransition = LED;
      }
      else if (id == 7)
      {
        EtatTransition = BOMBE;
      }
    }
    else
    {
      EtatTransition = END;
      Serial.print("COMMANDE NOT AVAILABLE\n\r");
      commandeValid = false;
    }
    break;

  case LED:
    // tester la valeur de rx
    break;

  case BOMBE:
    /* code */
    break;

  case END:
    if (rxData == '>')
    {
      commandeValid = true;
    }
    else
    {
      Serial.print("ERROR OF COMMUNICATION\n\r");
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

  txData[index++] = '>';
  txData[index] = '\0';

  Serial.println(txData);

  return 0;
}