/************************************************
 ** File: Untrained.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Untrained Horse methods
 ***********************************************/

//Preprocessor Directives
#include "Untrained.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

//Default Constructor
Untrained::Untrained(){
  srand(time(NULL));
}

//Overloaded Constructor
Untrained::Untrained(string name, Size size, int health,
		     int speed):Horse(name, size, health, speed){
  
}

//Returns a warhorse of a weight subclass based on size
Horse* Untrained::specialize(){
  //if size is small
  if(getSize() == 0){
    Horse* horse = new Light(getName(), getSize(), getHealth(), getSpeed());
    return horse;
  }
  //if size is medium
  else if(getSize() == 1){
    Horse* horse = new Medium(getName(), getSize(), getHealth(), getSpeed());
    return horse;
  }
  //if size is large
  else if(getSize() == 2){
    Horse* horse = new Heavy(getName(), getSize(), getHealth(), getSpeed());
    return horse;
  }
  //returns something if error occurs
  else{
    return NULL;
  }
}

//virtual train function that should not be called
bool Untrained::train(){
  cout << "Untrained horses cannot be trained without being specialized." << endl; 
  return false;
}

//returns class name
string Untrained::toString(){
    return "Untrained";
}

//virtual attack function that should not be called
int Untrained::attack(string target, int health){
  cout << "Untrained horses cannot attack" << endl;
  return 0;
}
