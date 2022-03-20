/**
 * @file keypad.h
 * @author Alexandre Falardeau (alexandre.falardeau@usherbrooke.ca)
 * @author Justin Houde (justin.houde@usherbrooke.ca)
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */





/**
 * 
 *  Revoir class, l'arduino doit seulement detecter un changement d'état et l'envoyer au PC, donc les méthodes ne corespond pas a ce qui est demandé 
 * 
 **/






#include "KeyPad.hpp"


// Pourquoi tu les declares dans le .cpp et le .hpp?????? 

uint8_t switchPin1;
uint8_t switchPin2;
uint8_t switchPin3;
uint8_t switchPin4;
//Fonction qui permet de générer une matrice de fils, aucune validation. Basé sur la fonction RandomNumberGenerator(). 
//Prend en paramètres un minimum, maximum, le nombre de chiffre à générer et la matrice de fils initilisée dans le main().
//Aucun retour, la matrice de fils est modifié directement à l'adresse némoire. 

Keypad :: Keypad(uint8_t switchPin1, uint8_t switchPin2, uint8_t switchPin3, uint8_t switchPin4)
{
  int arr[BOUTMAX][STATES]; // le tableau es local au constructeur, donc ne peux pas etre utiliser
  keypadInit(arr);
  genmodule(0, 4, BOUTMAX, arr);
  /*switchPin1 = this->switchPin1; v   c'est l'inverse, le this affect la variable privé de la class et non la variable en parametre
  switchPin2 = this->switchPin2;
  switchPin3 = this->switchPin3;
  switchPin4 = this->switchPin4;*/
  this->switchPin1 = switchPin1;
  this->switchPin2 = switchPin2;
  this->switchPin3 = switchPin3;
  this->switchPin4 = switchPin4;
}

Keypad::~Keypad()
{
}


/**
*
* A quoi sert cette méthode la ???? l'arduino ne genere pas de module
*
 **/
void Keypad :: genmodule(const int nMin, const int nMax, const int  nToGenerate, int arr[BOUTMAX][STATES])
{
  int ran_num = 0;
  for (int i = 0; i < nToGenerate;)
  {
    ran_num = rand()%(nMax-nMin) + nMin;
    if (ran_num!=arr[1][0] && ran_num!=arr[0][0] && ran_num!=arr[2][0] && ran_num!=arr[3][0])
    {
		arr[i][0]=ran_num;
		i++;
	}
  }
}


/**
*
* A quoi sert cette méthode la ???? 
*
 **/
void Keypad :: keypadInit(int arr[BOUTMAX][STATES])
{
	for (int i=0; i<BOUTMAX;i++)
	{
		arr[i][1]=ON;
		arr[i][0]=5;
	}
}

int Keypad :: Reussi(int arr[BOUTMAX][STATES])
{
	int total=0;
	for (int i=0;i<BOUTMAX;i++)
	{
		if (arr[i][1]==1)
		{
			total++;
		}
	}
	return total;
}

/**
*
* A quoi sert cette méthode la ???? l'arduino ne genere pas de module
*
 **/
void Keypad :: detecterTouche(int arr[BOUTMAX][STATES])
{
    if (digitalRead(switchPin1) == HIGH)
    {
        if (arr[1][1] == tour && arr[1][1] == 0)
	{
		arr[1][1]=1;
        tour++;
	}
        else
            status = GAMEOVER;
    }
    
    if (digitalRead(switchPin2) == HIGH)
    {
        if (arr[2][1] == tour  && arr[2][1] == 0)
	{
		arr[2][1]=1;
        tour++;
	}
        else
            status = GAMEOVER;
    }

    if (digitalRead(switchPin3) == HIGH)
    {
        if (arr[3][1] == 0 && arr[3][1] == 0)
	{
		arr[3][1]=1;
        tour++;
	}
        else
            status = GAMEOVER;
    }

    if (digitalRead(switchPin4) == HIGH)
    {
        if (arr[4][1] == 0 && arr[4][1] == 0)
	{
		arr[4][1]=1;
        tour++;
	}
        else
            status = GAMEOVER;
    }
    
	if (Reussi(arr) == 4)
	    status = RIGHT;
}


