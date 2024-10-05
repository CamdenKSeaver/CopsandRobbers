// Programmer: Camden Seaver
// Date: 12/3/2023
// File: classes.cpp
// Assignment: Final Project
// Purpose: this file completes the functionailty of the classes


#include "classes.h"
#include <iostream>
using namespace std;
//creates city with blank grid
City::City() {

    	jewelCount = 0;
    	for(int i = 0; i < 7; i++){
        	for(int j = 0; j < 7; j++){

            		cityGrid[i][j] = ' ';
        	}
    	}
}
void City::placeJewels(){
	int jewelsPlaced = 0;
	//makes sure jewels are all placed in new open space
	while(jewelsPlaced < 30){
        	int x = rand() % 7;
        	int y = rand() % 7;

        	if(cityGrid[x][y] == ' '){
            	cityGrid[x][y] = 'J';

		jewelsPlaced++;
        }
    }
}

void City::printGrid(){
	for (int i = 0; i < 7; ++i) {
        	for (int j = 0; j < 7; ++j) {
            		cout<<cityGrid[i][j]<<" ";
        }
        	cout<<"\n";
	}

}


Jewel::Jewel(){
    	value = 0;
    	x = y = 0;
}

Jewel::Jewel(int jewelValue, int jewelX, int jewelY){
    	value = jewelValue;
    	x = jewelX;
    	y = jewelY;
}
int Robber::totalLoot =0;
Robber::Robber(int robberId, int startX, int startY, bool greedy){
    	id = robberId;
    	x=startX;
    	y = startY;
    	numCollected = 0;
    	individualLoot =0;
	turns =0;
	noJewel =0;
	immobilized =0;
    	isActive =true;
    	isGreedy = greedy;
	//fill bag with empty jewels
	for(int i = 0; i < 10; i++){
        	bag[i] = Jewel();
    	}
}

