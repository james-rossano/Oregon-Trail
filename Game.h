//Project 2
//James Rossano

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Entity.h"
using namespace std;

class Game{
    private:
        Entity player1;
        Entity player2;

        //creates initial game component arrays
        Entity enemies[14] = {};
        //indicated the epic enemy index numbers
        //int epicEnemies[3] = {8,9,7};
        Potion potions[9] = {};
        Equipment equips[15] = {};
        Riddle riddles[15] = {};

        //3 randomized item shop array containers
        int itemShopEquips[3] = {};
        int itemShopPotions[3] = {};

        //containers for character inventories, equips, etc. Is set to -1 if empty
        int p1Potions[3] = {-1,-1,-1};
        int p1Equiped[2] = {-1,-1};
        int p1ExcessEquips[5] = {-1,-1,-1,-1,-1};
        int p2Potions[3] = {-1,-1,-1};
        int numPerPotion[3] = {1,1,1};
        int p2Equiped[2] = {-1,-1};
        int p2ExcessEquips[5] = {-1,-1,-1,-1,-1};
        int enemyEquips[2] = {-1,-1};
        int enemyPotions[2] = {-1,-1};

        //calamity chance for each player. random number (1-20) >= 12 = 40%
        //increases by 1 for calamity chance to increase by 5%
        int p1CalamityChance = 12;
        int p2CalamityChance = 12;

        //player ailment variables
        bool p1Poisoned = false;
        bool p2Poisoned = false;

        bool p1Diseased = false;
        bool p2Diseased = false;

        //determines if player turn is skipped from calamity or out of stamina
        bool p1SkipTurn;
        bool p2SkipTurn;

        bool p1Dead = false;
        bool p2Dead = false;

        bool p1AtIthaca = false;
        bool p2AtIthaca = false;

    public:
        //default constructor
        Game();
        //parameterized constructor
        Game(Entity, Entity);
        //player selection and setter for component arrays
        void introSeq(Entity _players[], Entity enemies[], Potion potions[], Equipment equips[], Riddle riddles[]);

        //getter functions
        Entity getPlayer(int);
        Riddle getRiddle(int);
        Equipment getEquip(int);
        Entity getEnemy(int);
        Potion getPotion(int);

        //sets intial items for characters
        void setItems();

        //adds potions/equips to player inventory
        void addPotion(int potNum,int playerNum);
        void addEquip(int eNum,int playerNum);

        //displays equips and potions for item shop
        void displayEquips();
        void displayPotions();
        
        void itemShop(int);

        //displays enemy and player stats
        void displayPlayerStats(int);
        void displayEnemyStats(Entity);

        //runs combat, calamities, hidden treasure, etc for given land type
        bool redTile(int tiletype, int playerNum);
        void greenTile(int playerNum);
        bool blueTile(int playerNum);

        //displays and determines if riddle was correctly answered
        void hiddenTreasure(int);

        //updates stamina when player moves
        void movingStamina(int);

        //detemines if player turn
        bool checkTurn(int);
        //updates player ailments (poisoned/dieased)
        void checkStatus(int);

        //updates player variables if reached ithaca
        void setReachIthaca(int);
        //determines if game is over
        bool gameOver();

        //swaps equipment given player number
        void swapEquipment(int);
        //uses potion from player inventory
        void usePotion(int);
        //adds potion stats to player given potion index
        void consumePotion(int,int);

        //displays character data to txt file
        void exitFile();
        
        //land island combat
        void combat(Entity player, Entity enemy, int);
        //two player epic combat
        void epicCombat();      
};


#endif

