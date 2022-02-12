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
#include "accelerometre.h"
#include "memory.h"

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

// fonction
bool etatTransitionModule(char rxData);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // etatTransition
  EtatTransition = START;
  commandeValid = false;
  id = 0;
}

void loop()
{
  // put your main code here, to run repeatedly:
}

/**
 * Possibiliter de reception
 *  -<1> //wire
 *  -<2> //Padluck
 *  -<3> //Memory
 *  -<4> //Keypad
 *  -<5> //accelerometre
 *  -<6,/a determiner/> //LED
 *  -<7,ON/OFF> //moteur vibrant
 *
 * Possibiliter de d'envoie
 *  -<1,wire_analog_value> //wire
 *  -<2,padluck_analog_Xvalue,padluck_analog_Yvalue> //Padluck
 *  -<3,memory_analog_value> //Memory
 *  -<4,keypad_digital_value> //Keypad
 *  -<5,accelerometre_analog_Xvalue,accelerometre_analog_Yvalue,accelerometre_analog_Zvalue> //accelerometre
 */

void serialEvent()
{
  while (Serial.available())
  {
    etatTransitionModule((char)Serial.read());
  }
}

bool etatTransitionModule(char rxData)
{
  switch (EtatTransition)
  {
  case START:
    if(rxData == '<'){
      EtatTransition = COMMANDE;
    }
    else{
      EtatTransition = START;
      Serial.print("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }
    break;

  case COMMANDE:
    if(('1' <= rxData) && (rxData <= '7')){
      id = rxData - '0';
      Serial.print(rxData);

      if((1 <= id) && (id <= 5)){
        EtatTransition = END;
      }
      else if(id == 6){
        EtatTransition = LED;
      }
            else if(id == 7){
        EtatTransition = BOMBE;
      }
    }
    else{
      EtatTransition = END;
      Serial.print("COMMANDE NOT AVAILABLE\n\r");
      commandeValid = false;
    }
    break;

  case LED:
    /* code */
    break;

  case BOMBE:
    /* code */
    break;

  case END:
    if(rxData == '>'){
      commandeValid = true;
    }
    else{
      Serial.print("ERROR OF COMMUNICATION\n\r");
      commandeValid = false;
    }
    EtatTransition = START;
    break;
  }
  return 0;
}