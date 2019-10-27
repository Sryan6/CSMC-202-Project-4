/************************************************
 ** File: Light.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Light Horse methods
 ***********************************************/

//Preprocessor Directives
#include "Light.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

//Default constructor
Light::Light(){
  srand(time(NULL));
}

//Overloaded constructor
Light::Light(string name, Size size, int health,
	     int speed):Warhorse(name, size, health, speed){
  
}

//Attack for a light horse
int Light::attack(string target, int health){
  cout << "The light warhorse " << getName() << " hits " << target << endl;
  int damage = health / 6 + getTraining();
  return damage;
}

//Returns name of class as string
string Light::toString(){
    return "Light";
}