void Robber::pickUpLoot(){
	if(numCollected < 10){
		//i add two because I want x and y to start at 1 and not zero since coordiantes on a grid start at 1,1 instead of 0,0 since then the jewel would have zero value
		Jewel jewel(((x+y+2)*(x+y+2)),x,y);
		bag[numCollected] =jewel;
		individualLoot += ((x+y+2)*(x+y+2));
		numCollected++;
		totalLoot += ((x+y+2)*(x+y+2));
	}

}
void Robber::printRobber(){
	if(isGreedy==true)
		cout<<"\tGreedy Robber id: "<<id<<endl;
	else
		cout<<"\tOriginal Robber id: "<<id<<endl;

	cout<<"\t\tFinal number of jewels picked up: "<<numCollected<<endl;
	cout<<"\t\tTotal jewel worth: "<<individualLoot<<endl;

}
void Robber::move(City & city,Police &police1, Police &police2,Robber & robber1,Robber & robber2, Robber & robber3){
 //only moves if active and not immobilized
  if(isActive == true && immobilized == 0){
		//holds how many active and inactive robbers there are on the space not including the robber that is moving
		//then determine what the space will be after the robber moves off the space(calculates what will be left over after the robber moves)
		int active = 0;
		int inactive = 0;

		//calculates how many active and inactive robbers are on the space to determine what the point value will be after it moves off of it
		if(robber1.getX() == x && robber1.getY() == y){
			if(robber1.getStatus() == true)
				active++;
			else
				inactive++;
		}

		if(robber2.getX() == x && robber2.getY() == y){
                        if(robber2.getStatus() == true)
                                active++;
                        else
                                inactive++;
                }
		if(robber3.getX() == x && robber3.getY() == y){
                        if(robber3.getStatus() == true)
                                active++;
                        else
                                inactive++;
                }
		if(active == 0){
			if(inactive > 0)
				city.setGridValue(x,y,'A');
			else
				city.setGridValue(x,y,' ');
		}
		else if(active == 1){
			city.setGridValue(x,y,'r');
		}
		else{
			city.setGridValue(x,y,'R');
		}

		bool finished = false;
		int nextX;
		int nextY;
		int val;
		//while loop to continue generating random movement until one is in bounds
		while(finished == false){
			val = rand() % 8;
                                nextX = x;
                                nextY = y;

			switch (val) {
				case 0:
	            			nextX--;
	        			nextY--;
        				break;
    				case 1:
            				nextX--;
        				break;
    				case 2:
        			    	nextX--;
        			    	nextY++;
        				break;
    				case 3:
        			    	nextY--;
        				break;
    				case 4:
	        		    	nextY++;
	        			break;
	    			case 5:
	        		    	nextX++;
	        	    		nextY--;
	        			break;
	    			case 6:
	        		    	nextX++;
	        			break;
	    			case 7:
	            			nextX++;
	        			nextY++;
	        			break;
			}
			//make sure it is not out of bounds
			if(nextX < 0 ||nextX > 6 ||nextY< 0 ||nextY > 6){
				finished = false;
			}
			else
				finished = true;

		}//end of while loop when finished

		x = nextX;
		y = nextY;
		//for if it lands on blank
		if(city.getGridValue(x,y) == ' '){
			city.setGridValue(x,y,'r');
			noJewel++;

		}
		//if it lands on a jewel
		else if(city.getGridValue(x,y) == 'J'){
			pickUpLoot();
			city.setGridValue(x,y,'r');
			if(isGreedy == true && ((x+y)*(x+y)) % 2 == 0 && turns < 3){
				turns++;
				//if greedy gets to move again but max 3 times
				move(city,police1,police2,robber1,robber2,robber3);
			}
			turns = 0;
			noJewel = 0;
		}
		//if it lands on a cop or arrested robber (since an 'A' can have a cop on it too)
		else if(city.getGridValue(x,y) == 'p' || city.getGridValue(x,y) == 'A' ){

			if(police1.getX() == x && police1.getY() == y){
				//couldnt figure out what to put in as a parameter, did some research and said *this, not sure if we learned this yet or not but i couldnt find another way https://cplusplus.com/forum/general/278436/
				police1.arrest(*this);
				city.setGridValue(x,y,'A');

			}
			//cheacks for both robbers since it is possible for their to be no police officer and just an arrested robber
			else if(police2.getX() == x && police2.getY() == y) {
				police2.arrest(*this);
				city.setGridValue(x,y,'A');
			}
			else{
				//not sure if two robbers with 1 inactive is R or A but R seemed like the rubric was trying to say
				city.setGridValue(x,y,'R');


			}
		}
		//can assume it is another robber
		else{
			//dont need to check if other robber is inactive since inactive robbers are 'A' not r or R
			if(isGreedy == true){
				//if its a greedy robber it loses half of its jewels starting from most recent and loses that loot value of those jewels
				//starts taking from numCollected since that will be the most recent jewel picked up that has a value (not default one that was pre put in bag)
				for(int i = numCollected - 1; i > (numCollected- 1)/2; i--){
					totalLoot -= bag[i].getValue();
					individualLoot -= bag[i].getValue();
					//checks to see if jewel can be placed in original position else it is randomly placed in an empty space
					if(city.getGridValue(bag[i].getX(),bag[i].getY()) != ' '){
						int rX = rand() % 8;
						int rY = rand() % 8;
						while(city.getGridValue(rX,rY) != ' '){
							rX = rand() % 8;
							rY = rand() % 8;
						}
						city.setGridValue(rX,rY, 'J');
					}
					else{
						city.setGridValue(bag[i].getX(),bag[i].getY(), ' ');
					}
					numCollected--;
				}
			}
			city.setGridValue(x,y,'R');
			noJewel++;
		}
		//setting them immobilized for whenever they dont pick up a jewel for five turns including this one
		if(noJewel == 5){
			immobilized = 2;
			noJewel = 0;
		}
  }
		//subtracts an immobilized turn after not moving
		if(isActive == true && immobilized != 0){
			immobilized--;
		}



}

Police::Police(int policeId, int startX, int startY){
	id = policeId;
	x = startX;
	y = startY;
	totalLoot = 0;
	robbersCaught = 0;
}

