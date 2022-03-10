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

//H22-S2-PROJET-P09
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>
//Constantes de dimensions pour la matrice de fils (4 fils, 3 états : couleur, coupé ou intact, bon ou mauvais).
#define BOUTMAX 4
#define STATES 3

//Constantes d'états pour la matrice de fils(ON/OFF : coupé et intact, RIGHT/WRONG : bon et mauvais).
#define ON 0
#define OFF -1
#define RIGHT 1
#define WRONG -1
#define GAMEOVER 2

class Keypad
{
public:
    Keypad(uint8_t switchPin1, uint8_t switchPin2, uint8_t switchPin3, uint8_t switchPin4);
    Keypad();
    ~Keypad();

    void genmodule(const int nMin, const int nMax, const int  nToGenerate, int arr[BOUTMAX][STATES]);
    void keypadInit(int arr[BOUTMAX][STATES]);
    int Reussi(int arr[BOUTMAX][STATES]);
    void detecterTouche(int arr[BOUTMAX][STATES]);

private:
    int tour = 0;
    int status = WRONG;
    uint8_t switchPin1;
    uint8_t switchPin2;
    uint8_t switchPin3;
    uint8_t switchPin4;

};
