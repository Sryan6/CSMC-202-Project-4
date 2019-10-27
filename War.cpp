/************************************************
 ** File: War.cpp
 ** Project: CMSC 202 Project 4, Warhorse
 ** Author: Steven Ryan
 ** Date: 4/18/19
 ** Section: 12
 ** E-Mail: sryan6@umbc.edu
 **
 ** This file is used to write the source code
 ** for the War methods
 ***********************************************/

//Preprocessor Directives
#include "War.h"

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
War::War(){
    srand(time(NULL));
}

//Destructor
War::~War(){
  //Deallocates player stable
  for(int i = 0; i < (int) m_myStable.size(); i++){
    delete m_myStable.at(i);
  }
  //Deallocates enemy stable
  for(int u = 0; u < (int) m_enemyStable.size(); u++){
    delete m_enemyStable.at(u);
  }
}

//loads in enemy horses
void War::loadHorses(char* file){
  ifstream inputStream;

  inputStream.open(file);
  
  //if file successfully opens
  if(inputStream.is_open()){
    string name;
    int sizeInt;
    Size size;
    int health;
    int speed;

    Horse* horse;
    Horse* newHorse;

    //while file is open
    while(inputStream){
      //reads in all the data
      inputStream >> name;
      inputStream >> sizeInt;
      size = Size(sizeInt);
      inputStream >> health;
      inputStream >> speed;

      //ignores newline
      inputStream.ignore(1);

      horse = new Untrained(name, size, health, speed);
      //uses a temp horse to deallocate memory in untrained when training the horse
      newHorse = horse->specialize();
      delete horse;
      //adds horse to vector
      m_enemyStable.push_back(newHorse);
      
    }
  }
}

//Interfaces with user to get input
void War::mainMenu(){
    int choice;
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Display Friendly Stable" << endl;
        cout << "2. Display Enemy Stable" << endl;
        cout << "3. Acquire Horse" << endl;
        cout << "4. Train Horse" << endl;
        cout << "5. Battle" << endl;
        cout << "6. Quit" << endl;
        cin >> choice;
	
	//validates input
	if(choice < 1 || choice > 6){
	  cout << "Please choose a valid answer" << endl;
	}
	else{

	  //displays player horses
	  if(choice == 1){
	    displayMyHorses();
	  }

	  //displays enemy horses
	  if(choice == 2){
	    displayEnemyHorses();
	  }

	  //gives player a new horse
	  if(choice == 3){
	    acquireHorse();
	  }

	  //trains the horse of the player's choosing
	  if(choice == 4){
	    trainHorse();
	  }

	  //Starts a battle between the player's horse and the enemy's
	  if(choice == 5){
	    startBattle();
	  }
	}
    }while(choice != 6 && (int)m_enemyStable.size() != 0);
    //If the game ends due to the player quitting, "Quit" is displayed
    if(choice == 6){
      cout << "Quit" << endl;
    }
    //if all the warhorses in the enemy's stable are killed, displays your win.
    else{
      cout << "You have won the war!" << endl;
    }
}

//Gives the player a new horse in their stable
void War::acquireHorse(){
  //fills variables relating to the new horse
  cout << "What would you like to name the horse?" << endl;
  string name;
  Horse *newHorse;
  cin >> name;
  cout << "You have acquired a new horse" << endl << endl;
  //randomizes size
  int sizeInt = rand() % (MAX_SIZE + 1);
  Size size = Size(sizeInt);
  int speed;
  int health;
  //determines tier of horse's stats related to size
  switch(sizeInt){
  case 0:
    //Light horse
    health = LT_MIN_HEALTH + rand() % (LT_MAX_HEALTH - LT_MIN_HEALTH + 1);
    speed = LT_MIN_SPEED + rand() % (LT_MAX_SPEED - LT_MIN_SPEED + 1);
    break;
  case 1:
    //Medium horse
    health = MD_MIN_HEALTH + rand() % (MD_MAX_HEALTH - MD_MIN_HEALTH + 1);
    speed = MD_MIN_SPEED + rand() % (MD_MAX_SPEED - MD_MIN_SPEED + 1);
    break;
  case 2:
    //Heavy horse
    health = HV_MIN_HEALTH + rand() % (HV_MAX_HEALTH - HV_MIN_HEALTH + 1);
    speed = HV_MIN_SPEED + rand() % (HV_MAX_SPEED - HV_MIN_SPEED + 1);
    break;
  }
  //dynamically creates new horse with the aforementioned traits
  newHorse = new Untrained(name, size, health, speed);
  //adds to vector
  m_myStable.push_back(newHorse);
}

