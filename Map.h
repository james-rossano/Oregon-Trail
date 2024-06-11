//Project 2
//James Rossano

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Map{
    public:
        // Default constructor
        Map();
        
        // Parametrized Constructor
        Map(int players_num, int size);

        //Setter-Getter pair for position on map
        void setMapPos(string value, int playerID, int index);
        string getMapPos(int playerID, int index);

        //Creates initial map
        void initializeMap();
        //displays new map with updated parameters
        void displayMap(Map);
        //moves player forward/backward given distance
        void moveForward(int player, int dist);
        void moveBackward(int player, int dist);
        //returns the the land type "land","special",etc at index
        string getLandType(int);
        //returns the type of special tile landed on: shortcut, riddle, etc
        int getSpecialTileType(int);
        //returns true if both players on same index (epic combat)
        bool epicCombat();

    private:
        // array of tiles
        string m_mapArr[2][50] = {};
        // player positions
        int player1Pos = 0;
        int player2Pos = 0;

        //Siren's Song Tile, Hidden Treasure, Helios' Beacon Tile, Hidden Treasure, Nymph's Spring Tile, Hidden Treasure, Shortcut Tile
        int specialTileLocations1[7];
        int specialTileLocations2[7];
};

#endif