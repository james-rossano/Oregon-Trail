//Project 2
//James Rossano

#include <iostream>

#include "Map.h"

#define RED "\033[41m"     /* Red */
#define GREEN "\033[42m"   /* Green */
#define BLUE "\033[44m"    /* Blue */
#define MAGENTA "\033[45m" /* Magenta */
#define CYAN "\033[46m"    /* Cyan */
#define RESET "\033[0m"

using namespace std;

Map::Map(){
}

Map::Map(int players_num, int size){
    m_mapArr[players_num][size] = {};
}

// setter for position on map given the value and which player and then the index for their lane
void Map::setMapPos(string value, int playerID, int index){
    m_mapArr[playerID][index] = value;
}

// getter for position on map given which player and then the index for their lane
string Map::getMapPos(int playerID, int index){
    return m_mapArr[playerID][index];
}

void Map::initializeMap(){

    // variables to hold random numbers
    int rand_num1;

    //number of red and green tiles
    int laneRed;
    int laneGreen;

    bool goodLane = false;
    int currentLane = 0;

    while(currentLane <= 1){
        laneRed = 0;
        laneGreen = 0;
        while(goodLane == false){
            for (int i = 0; i < 50; i++){
                
                rand_num1 = rand() % 100 + 1;

                //randomly selects red,green,blue tiles
                if (rand_num1 <= 25 && i > 0 && m_mapArr[currentLane][i-1] != RED){
                    if(currentLane == 0){
                        if(laneRed < 7){
                            specialTileLocations1[laneRed] = i;
                        }
                    }else{
                        if(laneRed < 7){
                            specialTileLocations2[laneRed] = i;
                        }
                    }    
                    m_mapArr[currentLane][i] = RED;
                    laneRed++;
                }
                else if (rand_num1 <= 50 && i > 0 && m_mapArr[currentLane][i-1] != GREEN){            
                    m_mapArr[currentLane][i] = GREEN;
                    laneGreen++;
                }
                else{
                    m_mapArr[currentLane][i] = BLUE;
                }
            }
            if(laneGreen >= 3 && laneRed >= 7){
                //ensures that the game has enough red and green tiles
                goodLane = true;
            }
        }
        goodLane = false;
        currentLane++;
    }
}
// displays map given player 1 and 2 positions
void Map::displayMap(Map starterMap){
    for(int i = 0; i < 50; i++){
        if(i == player1Pos){
            cout << starterMap.getMapPos(0,i) << "1" << " " << RESET << " "; 
            continue;
        }
        cout << starterMap.getMapPos(0,i) << "  " << RESET << " "; 
    }

    cout << endl;
    cout << endl;

    for(int i = 0; i < 50; i++){
        if(i == player2Pos){
            cout << starterMap.getMapPos(1,i) << "2" << " " << RESET << " ";
            continue; 
        }
        cout << starterMap.getMapPos(1,i) << "  " << RESET << " "; 
    }

    cout << RESET << endl;
    cout << endl;
}
// moves player forward a given distance
void Map::moveForward(int playerID, int dist){
    if(playerID == 1){
        for(int i = player1Pos+1; i <= player1Pos+dist; i++){
            if(i >= 49){
                break;
            }
            if(getMapPos(0,i) == GREEN){
                dist = (i) - player1Pos;
            }
        }
        player1Pos += dist;
        if(player1Pos > 49){
            player1Pos = 49;
        }
    }else{
        for(int i = player2Pos+1; i <= player2Pos+dist; i++){
            if(i >= 49){
                break;
            }
            if(getMapPos(1,i) == GREEN){
                dist = (i) - player2Pos;
            }
        }
        player2Pos += dist;
        if(player2Pos > 49){
            player2Pos = 49;
        }
    }
}
// moves player backwards a given distance
void Map::moveBackward(int playerID, int dist){
    if(playerID == 1){
        if(player1Pos-dist < 0){
            dist = player1Pos;
        }
        for(int i = player1Pos; i >= player1Pos-dist; i--){
            if(getMapPos(0,i) == GREEN){
                dist = (i) - player1Pos;
            }
        }
        player1Pos -= dist;
        if(player1Pos <= 0){
            player1Pos = 0;
        }
    }else{
        if(player1Pos-dist < 0){
            dist = player1Pos;
        }
        for(int i = player2Pos; i >= player2Pos-dist; i--){
            if(getMapPos(1,i) == GREEN){
                dist = (i) - player2Pos;
            }
        }
        player2Pos -= dist;
        if(player2Pos <= 0){
            player2Pos = 0;
        }
    }
}
//returns land type that given player number is on
string Map::getLandType(int playerID){
    if(player1Pos == 49){
            return "Ithaca";
        }
    if(playerID == 1){
        if(getMapPos(0,player1Pos) == BLUE){
            return "blue";
        }else if(getMapPos(0,player1Pos) == GREEN){
            return "green";
        }else{
            return "red";
        }
    }else{
        if(player2Pos == 49){
            return "Ithaca";
        }
        if(getMapPos(1,player2Pos) == BLUE){
            return "blue";
        }else if(getMapPos(1,player2Pos) == GREEN){
            return "green";
        }else{
            return "red";
        }
    }
}
//returns the special tile type that a given player is on
int Map::getSpecialTileType(int playerNum){
    if(playerNum == 1){
        for(int i = 0;i < 7;i++){
            if(specialTileLocations1[i] == player1Pos){
                return i;
            }
        }
        return 6;
    }else{
        for(int i = 0;i < 7;i++){
            if(specialTileLocations2[i] == player2Pos){
                return i;
            }
        }
        return 6;
    }
    
}
//sees if epic combat should be initiated
bool Map::epicCombat(){
    if(player1Pos == player2Pos && player1Pos != 0){
        return true;
    }else{
        return false;
    }
}