/// Programmer: Camden Seaver
// Date: 12/3/2023
// File: main.cpp
// Assignment: Final Project
// Purpose: this file runs the heist simulation


#include "classes.h"
#include <iostream>
using namespace std;
int main() {
	srand(100);
	City city;
	city.placeJewels();
	int xRand;
	int yRand;
	//Creates all police and robbers placing them on the grid in an empty location
	do{
		xRand = rand() % 7;
		yRand = rand() % 7;
	}while(city.getGridValue(xRand,yRand) != ' ');
	Robber r1(1,xRand,yRand,false);
	city.setGridValue(xRand,yRand,'r');

	do{
                xRand = rand() % 7;
                yRand = rand() % 7;
        }while(city.getGridValue(xRand,yRand) != ' ');
        Robber r2(2,xRand,yRand,false);
	city.setGridValue(xRand,yRand,'r');


	do{
                xRand = rand() % 7;
                yRand = rand() % 7;
        }while(city.getGridValue(xRand,yRand) != ' ');
        Robber r3(3,xRand,yRand,true);
	city.setGridValue(xRand,yRand,'r');

	do{
                xRand = rand() % 7;
                yRand = rand() % 7;
        }while(city.getGridValue(xRand,yRand) != ' ');
        Robber r4(4,xRand,yRand,true);
	city.setGridValue(xRand,yRand,'r');

	do{
                xRand = rand() % 7;
                yRand = rand() % 7;
        }while(city.getGridValue(xRand,yRand) != ' ');
        Police p1(1,xRand,yRand);
	city.setGridValue(xRand,yRand,'p');

	do{
                xRand = rand() % 7;
                yRand = rand() % 7;
        }while(city.getGridValue(xRand,yRand) != ' ');
        Police p2(2,xRand,yRand);
	city.setGridValue(xRand,yRand,'p');

	//keep track of turns taken
	int numTurns = 0;
	city.printGrid();
	//while loop to run all turns till complete or stopped early
	//Istructions werent entirely clear on what to do when certain things overlap
	//For example, if a police and inactive robber are on a space, the 'A' shows for inactive robber
	//instructions didnt say what to do so i thought that would be best
	//also if multiple robbers are on a space and AT LEAST 1 is active, i put 'R' instead of 'A'
	while(Robber::totalLoot < 2023 && numTurns < 50 && (p1.getRobbersCaught() + p2.getRobbersCaught()) != 4){
		r1.move(city,p1,p2,r2,r3,r4);
		r2.move(city,p1,p2,r1,r3,r4);
		r3.move(city,p1,p2,r1,r2,r4);
		r4.move(city,p1,p2,r1,r2,r3);
		p1.move(city,p2,r1,r2,r3,r4);
		p2.move(city,p1,r1,r2,r3,r4);
		cout<<"\nTurn: "<<numTurns + 1<<endl;
		city.printGrid();
		numTurns++;

	}
	if(Robber::totalLoot > 2023)
		cout<<"The robbers win the chase because they reached $2023!"<<endl;
	if(numTurns >= 50)
		cout<<"The robbers win the chase because the maximum amount of turns (50) has been reached!"<<endl;
	else
		cout<<"The police win the chase because they caught all the robbers!"<<endl;
	p1.printPolice();
	p2.printPolice();
	r1.printRobber();
	r2.printRobber();
	r3.printRobber();
	r4.printRobber();


}
