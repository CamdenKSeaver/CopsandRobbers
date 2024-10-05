// Programmer: Camden Seaver
// Date: 12/3/2023
// File: classes.h
// Assignment: Final Project
// Purpose: this file contains all classes
#ifndef CLASSES_H
#define CLASSES_H
#include <cstdlib>
#include <ctime>



class City {
private:
	char cityGrid[7][7];
	int jewelCount;

public:
	//default constructor
	City();
	//places jewels on grid
	//none
	//returns nothing but fills city grid with jewels
	void placeJewels();
	//prints grid 
	//none
	//prints grid in format
	void printGrid();
	//getter for val at coordinate
	//none
	//returns char at given x y coord
	char getGridValue(int x, int y) const;
	//setter for grid
	//none
	//sets point given to value given
	void setGridValue(int x, int y, char value);

};

class Jewel {
private:
	int value;
	int x, y;
public:
	//default constructor
	Jewel();
	//constructor
	Jewel(int jewelValue, int jewelX, int jewelY);
	//getter for jewel val
	//none
	//returns value of jewel
	int getValue() const;
	//getter for x
	//none
	//returns x
	int getX() const;
	//getter for y
	//none
	//returns y
	int getY() const;
};

//couldnt figure out why my functions in robber wouldnt work with police in the paramters
// did research and said i need to declare it before also, not sure if we learned this but only way it worked
class Police;
class Robber {
private:
	int id;
	int x, y;
	//holds the jewels collected so we know all jewels old coordinates and their value
	Jewel bag[10];
	//know how many jewels we have collected so we dont go over 10 and for sizing of loops
	int numCollected;
	int noJewel;
	int immobilized;
	int turns;
	int individualLoot;
	bool isActive;
	bool isGreedy;

public:
	//static var holds total loot for all robbers
	static int totalLoot;
	//constructor
	Robber(int robberId, int startX, int startY, bool greedy);
	//simulates picking up loot
	//none
	//adds jewel to robber
	void pickUpLoot();
	//moves the robber in a valid location and performs action
	//none
	//returns nothing, moves robber to valid location and performs action
	void move(City & city,Police & police1, Police & police2,Robber & robber1, Robber &robber2,Robber & robber3);
	//prints robber info
	//none
	//returns nothing, prints formatted robber
	void printRobber();
	//getter for active
	//none
	//returns its status(active or not)
	bool getStatus() const;
	//setter for isActive
	//none
	//sets isActive to newStatus
	void setStatus(bool newStatus);
	//getter for individiualLoot
	//none
	//returns individualLoot
	int getIndividualLoot() const;
	//setter for individualLoot
	//none
	//sets individualLoot to new val
	void setIndividualLoot(int newIndividualLoot);
	//getter for x
	//none
	//returns x
	int getX() const;
	//getter for y
	//none
	//returns y
    	int getY() const;
};
class Police {
private:
	int id;
	int x, y;
	char holdChar;
	int totalLoot;
	int robbersCaught;

public:
	//constructor
	Police(int policeId, int startX, int startY);
	//simulates arresting a robber
	//none
	//takes loot from robber and sets status to inactive
	void arrest(Robber & robber);
	//simulates moving the police
	//none
	//performs actions based on where it moved to (must be valid location)
	void move(City &city, Police & police, Robber & robber1,Robber & robber2,Robber & robber3,Robber &robber4);
	//prints police object
	//none
	//formatted printout of police info
	void printPolice();
	//getter for x
	//none
	//returns x
	int getX() const;
	//getter for y 
	//none
	//returns y
	int getY() const;
	//getter for totalLoot
        //none
        //returns totalLoot
	int getTotalLoot() const;
	//setter for totalLoot
	//none
	//set totalLoot to newLoot
	void setTotalLoot(int newLoot);
	//getter for robbersCaught
        //none
        //returns robberCaught
	int getRobbersCaught() const;
};



#endif
