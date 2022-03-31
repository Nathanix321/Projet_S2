#include "wire.hpp"

Wire::Wire(uint8_t analogPin1)
{
    pinMode(analogPin1, INPUT);
    this->analogPin1 = analogPin1;
}

Wire::~Wire()
{
}
 
int Wire::getCutWires()
{
    return formatvoltage(analogRead(analogPin1));
}


//Fonction qui permet de transformer la valeur de voltage en un multiple entier de la constante INCREMENTVOLTAGE. La fonction filtre aussi pour une incertitude raisonnable.
//Prend en paramètre la valeur de voltage. 
//Retourne le multiple de INCREMENTVOLTAGE calculé.
int Wire::formatvoltage(float voltage)
{
  int format=0;
  while (voltage>INCREMENTVOLTAGE)
  {
    voltage-=INCREMENTVOLTAGE;
    format++;
  }	
  if (voltage>INCREMENTVOLTAGE/2)
  {
	format++;  
  }
  return format;
}