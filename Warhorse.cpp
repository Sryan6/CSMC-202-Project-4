/************************************************
 ** File: Warhorse.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Warhorse horse methods
 ***********************************************/

//Preprocessor Directives
#include "Warhorse.h"

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
Warhorse::Warhorse(){
  srand(time(NULL));
}

//Overloaded constructor
Warhorse::Warhorse(string name, Size size, int health,
		   int speed):Horse(name, size, health, speed){
    
}

//Gives 50/50 chance of training increasing or not
bool Warhorse::train(){
  if(randomPercentBased(50)){
    return increaseTraining();
  }
  else{
    return false;
  }
}

//Returns the class name as a string
string Warhorse::toString(){
  return "Warhorse";
}

//Dictates how a battle plays out
bool Warhorse::battle(Horse* enemy){
  int counter = 0;
  int playerHealth = getHealth();
  int enemyHealth = enemy->getHealth();
  //while neither hrose is dead
  while(enemy->getHealth() > 0 && getHealth() > 0){
    if(counter % getSpeed() == 0){
      //player attacks enemy
      enemy->setHealth(enemy->getHealth() -
		       (attack(enemy->getName(), enemy->getHealth())));
    }
    
    if(counter % enemy->getSpeed() == 0 && enemy->getHealth() > 0){
      //enemy attacks player
      setHealth(getHealth() - (enemy->attack(getName(), getHealth())));
    }

    counter++;
  }

  //if enemy's horse dies
  if(enemy->getHealth() < 0){
    setHealth(playerHealth);
    return true;
  }
  //if players' horse dies
  else if(getHealth() < 0){
    enemy->setHealth(enemyHealth);
    return false;
  }
  //returns something if error occurs
  else{
    return false;
  }
}