void Police::arrest(Robber & robber){
        if(robber.getStatus() == true){
		robber.setStatus(false);
		totalLoot += robber.getIndividualLoot();
		robbersCaught++;
		Robber::totalLoot -= robber.getIndividualLoot();
		robber.setIndividualLoot(0);
	}


}
void Police::printPolice(){
	cout<<"\tPolice id: "<<id<<endl;
	cout<<"\t\tConfiscated jewel amount: $"<<totalLoot<<endl;
	cout<<"\t\tFinal number of robber caught: "<<robbersCaught<<endl;
}
void Police::move(City &city,Police & police, Robber &robber1, Robber & robber2, Robber & robber3, Robber & robber4){


	 	bool finished = false;
		//determines whether the police moved to arrest robbers on the previous turn
		//then sets the char to what it will be after the police moves
		if((x == robber1.getX() && y == robber1.getY()) ||(x == robber2.getX() && y == robber2.getY()) ||(x == robber3.getX() && y == robber3.getY())|| (x == robber4.getX() && y == robber4.getY()))
			city.setGridValue(x,y,'A');
		else if(holdChar == 'r' || holdChar == 'R' || holdChar == 'A')
			city.setGridValue(x,y,'A');
		else
			city.setGridValue(x,y,' ');
                int nextX;
                int nextY;
                int val;
                //while loop to continue generating random movement until one is in bounds
                while(finished == false){
                        	val = rand() % 8;
                                nextX = x;
                                nextY = y;

                        switch (val) {
                                case 0:
                                        nextX--;
                                        nextY--;
                                        break;
                                case 1:
                                        nextX--;
                                        break;
                                case 2:
                                        nextX--;
                                        nextY++;
                                        break;
                                case 3:
                                        nextY--;
                                        break;
                                case 4:
                                        nextY++;
                                        break;
                                case 5:
                                        nextX++;
                                        nextY--;
                                        break;
                                case 6:
                                        nextX++;
                                        break;
                                case 7:
                                        nextX++;
					nextY++;
                                        break;
                        }
			//make sure it is not out of bounds
                        if(nextX < 0 ||nextX > 6 ||nextY< 0 ||nextY > 6){
                                finished = false;
                        }
                        else
                                finished = true;

                }//end of while loop when finished
		x = nextX;
		y= nextY;
		holdChar = city.getGridValue(x,y);
		//if moves onto blank
		if(city.getGridValue(x,y) == ' '){
			city.setGridValue(x,y,'p');
		}
		//if moves onto a robber or multiple
		else if(city.getGridValue(x,y) == 'r' || city.getGridValue(x,y) == 'R'){
			//checks what robbers its with and arrests those
			if(robber1.getX() == x && robber1.getY() == y){
				arrest(robber1);
			}
			if(robber2.getX() == x && robber2.getY() == y){
                                arrest(robber2);
                        }
			if(robber3.getX() == x && robber3.getY() == y){
                                arrest(robber3);
                        }
			if(robber4.getX() == x && robber4.getY() == y){
                                arrest(robber4);
                        }
			city.setGridValue(x,y,'A');

		}
		//if finds jewel
		else if(city.getGridValue(x,y) == 'J'){

			city.setGridValue(x,y,'p');
		}
		//can assume it is another cop
		//splits money with eachother and moves again
		else{
			int total = police.getTotalLoot() + totalLoot;
			int split = (total/2);
			police.setTotalLoot(split);
			totalLoot = split;
			move(city,police,robber1,robber2,robber3,robber4);

		}

}



//all setters and getters


char City::getGridValue(int x, int y) const{
	return cityGrid[x][y];
}

void City::setGridValue(int x, int y, char value){
	cityGrid[x][y] = value;
}
bool Robber::getStatus() const{
	return isActive;
}

void Robber::setStatus(bool newStatus){
	isActive = newStatus;
}

int Robber::getIndividualLoot() const{
	return individualLoot;
}

void Robber::setIndividualLoot(int newIndividualLoot){
	individualLoot = newIndividualLoot;
}
int Robber::getX() const {
	return x;
}

int Robber::getY() const {
	return y;
}
int Jewel::getValue() const{
	return value;
}

int Jewel::getX() const{
	return x;
}

int Jewel::getY() const{
	return y;
}
int Police::getX() const {
	return x;
}

int Police::getY() const {
	return y;
}
int Police::getTotalLoot() const {
	return totalLoot;
}
void Police::setTotalLoot(int newLoot) {
	totalLoot = newLoot;
}
int Police::getRobbersCaught() const{
	return robbersCaught;
}
