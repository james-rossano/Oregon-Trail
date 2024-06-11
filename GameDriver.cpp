//Project 2
//James Rossano

#include "Game.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctype.h>

using namespace std;

// splitter used to read from text files
int split(string input_string, char separator, string arr[], const int ARR_SIZE){
    int min = 0;
    int iter = 0;
    int slength = input_string.length();
    for(int i = 0; i < slength; i++){
        
        if(input_string[i] == separator){
            arr[iter] = input_string.substr(min, i-min);
            if(ARR_SIZE-1 == iter){
                return -1;
            }
            arr[iter+1] = input_string.substr(i+1, slength-1);
            min = i+1;
            iter += 1;
        }
        if(i==slength-1 && iter==0){
            arr[0] = input_string;
        }
        
    }
    if(input_string == ""){
        return 0;
    }
    return iter+1;
}
//loads the starting game characters from text files
void loadCharacters(string filename, Entity players[], const int CHARACTERS_SIZE){
    ifstream myfile;
    myfile.open(filename);

    if(myfile.fail()){
        return;
    }

    int idx = 0;
    string placeHold;
    string att[12];

    while(getline(myfile, placeHold) && idx != CHARACTERS_SIZE+1) {
        if(idx != 0){
            split(placeHold,'|',att,12);
            //name|type|health|stamina|defense|condition|advantage|weakness|gold|starting items|number of items|ultimate
            players[idx-1].setCharacter(att[0],att[1][0],stoi(att[2]),stoi(att[3]),stoi(att[4]),att[5][0],att[6],att[7],stoi(att[8]),att[9],att[10],att[11]);
            cout << players[idx-1].getName() << " Loaded" << endl;
        }
        idx++;
    }
}
//loads the starting game enemies from text files
void loadEnemies(string filename, Entity enemies[], const int CHARACTERS_SIZE){
    ifstream myfile;
    myfile.open(filename);

    if(myfile.fail()){
        return;
    }

    int idx = 0;
    string placeHold;
    string att[12];

    while(getline(myfile, placeHold) && idx != CHARACTERS_SIZE+1) {
        if(idx != 0){
            split(placeHold,'|',att,12);
            //name|type|health|stamina|defense|condition|advantage|weakness|gold|starting items|number of items|ultimate
            enemies[idx-1].setCharacter(att[0],att[1][0],stoi(att[2]),stoi(att[3]),stoi(att[4]),att[5][0],att[6],att[7],stoi(att[8]),att[9],att[10],att[11]);
        }
        idx++;
    }
}
//loads all game items from text file
void loadItems(string filename, Potion potions[], Equipment equips[], int POTION_SIZE, int EQUIPMENT_SIZE){
    ifstream myfile;
    myfile.open(filename);

    if(myfile.fail()){
        return;
    }

    int idxP = 0;
    int idxE = 0;
    int idx = 0;
    string placeHold;
    string att[10];

    while(getline(myfile, placeHold)) {
        if(idx != 0){
            split(placeHold,'|',att,10);
            
            if(att[2][0] == 'P'){
                //name|description|type|effect value|element|price
                potions[idxP].name=att[0];
                potions[idxP].desc=att[1];
                potions[idxP].effectVal=stoi(att[3]);
                potions[idxP].price=stoi(att[5]);
                idxP++;
            }else{
                //name|description|type|effect value|element|price
                equips[idxE].name=att[0];
                equips[idxE].desc=att[1];
                equips[idxE].type=att[2][0];
                equips[idxE].effectVal=stoi(att[3]);
                equips[idxE].element=att[4][0];
                equips[idxE].price=stoi(att[5]);
                idxE++;
            }
            
        }
        idx++;
    }
}
//loads all game riddles from text file
void loadRiddles(string filename, Riddle riddles[]){
    ifstream myfile;
    myfile.open(filename);

    if(myfile.fail()){
        return;
    }

    int idx = 0;
    string placeHold;
    string att[3];

    while(getline(myfile, placeHold)) {
        split(placeHold,'|',att,3);
        riddles[idx].text=att[0];
        riddles[idx].answer=att[1];
        idx++;
    }

}
//displays the menu after each player turn
int dispMenu(){
    while(true){
        cout << "1. Move" << endl;
        cout << "2. Swap/Drop Weapon" << endl;
        cout << "3. Use Potion" << endl;
        cout << "4. Print Player Stats" << endl;
        cout << "5. Quit" << endl;

        string option;
        getline(cin,option);

        if(option == "1"){
            return 1;
        }else if(option == "2"){
            return 2;
        }else if(option == "3"){
            return 3;
        }else if(option == "4"){
            return 4;
        }else if(option == "5"){
            cout << "Bye!!" << endl;
            return 5;
        }else{
            cout << "Invalid input. Please enter a valid choice (1-5)" << endl;
        }
    }
}


