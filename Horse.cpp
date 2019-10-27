/************************************************
 ** File: Horse.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the Horse methods
 ***********************************************/

//Preprocessor Directives
#include "Horse.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

Horse::Horse(){
  srand(time(NULL));
}

Horse::Horse(string name, Size size, int health, int speed){
    m_name = name;
    m_size = size;
    m_health = health;
    m_speed = speed;
    m_training = Training(0);
}

string Horse::getName(){
    return m_name;
}

Size Horse::getSize(){
    return m_size;
}

int Horse::getHealth(){
    return m_health;
}

int Horse::getSpeed(){
    return m_speed;
}

Training Horse::getTraining(){
    return m_training;
}

void Horse::setHealth(int health){
    m_health = health;
}

bool Horse::increaseTraining(){
    if(m_training < MAX_TRAINING){
      m_training = Training(m_training + 1);
      return true;
    }
    else{
      cout << "This horse is already trained to max!" << endl;
      return false;
    }
}

Horse* Horse::specialize(){
  cout << "This horse cannot be specialized." << endl;
  return NULL;
}

bool Horse::battle(Horse* horse){
  cout << "This horse cannot battle." << endl;
  return false;
}

//operator stuff
ostream& operator<<(ostream& output, Horse& horse){
  string size;
  switch(horse.m_size){
  case SMALL:
    size = "Light";
    break;
  case MEDIUM:
    size = "Medium";
    break;
  case LARGE:
    size = "Heavy";
    break;
  }
  cout << setw(18) << right << horse.m_name << "   ";
  cout << setw(16) << left << size;
  cout << setw(8) << left << horse.m_health;
  cout << setw(8) << left << horse.m_speed;
  cout << horse.trainingString(horse.m_training);
  return output;
}

bool Horse::randomPercentBased(int percent){
  int num = 1 + rand() % ((100 + 1) - 1);
    if(num < percent){
        return true;
    }
    else{
        return false;
    }
    
}

string Horse::trainingString(Training training){
    if(m_training == 0){
        return "Untrained";
    }
    else if(m_training == 1){
        return "Saddle";
    }
    else if(m_training == 2){
        return "Green";
    }
    else if(m_training == 3){
        return "Intermediate";
    }
    else if(m_training == 4){
        return "Expert";
    }
    else if(m_training == 5){
        return "Master";
    }
    else{
      return "Null";
    }
}
