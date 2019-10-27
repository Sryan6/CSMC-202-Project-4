//Title: driver.cpp
//Author: Jeremy Dixon
//Date: 4/2/2019
//Description: This is the driver for project 4 practicing polymorphism

#include "War.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argv, char* argc[]){
  //load file from command line argument
  if(argv < 1 or argv > 2){
    cout << "Invalid number of parameters..." << endl;
    return -1;
  }
  
  cout << "Loading file: " << argc[1] << endl << endl;

  cout << "Welcome to UMBC War" << endl << endl;
  
  //Make new horse load file and run program
  War s;
  s.loadHorses(argc[1]);
  s.mainMenu();
  
  return 0;
}