//trains the horse selected
void War::trainHorse(){
  //in case the stable is empty
  if((int)m_myStable.size() == 0){
    cout << "You will need to add a horse before you can train it" << endl << endl; 
  }
  else{
    //gets choice of horse by user
    int choice = chooseHorse();
    //if the horse is trained to Master
    if(m_myStable.at(choice)->getTraining() == MAX_TRAINING){
      cout << "Unable to train this horse further" << endl << endl;
    }
    else{
      //if horse is not specialized
      if(m_myStable.at(choice)->getTraining() == 0){
	//specialize the horse and increase to saddle
	Horse* horse = m_myStable.at(choice)->specialize();
	delete m_myStable.at(choice);
	m_myStable.at(choice) = horse;
        m_myStable.at(choice)->increaseTraining();
      }

      //if horse is specialized, decide whether it can be trained further (50% chance)
      bool trained = m_myStable.at(choice)->train();

      //if training was successful
      if(trained == true){
	cout << m_myStable.at(choice)->getName() << " has been trained" << endl << endl;
      }
      //if training was not successful
      else{
	cout << "This horse is being unruly. Try training again later" << endl << endl;
      }
    }
  }
}

//Begins a battle with the 1st enemy horse
void War::startBattle(){
  //if stable is empty
  if((int)m_myStable.size() == 0){
    cout << "You will need to acquire horses before battling" << endl << endl;
  }
  else{
    //gets horse choice
    int choice = chooseHorse();
    
    //if horse chosen is Untrained
    if(m_myStable.at(choice)->getTraining() == 0){
      cout << "You must choose a horse with some sort of training" << endl << endl;
    }
    else{
      //calls battle and puts result in a boolean
      bool winOrLose = m_myStable.at(choice)->battle(m_enemyStable.at(0));

      //if the player wins battle
      if(winOrLose == true){
	//deallocates enemy horse and takes out of vector
	delete m_enemyStable.at(0);
	m_enemyStable.erase(m_enemyStable.begin() + 0);
	cout << "Congrats! You won" << endl;
      }
      //if the enemy wins battle
      else if(winOrLose == false){
	//deallocates player horse and takes out of vector
	delete m_myStable.at(choice);
	m_myStable.erase(m_myStable.begin() + choice);
	cout << "Your horse perished in the fighting" << endl << endl;
      }
    }
  }
}

//Displays the vector of player's horses
void War::displayMyHorses(){
  cout << "My Horses" << endl;
  //if the stable is empty
  if((int) m_myStable.size() == 0){
    cout << "Your stable is currently empty" << endl << endl;
  }
  else{
    cout << "Num             Horse   Size            Health  Speed   Training" << endl;
    for(int i = 0; i < (int) m_myStable.size(); i++){
      //formats horse display chart
      if(i == 0){
	cout << i + 1 << "  ";
      }
      else{
	cout << setw(3) << i + 1;
      }
      //calls overloaded operator
      cout << *m_myStable.at(i) << endl;
    }
    cout << endl;
  }
}

//Displays the vector of enemy horses
void War::displayEnemyHorses(){
  cout << "Enemy Horses" << endl;
  cout << "Num             Horse   Size            Health  Speed   Training" << endl;
  for(int i = 0; i < (int) m_enemyStable.size() - 1; i++){
    //formats horse display chart
    if(i == 0){
      cout << i + 1 << "  ";
    }
    else{
      cout << setw(3) << i + 1;
    }
    //calls overloaded operator
    cout << *m_enemyStable.at(i) << endl;
  }
  cout << endl;
}

//Helper function to validate horse choice
int War::chooseHorse(){
  //if stable is empty
  if((int) m_myStable.size() == 0){
    cout << "Your stable is currently empty" << endl;
    return 0;
  }
  //if stable has at least 1 horse
  else{
    int choice;
    cout << "Which horse would you like to work with?" << endl;
    displayMyHorses();
    cin >> choice;
    //validates choice
    while(choice < 1 || choice > (int) m_myStable.size()){
      cout << "Please choose a valid horse" << endl;
      cin >> choice;
    }
    //returns index by decrementing choice by 1
    return choice - 1;
  }
}
