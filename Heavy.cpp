/************************************************
 ** File: Heavy.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Heavy Horse methods
 ***********************************************/

//Preprocessor Directives
#include "Heavy.h"

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
Heavy::Heavy(){
  srand(time(NULL));
}

//Overloaded constructor
Heavy::Heavy(string name, Size size, int health,
	     int speed):Warhorse(name, size, health, speed){
  
}

//Attack of heavy warhorse (with kick)
int Heavy::attack(string target, int health){
  cout << "The Heavy warhorse " << getName() << " hits " << target << endl;
  cout << "The Heavy warhorse spins and kicks the enemy! " << endl;
  int damage = (health / 6 + getTraining()) + kick();
  return damage;
}

//returns name of class as a string
string Heavy::toString(){
    return "Heavy";
}

//Adds additional damage to a heavy warhorse's attack
int Heavy::kick(){
  int damage = 1 + rand() % ((3 - 1)+ 1);
  return damage;
}