int main()
{
    Entity players[4] = {};
    Entity enemies[14] = {};
    Potion potions[9] = {};
    Equipment equips[15] = {};
    Riddle riddles[15] = {};

    Game _game;

    //loading in all text files into arrays
    loadCharacters("adv_entity.txt", players, 4);
    loadEnemies("entity.txt", enemies, 14);
    loadItems("items.txt", potions, equips, 9, 15);
    loadRiddles("riddles.txt",riddles);

    //into character selection
    _game.introSeq(players, enemies, potions, equips, riddles);

    //sets all the items to respective players 
    _game.setItems();

    //item shops
    cout << "Player 1 (" << _game.getPlayer(1).getName() << ") Item Shop" << endl;
    _game.itemShop(1);
    cout << "Player 2 (" << _game.getPlayer(2).getName() << ") Item Shop" << endl;
    _game.itemShop(2);
    
    srand (time(NULL));
    Map starterMap = Map();
    // initialize tiles
    starterMap.initializeMap();
    starterMap.displayMap(starterMap);

    //game loop variables
    bool programLoop = true;
    int menuChoice; 
    int dieRoll;
    bool player1Turn = false;
    int backSpaces;
    bool shipWreck = false;
    string landType;
    bool stillTurn;
    int redTileType;
    bool skipForward;
    bool epicCombatLastTurn  = false;

    while(programLoop){
        player1Turn = !player1Turn;
        stillTurn = true;

        //sees if players reach ithaca or died
        if(_game.gameOver()){
            stillTurn = false;
            programLoop = false;
            break;
        }

        //displays player turn and determines if their turn was skipped
        cout << "Player ";
        if(player1Turn){
            cout << "1 Turn" << endl;
            _game.checkStatus(1);
            if(_game.checkTurn(1)){
                stillTurn = false;
            }
        }else{
            cout << "2 Turn" << endl;
            _game.checkStatus(2);
            if(_game.checkTurn(2)){
                stillTurn = false;
            }
        }

        //determines if epic combat is initiated
        if(starterMap.epicCombat() && epicCombatLastTurn == false){
            _game.epicCombat();
            epicCombatLastTurn = true;
            stillTurn = false;
        }else{
            epicCombatLastTurn = false;
        }

        //main program loop for player turn
        while(stillTurn){
            menuChoice = dispMenu();
            stillTurn = false;

            switch(menuChoice){
                //player moving
                case 1:
                    cout << "Rolling a 6 sided die..." << endl;
                    srand (time(NULL));
                    dieRoll = rand() % 6 + 1; 
                    cout << "You rolled a: " << dieRoll << endl;
                    cout << "Updating Map..." << endl;
                    cout << endl;
                    if(player1Turn){
                        starterMap.moveForward(1,dieRoll);
                    }else{
                        starterMap.moveForward(2,dieRoll);
                    }
                    
                    starterMap.displayMap(starterMap);

                    //sees which type of land type player landed on
                    if(player1Turn){
                        _game.movingStamina(1);
                        landType = starterMap.getLandType(1);
                        if(landType == "green"){
                            cout << "You landed on an island" << endl;
                            _game.greenTile(1);
                        }else if(landType == "red"){
                            cout << "You landed on a special tile" << endl;
                            redTileType = starterMap.getSpecialTileType(1);
                            skipForward = _game.redTile(redTileType,1);
                            //if landed on move forward special tile, move forward
                            if(skipForward){
                                starterMap.moveForward(1,4);
                                cout << endl;
                                starterMap.displayMap(starterMap);
                            }
                            

                        }else if(landType == "blue"){
                            shipWreck = _game.blueTile(1);
                            //if shipwreck calamity move backwards
                            if(shipWreck){
                                backSpaces = rand() % 4 + 1;
                                starterMap.moveBackward(1,backSpaces);
                                cout << endl;
                                starterMap.displayMap(starterMap);
                                shipWreck = false;
                            }
                        }else{
                            cout << "You reached Ithaca" << endl;
                            _game.setReachIthaca(1);
                        }   
                        cout << endl;
                    }else{ //does same thing for player 2
                        _game.movingStamina(2);
                        landType = starterMap.getLandType(2);
                        if(landType == "green"){
                            cout << "You landed on an island" << endl;
                            _game.greenTile(2);
                        }else if(landType == "red"){
                            cout << "You landed on a special tile" << endl;
                            redTileType = starterMap.getSpecialTileType(1);
                            skipForward = _game.redTile(redTileType,2);
                            if(skipForward){
                                starterMap.moveForward(2,4);
                                cout << endl;
                                starterMap.displayMap(starterMap);
                            }
                            

                        }else if(landType == "blue"){
                            shipWreck = _game.blueTile(2);
                            if(shipWreck){
                                backSpaces = rand() % 4 + 1;
                                starterMap.moveBackward(2,backSpaces);
                                cout << endl;
                                starterMap.displayMap(starterMap);
                                shipWreck = false;
                            }
                        }else{
                            cout << "You reached Ithaca" << endl;
                            _game.setReachIthaca(2);
                        }   
                        cout << endl; 
                    }

                    break;
                case 2:
                    //runs if player wants to swap equipment
                    if(player1Turn){
                        _game.swapEquipment(1);
                    }else{
                        _game.swapEquipment(2);
                    }
                    cout << endl;
                    break;
                case 3:
                    //runs if player want to use a potion
                    if(player1Turn){
                        _game.usePotion(1);
                    }else{
                        _game.usePotion(2);
                    }
                    cout << endl;
                    break;
                case 4:
                    //runs if player wants to display stats
                    if(player1Turn){
                        _game.displayPlayerStats(1);
                    }else{
                        _game.displayPlayerStats(2);
                    }
                    //turn still remains same player
                    stillTurn = true;
                    break;
                case 5:
                    //exits game if quits
                    programLoop = false;
                    cout << "Quitting Game..." << endl;
                    break;
            }
        }
    }
    //outputs the player stats into a text file at end of game
    _game.exitFile();
}

