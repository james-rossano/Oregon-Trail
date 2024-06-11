//Project 2
//James Rossano

#include "Game.h"

//same as split function, used for data manipulation
int spliter(string input_string, char separator, string arr[], const int ARR_SIZE){
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
//default constructor
Game::Game(){
}
//parameterized constructor
Game::Game(Entity _player1, Entity _player2){
    player1 = _player1;  
    player2 = _player2; 
}
//returns the player entity given player number
Entity Game::getPlayer(int playNum){
    if(playNum == 1){
        return player1;
    }else{
        return player2;
    }
}
//returns potion given potion index
Potion Game::getPotion(int idx){
    return potions[idx];
}
//returns equipment given equipment index
Equipment Game::getEquip(int idx){
    return equips[idx];
}
//returns riddle given riddle idex
Riddle Game::getRiddle(int idx){
    return riddles[idx];
}
//returns enemy given enemy index
Entity Game::getEnemy(int idx){
    return enemies[idx];
}
//runs intro sequence character selection and assigns initial data to arrays
void Game::introSeq(Entity _players[], Entity _enemies[], Potion _potions[], Equipment _equips[], Riddle _riddles[]){
    cout << "Player 1" << endl;
    cout << "Here is a list of players you can select from:" << endl;

    for(int i = 0; i < 4; i++){
        cout << i+1 << " " << _players[i].getName() << " ";
    }
    cout << endl;
    
    string player1Select;
    cout << "The selected character (1-4) is:" << endl;
    getline(cin,player1Select);

    
    int player1index;

    while(!(player1Select == "1" || player1Select == "2" || player1Select == "3" || player1Select == "4")){
        cout << "Invalid selection. Select from the list!" << endl;
        for(int i = 0; i < 4; i++){
            cout << i+1 << " " << _players[i].getName() << " ";
        }
        cout << endl;
        cout << "The selected character (1-4) is:" << endl;
        getline(cin,player1Select);
    }

    player1index = stoi(player1Select)-1;


    cout << "Player 2" << endl;
    cout << "Here is a list of players you can select from:" << endl;

    int idx = 1;
    for(int i = 0; i < 4; i++){
        if(player1index == i){
            continue;
        }
        cout << idx << " " << _players[i].getName() << " ";
        idx++;
    }
    cout << endl;
    
    string player2Select;
    cout << "The selected character (1-3) is:" << endl;
    getline(cin,player2Select);

    
    int player2index;

    while(!(player2Select == "1" || player2Select == "2" || player2Select == "3")){
        cout << "Invalid selection. Select from the list!" << endl;
        idx = 1;
        for(int i = 0; i < 4; i++){
            if(player1index == i){
                continue;
            }
            cout << idx << " " << _players[i].getName() << " ";
            idx++;
        }
        cout << endl;
        cout << "The selected character (1-3) is:" << endl;
        getline(cin,player2Select);
    }
    if(stoi(player2Select) >= player1index+1){
        player2index = stoi(player2Select);
    }else{
        player2index = stoi(player2Select)-1;
    }

    player1 = _players[player1index];
    player2 = _players[player2index];
    
    for(int i = 0; i < 14; i++){
        enemies[i] = _enemies[i];
    }
    for(int i = 0; i < 15; i++){
        riddles[i] = _riddles[i];
    }
    for(int i = 0; i < 9; i++){
        potions[i] = _potions[i];
    }
    for(int i = 0; i < 15; i++){
        equips[i] = _equips[i];
    }
}
//set characters starting items
void Game::setItems(){
    string SItems = player1.getSItems();
    string items[5];
    spliter(SItems,',',items,5);
    for(int i = 0; i < 2; i++){
        if(i > 0){
            items[i] = items[i].substr(1,-1);
        }
        for(int g = 0; g < 15; g++){
            if(items[i] == equips[g].name){
                addEquip(g,1);
            }
        }
        
        if(items[i] == "Health Potion"){
            addPotion(0,1);
        }
        
    }

    SItems = player2.getSItems();
    string item[5];
    spliter(SItems,',',item,5);
    for(int i = 0; i < 2; i++){
        if(i > 0){
            item[i] = item[i].substr(1,-1);
        }
        for(int g = 0; g < 15; g++){
            if(item[i] == equips[g].name){
                addEquip(g,2);
                
            }
        }
        
        if(item[i] == "Health Potion"){
            addPotion(0,2);
        }
    }
}
//adds potion to player inventory
void Game::addPotion(int potNum,int playerNum){
    if(playerNum == 1){
        for(int i = 0;i < 3; i++){
            if(p1Potions[i] >= 0){
                continue;
            }else{
                p1Potions[i] = potNum;
                return;
            }
        }
        cout << "Potion Inventory Full" << endl;
    } else if(playerNum == 2){
        for(int i = 0;i < 3; i++){
            if(p2Potions[i] >= 0){
                continue;
            }else{
                p2Potions[i] = potNum;
                return;
            }
        }
        cout << "Potion Inventory Full" << endl;
    } else{
        enemyPotions[0] = potNum;
    }
}
//adds equipment to player inventory
void Game::addEquip(int eNum,int playerNum){
    if(playerNum == 1){
        if(equips[eNum].type == 'D'){
            if(p1Equiped[0] >= 0){
                cout << "Equiped Items are full. Adding item to inventory" << endl;
                for(int i = 0; i < 5; i++){
                    if(p1ExcessEquips[i] < 0){
                        p1ExcessEquips[i] = eNum;
                        return;
                    }
                }
            }else{
                p1Equiped[0] = eNum;
            }
        }else{
            if(p1Equiped[1] >= 0){
                cout << "Equiped Items are full. Adding item to inventory" << endl;
                for(int i = 0; i < 5; i++){
                    if(p1ExcessEquips[i] < 0){
                        p1ExcessEquips[i] = eNum;
                        return;
                    }
                }
            }else{
                p1Equiped[1] = eNum;
            }
        }
    }else if(playerNum == 2){
        if(equips[eNum].type == 'D'){
            if(p2Equiped[0] >= 0){
                cout << "Equiped Items are full. Adding item to inventory" << endl;
                for(int i = 0; i < 5; i++){
                    if(p2ExcessEquips[i] < 0){
                        p2ExcessEquips[i] = eNum;
                        return;
                    }
                }
            }else{
                p2Equiped[0] = eNum;
            }
        }else{
            if(p2Equiped[1] >= 0){
                cout << "Equiped Items are full. Adding item to inventory" << endl;
                for(int i = 0; i < 5; i++){
                    if(p2ExcessEquips[i] < 0){
                        p2ExcessEquips[i] = eNum;
                        return;
                    }
                }
            }else{
                p2Equiped[1] = eNum;
            }
        }
    } else{
        if(eNum == 50 || eNum == 60){
            enemyEquips[0] = 5;
        }
        if(equips[eNum].type == 'D'){
            
            enemyEquips[0] = eNum;
        }else{
            enemyEquips[1] = eNum;
        }
    }
}
//creates randomized item shop for player
void Game::itemShop(int playerNum){
    cout << "1. Buy Weapon" << endl;
    cout << "2. Buy Potion" << endl;
    cout << "3. Leave Shop" << endl;

    string userIn;
    getline(cin, userIn);

    while(!(userIn == "1" || userIn == "2" || userIn == "3")){
        cout << "Invalid Input, Choose Again" << endl;
        cout << "1. Buy Weapon" << endl;
        cout << "2. Buy Potion" << endl;
        cout << "3. Leave Shop" << endl;
        getline(cin, userIn);
    }

    if(userIn == "1"){
        if(playerNum == 1){
            displayEquips();
            cout << "You have: " << player1.getGold() << " gold" << endl;
            
            string userIn;
            bool invalid = true;
            while(invalid){
                cout << "Select the item number (integer) or \"-1\" to leave shop" << endl;
                getline(cin, userIn);

                if(userIn == "-1"){
                    break;
                }

                for(int i = 0; i < 3; i++){
                    if(to_string(itemShopEquips[i]+1) == userIn){
                        invalid = false;
                    }
                }

                if(invalid == true){
                    cout << "Invalid Input" << endl;
                }else if(player1.getGold() < equips[stoi(userIn)-1].price){
                    cout << "Not enought gold" << endl;
                    invalid = true;
                }
            }
            if(!invalid){
                cout << "You bought: " << equips[stoi(userIn)-1].name << endl;

                player1.setGold(player1.getGold() - equips[stoi(userIn)-1].price);
                addEquip(stoi(userIn)-1,1);
                cout << endl;

            }else{
                cout << "leaving item shop" << endl;
                cout << endl;
            }
        }else{ 
            displayEquips();
            cout << "You have: " << player2.getGold() << " gold" << endl;
            
            string userIn;
            bool invalid = true;
            while(invalid){
                cout << "Select the item number (integer) or \"-1\" to leave shop" << endl;
                getline(cin, userIn);

                if(userIn == "-1"){
                    break;
                }

                for(int i = 0; i < 3; i++){
                    if(to_string(itemShopEquips[i]+1) == userIn){
                        invalid = false;
                    }
                }

                if(invalid == true){
                    cout << "Invalid Input" << endl;
                }else if(player2.getGold() < equips[stoi(userIn)-1].price){
                    cout << "Not enought gold" << endl;
                    invalid = true;
                }
            }
            if(!invalid){
                cout << "You bought: " << equips[stoi(userIn)-1].name << endl;

                player2.setGold(player2.getGold() - equips[stoi(userIn)-1].price);
                addEquip(stoi(userIn)-1,2);
                cout << endl;
                
            }else{
                cout << "leaving item shop" << endl;
                cout << endl;
            }
        }

    }else if(userIn == "2"){
        if(playerNum == 1){
            displayPotions(); 
            cout << "You have: " << player1.getGold() << " gold" << endl;
            
            string userIn;
            bool invalid = true;
            while(invalid){
                cout << "Select the item number (integer) or \"-1\" to leave shop" << endl;
                getline(cin, userIn);

                if(userIn == "-1"){
                    break;
                }

                for(int i = 0; i < 3; i++){
                    if(to_string(itemShopPotions[i]+1) == userIn){ 
                        invalid = false;
                    }
                }

                if(invalid == true){
                    cout << "Invalid Input" << endl;
                }else if(player1.getGold() < potions[stoi(userIn)-1].price){
                    cout << "Not enought gold" << endl;
                    invalid = true;
                }
            }
            if(!invalid){
                cout << "You bought: " << potions[stoi(userIn)-1].name << endl;

                player1.setGold(player1.getGold() - potions[stoi(userIn)-1].price);
                addPotion(stoi(userIn)-1,1);
                cout << endl;

            }else{
                cout << "leaving item shop" << endl;
                cout << endl;
            }
        }else{ 
            displayPotions(); 
            cout << "You have: " << player2.getGold() << " gold" << endl;
            
            string userIn;
            bool invalid = true;
            while(invalid){
                cout << "Select the item number (integer) or \"-1\" to leave shop" << endl;
                getline(cin, userIn);

                if(userIn == "-1"){
                    break;
                }

                for(int i = 0; i < 3; i++){
                    if(to_string(itemShopPotions[i]+1) == userIn){ 
                        invalid = false;
                    }
                }

                if(invalid == true){
                    cout << "Invalid Input" << endl;
                }else if(player2.getGold() < potions[stoi(userIn)-1].price){
                    cout << "Not enought gold" << endl;
                    invalid = true;
                }
            }
            if(!invalid){
                cout << "You bought: " << potions[stoi(userIn)-1].name << endl;

                player2.setGold(player2.getGold() - potions[stoi(userIn)-1].price);
                addPotion(stoi(userIn)-1,2);
                cout << endl;

            }else{
                cout << "leaving item shop" << endl;
                cout << endl;
            }
        }
    }else if(userIn == "3"){
        cout << "Leaving Item Shop" << endl;
        cout << endl;
    }
}
//displays random 3 equipment for item shop
void Game::displayEquips(){
    int numItems = 0;
    srand (time(NULL));
    bool redo = false;

    while(numItems < 3){
        
        int randItem = rand() % 15; 

        if(equips[randItem].price == 0){
            continue;
        }

        for(int i = 0; i < 3; i++){
            if(p1Equiped[i] == randItem || p2Equiped[i] == randItem || p1ExcessEquips[i] == randItem || p2ExcessEquips[i] == randItem || itemShopEquips[i] == randItem){
                redo = true;
            }
        }

        if(!(redo)){
            cout << "(" << randItem+1 << ") " << equips[randItem].name << endl;
            cout << equips[randItem].desc << endl;
            cout << "Type: " << equips[randItem].type << endl;
            cout << "Element: " << equips[randItem].element << endl;
            cout << "Effect Value: " << equips[randItem].effectVal << endl;
            cout << "Price: " << equips[randItem].price << endl;
            cout << "--------------------------------" << endl;

            itemShopEquips[numItems] = randItem;
            
            numItems++;
        }
        redo = false;
    }
}
//displays random 3 potions for item shop
void Game::displayPotions(){
    int numItems = 0;
    srand (time(NULL));
    int prevNum = -1;
    int randItem;

    while(numItems < 3){
        while(randItem == prevNum){
            randItem = rand() % 9; 
        }
        prevNum = randItem;
        
        cout << "(" << randItem+1 << ") " << potions[randItem].name << endl;
        cout << potions[randItem].desc << endl;
        cout << "Effect Value: " << potions[randItem].effectVal << endl;
        cout << "Price: " << potions[randItem].price << endl;
        cout << "--------------------------------" << endl;

        itemShopPotions[numItems] = randItem;
        
        numItems++;
    }
}
//display player stats given player number
void Game::displayPlayerStats(int playerNum){
    if(playerNum == 1){
        cout << "--------------------------------" << endl;
        cout << "Player: " << player1.getName() << endl;
        cout << "Health: " << player1.getHP() << endl;
        cout << "Condition: " << player1.getCondition() << endl;
        cout << "Stamina: " << player1.getStamina() << endl;
        cout << "Defense: " << player1.getDefense() << endl;
        cout << "Gold: " << player1.getGold() << endl;
        cout << "Equiped Items: ";
        for(int i = 0; i < 2; i++){
            if(p1Equiped[i] >= 0){
                cout << equips[p1Equiped[i]].name << " ";
            }
        }
        cout << endl;
        cout << "Inventory Items: ";
        for(int i = 0; i < 5; i++){
            if(p1ExcessEquips[i] >= 0){
                cout << equips[p1ExcessEquips[i]].name << " ";
            }
        }
        cout << endl;
        cout << "Potions: ";
        for(int i = 0; i < 3; i++){
            if(p1Potions[i] >= 0){
                cout << potions[p1Potions[i]].name << " ";
            }
        }
        cout << endl;
        cout << "--------------------------------" << endl;
    } else{
        cout << "--------------------------------" << endl;
        cout << "Player: " << player2.getName() << endl;
        cout << "Health: " << player2.getHP() << endl;
        cout << "Condition: " << player2.getCondition() << endl;
        cout << "Stamina: " << player2.getStamina() << endl;
        cout << "Defense: " << player2.getDefense() << endl;
        cout << "Gold: " << player2.getGold() << endl;
        cout << "Equiped Items: ";
        for(int i = 0; i < 2; i++){
            if(p2Equiped[i] >= 0){
                cout << equips[p2Equiped[i]].name << " ";
            }
        }
        cout << endl;
        cout << "Inventory Items: ";
        for(int i = 0; i < 5; i++){
            if(p2ExcessEquips[i] >= 0){
                cout << equips[p2ExcessEquips[i]].name << " ";
            }
        }
        cout << endl;
        cout << "Potions: ";
        for(int i = 0; i < 3; i++){
            if(p2Potions[i] >= 0){
                cout << potions[p2Potions[i]].name << " ";
            }
        }
        cout << endl;
        cout << "--------------------------------" << endl;
    }
}
//displays enemy stats given enemy index
void Game::displayEnemyStats(Entity Enemy){
    cout << "--------------------------------" << endl;
    cout << "Enemy: " << Enemy.getName() << endl;
    cout << "Health: " << Enemy.getHP() << endl;
    cout << "Condition: " << Enemy.getCondition() << endl;
    cout << "Stamina: " << Enemy.getStamina() << endl;
    cout << "Defense: " << Enemy.getDefense() << endl;
    cout << "Gold: " << Enemy.getGold() << endl;

    if(enemyEquips[0] != -1){
        cout << "Items: " << equips[enemyEquips[0]].name << endl;
    }else if(Enemy.getName() == "Giants"){
        cout << "Items: Maul of the Giants" << endl;
    }else{
        cout << "Items: Tidal Charm of the Sirens" << endl;
    }
    cout << "Potions: " << potions[enemyPotions[0]].name << endl;
    cout << "Weakness: " << Enemy.getWeakness() << endl;
    cout << "--------------------------------" << endl;
}
//runs if player lands on 'special' red tile
bool Game::redTile(int tileType, int playerNum){
    switch(tileType){
        case(0):
            cout << "As the Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen. You stop in your tracks. You cannot move on your next turn only." << endl;  
            if(playerNum == 1){
                p1SkipTurn = true;
            }else{
                p2SkipTurn = true;
            }
            break;
        case(1):
            cout << "You landed on a hidden treasure!" << endl;
            if(playerNum == 1){
                hiddenTreasure(1);
            }else{
                hiddenTreasure(2);
            }
            
            break;
        case(2):
            cout << "As you stand in the brilliance of Helios' Beacon, you feel the warmth of the sun god's favor shining upon you. You feel luckier. Reduce calamity chances by 5%, permanently" << endl;
            if(playerNum == 1){
                p1CalamityChance += 1;
            }else{
                p2CalamityChance += 1;
            }
            break;
        case(3):
            cout << "You landed on a hidden treasure!" << endl;
            if(playerNum == 1){
                hiddenTreasure(1);
            }else{
                hiddenTreasure(2);
            }
            break;
        case(4):
            cout << "In the embrace of the Nymph's Spring, you feel the embrace of nature itself. Your stamina is replenished." << endl;
            player1.setStamina(100 - player1.getStamina());
            break;
        case(5):
            cout << "You landed on a hidden treasure!" << endl;
            if(playerNum == 1){
                hiddenTreasure(1);
            }else{
                hiddenTreasure(2);
            }
            break;
        case(6):
            cout << "Your spirits soar as you're propelled four tiles ahead. Ithaca isn't far." << endl;
            return true;
            break;
        default:
            cout << "Your spirits soar as you're propelled four tiles ahead. Ithaca isn't far." << endl;
            return true;
            break;
    }
    return false;
    //Siren's Song Tile, Hidden Treasure, Helios' Beacon Tile, Hidden Treasure, Nymph's Spring Tile, Hidden Treasure, Shortcut Tile
}
//diplays riddles if player lands on hidden treasure
void Game::hiddenTreasure(int playerNum){
    srand (time(NULL));
    int randRiddle = rand() % 15;
    int randNum;
    cout << riddles[randRiddle].text << endl;
    string answer;
    getline(cin,answer);
    if(answer == riddles[randRiddle].answer){
        cout << "That is the correct answer!" << endl;
        srand (time(NULL));
        randNum = rand() % 10;
        if(randNum >= 3){
            randNum = 5 + (rand() % 6);
            cout << "You recieved a " << randNum << " point damage buff!" << endl;
            if(playerNum == 1){
                equips[p1Equiped[0]].effectVal += randNum;
            }else{
                equips[p2Equiped[0]].effectVal += randNum;
            }
        }else if(randNum <= 6){
            randNum = 10 + (rand() % 21);
            cout << "You recieved a " << randNum << " point stamina refill!" << endl;
            if(playerNum == 1){
                player1.setStamina(randNum);
            }else{
                player2.setStamina(randNum);
            }
        }else{
            randNum = 20 + (rand() % 21);
            cout << "You recieved " << randNum << " gold via a Gold Windfall!" << endl;
            if(playerNum == 1){
                player1.setGold(randNum);
            }else{
                player2.setGold(randNum);
            }
        }
    }else{
        cout << "That answer is incorrect" << endl;
    }
}
//initiates combat if player lands on green land tile
void Game::greenTile(int playerNum){
    int randIslandEnemy = rand() % 7;
    cout << "You are fighting " << enemies[randIslandEnemy].getName().substr(0,-1) << endl;

    if(playerNum == 1){
        combat(player1,enemies[randIslandEnemy],1);
    }else{
        combat(player2,enemies[randIslandEnemy],2);
    }
    
}
//determines if calamity occurs if player lands on blue tile
bool Game::blueTile(int playerNum){
    srand (time(NULL));
    int calamity;
    if(playerNum == 1){
        calamity = rand() % 21 + 1;
        if(calamity > p1CalamityChance){
            cout << "You recieved a Calamity" << endl;
            calamity = rand() % 21 + 1;
            if(calamity <= 4){
                cout << "Poisonous Rats: Much to your dismay, it seems you are not the only one on your ship" << endl;
                cout << "*You recieved the poisoned ailment*" << endl;
                p1Poisoned = true;
            }else if(calamity <= 11){
                cout << "Plague Outbreak: The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality" << endl;
                cout << "*You recieved the diseased ailment*" << endl;
                p1Diseased = true;
            }else{
                cout << "Stormy Seas: With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon" << endl;
                return true;
            }
        }else{
            cout << "Nothing Happens" << endl;
        }
    }else{
        calamity = rand() % 21 + 1;
        if(calamity > p2CalamityChance){
            cout << "You recieved a Calamity" << endl;
            calamity = rand() % 21 + 1;
            if(calamity <= 4){
                cout << "Poisonous Rats: Much to your dismay, it seems you are not the only one on your ship" << endl;
                cout << "*You recieved the poisoned ailment*" << endl;
                p2Poisoned = true;
            }else if(calamity <= 11){
                cout << "Plague Outbreak: The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality" << endl;
                cout << "*You recieved the diseased ailment*" << endl;
                p2Diseased = true;
            }else{
                cout << "Stormy Seas: With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon" << endl;
                return true;
            }
        }else{
            cout << "Nothing Happens" << endl;
        }
    }
    return false;
}
//if player is poisoned or diseased, health/stamina is depleted each turn
void Game::checkStatus(int pTurn){
    if(pTurn == 1){
        if(p1Poisoned){
            player1.setHealth(-5);
        }
        if(p2Diseased){
            player1.setStamina(-5);
        }
        if(player1.getHP() <= 0){
            p1Dead = true;
        }
    }else{
        if(p2Poisoned){
            player2.setHealth(-5);
        }
        if(p2Diseased){
            player2.setStamina(-5);
        }
        if(player2.getHP() <= 0){
            p2Dead = true;
        }
    }
}
//determines if player turn is skipped because they are dead or out of stamina
bool Game::checkTurn(int playerNum){
    if(playerNum == 1){
        if(p1AtIthaca){
            cout << "Player 1 is reached Ithaca" << endl;
            return true;
        }
        if(p1Dead){
            cout << "Player 1 is dead" << endl;
            return true;
        }
        if(player1.getStamina() <= 0){
            player1.setStamina(20);
            return true;
        }
        if(p1SkipTurn == true){
            cout << "Turn skipped" << endl;
            p1SkipTurn = false;
            return true;
        }
        return false;
    }else{
        if(p2AtIthaca){
            cout << "Player 2 is reached Ithaca" << endl;
            return true;
        }
        if(p2Dead){
            cout << "Player 2 is dead" << endl;
            return true;
        }
        if(player2.getStamina() <= 0){
            player1.setStamina(20);
            return true;
        }
        if(p2SkipTurn == true){
            cout << "Turn skipped" << endl;
            p2SkipTurn = false;
            return true;
        }
        return false;
    }
}
//updates player stamina from moving
void Game::movingStamina(int playerNum){
    if(playerNum == 1){
        player1.setStamina(-5);
    }else{
        player2.setStamina(-5);
    }
}
//checks if game is over from reaching ithaca or dieing
bool Game::gameOver(){
    if(p1AtIthaca){
        cout << "Player 1 has reached Ithaca! Player 1 Wins!" << endl;
        return true;
    } else if(p2AtIthaca){
        cout << "Player 2 has reached Ithaca! Player 2 Wins!" << endl;
        return true;
    } else if(p1Dead && p2Dead){
        cout << "Both players have died" << endl;
        return true;
    }else{
        return false;
    }
}
//land combat function used to face random land enemy
void Game::combat(Entity player, Entity enemy, int playerNum){
    //setting enemy starting items
    string SItems = enemy.getSItems();
    string items[2];
    spliter(SItems,',',items,5);
    for(int i = 0; i < 2; i++){
        if(i > 0){
            items[i] = items[i].substr(1,-1);
        }
        for(int g = 0; g < 15; g++){
            if(items[i] == equips[g].name){
                addEquip(g,3);
            }
        }
        if(items[i] == "Health Potion"){
            addPotion(0,3);
        }
        if(items[i] == "Tidal Charm of the Sirens"){
            addEquip(50,3);
        }
        if(items[i] == "Maul of the Giants"){
            addEquip(60,3);
        }
        
    }
    displayPlayerStats(playerNum);
    displayEnemyStats(enemy);
    bool playerTurn = true;
    bool attacking = true;
    int playerAttack;
    int enemyAttack;
    string playerChoice;
    //determines advantage then uses coin toss
    if(enemy.getAdvantage() == "True"){
        playerTurn = false;
        cout << "Enemy won has advantage and attacks first" << endl;
    }else{
        if(rand() % 2 > 0){
            playerTurn = false;
            cout << "Enemy won coin toss and attacks first" << endl;
        }else{
            cout << "You won the coin toss and can go first" << endl;
        }
    }
    
    while(attacking){
        if(playerTurn){
            cout << "Player's Turn" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Use Potion" << endl;
            cout << "3. Swap Weapon" << endl;
            cout << "4. Attempt to Run" << endl;
            getline(cin,playerChoice);
            if(playerChoice == "1"){
                if(playerNum == 1){
                    //if not weapon equipeed, player attacks with fists
                    if(p1Equiped[0] == -1){
                        playerAttack = 5;
                        cout << "You attacked with your fists";
                    }else{
                        playerAttack = equips[p1Equiped[0]].effectVal;
                        //damage buff if weapon element is the enemy weakness
                        if(equips[p1Equiped[0]].type == enemy.getWeakness()[0]){
                            playerAttack = playerAttack * 2;
                        }
                        cout << "You attacked with " << equips[p1Equiped[0]].name;
                    }
                }else{
                    if(p2Equiped[0] == -1){
                        playerAttack = 5;
                        cout << "You attacked with your fists";
                    }else{
                        playerAttack = equips[p2Equiped[0]].effectVal;
                        if(equips[p2Equiped[0]].type == enemy.getWeakness()[0]){
                            playerAttack = playerAttack * 2;
                        }
                        cout << "You attacked with " << equips[p2Equiped[0]].name;
                    }
                }
                playerAttack = rand() % playerAttack + 1;
                playerAttack = playerAttack * 3.5;
                //subtracts enemy defense
                playerAttack -= enemy.getDefense();
                if(playerAttack <= 0){
                    playerAttack = 1;
                }
                cout << " for " << playerAttack << " damage" << endl;
                enemy.setHealth(-playerAttack);
                cout << enemy.getName() << " has " << enemy.getHP() << " HP" << endl;
            }else if(playerChoice == "2"){
                int initialHealth; 
                int initialStam;

                if(playerNum == 1){
                    initialHealth = player1.getHP();
                    initialStam = player1.getStamina();
                }else{
                    initialHealth = player2.getHP();
                    initialStam = player2.getStamina();
                }
                
                usePotion(playerNum);

                if(playerNum == 1){
                    player.setHealth(player1.getHP() - initialHealth);
                    player.setStamina(player1.getStamina() - initialStam);
                }else{
                    player.setHealth(player2.getHP() - initialHealth);
                    player.setStamina(player2.getStamina() - initialStam);
                }
            }else if(playerChoice == "3"){
                swapEquipment(playerNum);
            }else if(playerChoice == "4"){
                if(rand() % 10 > 5){
                    if(player.getStamina() >= 35){
                        cout << "Running away was successful" << endl;
                        cout << "The fight is over" << endl;
                        player.setStamina(-35);
                        attacking  = false;
                    }else{
                        cout << "You don't have enough stamina to run away" << endl;
                    }
                }else{
                    cout << "Running away was unsuccessful" << endl;
                }
            }else{
                cout << "Invalid selection" << endl;
                continue;
            }

        }else{
            cout << "--------------------------------" << endl;
            cout << "Enemy's Turn" << endl;
            enemyAttack = equips[enemyEquips[0]].effectVal;
            cout << "Enemy attacked with " << equips[enemyEquips[0]].name;
            enemyAttack = rand() % enemyAttack + 1;
            if(playerNum == 1){
                enemyAttack -= player1.getDefense();
            }else{
                enemyAttack -= player2.getDefense();
            }
            if(p1Equiped[1] != -1){
                enemyAttack -= equips[p1Equiped[1]].effectVal;
            }
            if(enemyAttack <= 0){
                enemyAttack = 1;
            }
            enemyAttack = enemyAttack * 2.5;
            cout << " for " << enemyAttack << " damage" << endl;
            player.setHealth(-enemyAttack);
            cout << player.getName() << " has " << player.getHP() << " HP" << endl;

            cout << "--------------------------------" << endl;
        }
        if(player.getHP() <= 0){
            cout << "You died" << endl;
            attacking = false;
        }
        if(enemy.getHP() <= 0){
            attacking = false;
            cout << "You won the fight!" << endl;
            cout << "Gained: " << enemy.getGold() << " gold" << endl;

            if(enemyPotions[0] != -1){
                cout << "Gained: " << potions[enemyPotions[0]].name << " ";
                if(playerNum == 1){
                    addPotion(enemyPotions[0],1);
                }else{
                    addPotion(enemyPotions[0],2);
                }
            }
            if(enemyPotions[1] != -1){
                cout << potions[enemyPotions[1]].name << endl;
                if(playerNum == 1){
                    addPotion(enemyPotions[1],1);
                }else{
                    addPotion(enemyPotions[1],2);
                }
            }else{
                cout << endl;
            }

            if(enemyEquips[0] != -1){
                cout << "Gained: " << equips[enemyEquips[0]].name << endl;
                if(playerNum == 1){
                    addEquip(enemyEquips[0],1);
                }else{
                    addEquip(enemyEquips[0],2);
                }
            }
            
            if(playerNum == 1){
                player1.setGold(player1.getGold() + enemy.getGold());
            }else{
                player2.setGold(player2.getGold() + enemy.getGold());
            }

            if(rand() % 3 == 0){
                cout << "You got an item Shop!" << endl;
                if(playerNum == 1){
                    itemShop(1);
                }else{
                    itemShop(2);
                }
            }
            
        }
        playerTurn = !playerTurn;
    }

    if(playerNum == 1){
        player1.setStamina(-(player1.getStamina()-player.getStamina()));
        player1.setHealth(-(player1.getHP()-player.getHP()));
    }else{
        player2.setStamina(-(player2.getStamina()-player.getStamina()));
        player2.setHealth(-(player2.getHP()-player.getHP()));
    }

}
//determines the potion that a player wants to use given their inventory
void Game::usePotion(int playerNum){
    int numPotions = 1;
    bool potionFound = false;
    string potionChoice;

    cout << "Potions you can use in your inventory:" << endl;

    for(int i = 0; i < 3; i++){
        if(playerNum == 1){
            if(p1Potions[i] != -1){
                cout << numPotions << " " << potions[p1Potions[i]].name << endl;
                numPotions++;
            }
        }else{
            if(p2Potions[i] != -1){
                cout << numPotions << " " << potions[p2Potions[i]].name << endl;
                numPotions++;
            }
        }
    }
    if(numPotions == 1){
        cout << "You have no potions to use" << endl;
        return;
    }else{
        
        while(potionFound == false){
            cout << "Select the potion number to use or (-1) to quit:" << endl;
            getline(cin,potionChoice);
            if(potionChoice == "-1"){
                cout << "leaving..." << endl;
                return;
            }
            for(int i = 1; i < numPotions; i++){
                if(potionChoice == to_string(i)){
                    if(playerNum == 1){
                        cout << "You used: " << potions[p1Potions[i-1]].name << endl;
                        consumePotion(1,p1Potions[i-1]);
                        p1Potions[i-1] = -1;
                    }else{
                        cout << "You used: " << potions[p2Potions[i-1]].name << endl;
                        consumePotion(2,p2Potions[i-1]);
                        p2Potions[i-1] = -1;
                    }
                    potionFound = true;
                    break;
                }
            }
            if(potionFound == false){
                cout << "Invalid selection" << endl;
            }
        }   
    }
}
//consumes the given potion that the player selects
void Game::consumePotion(int playerNum, int potNum){
    switch(potNum){
        case 0:
            if(playerNum == 1){
                player1.setHealth(10);
            }else{
                player2.setHealth(10);
            }
            break;
        case 1:
            if(playerNum == 1){
                player1.setHealth(25);
            }else{
                player2.setHealth(25);
            }
            break;
        case 2:
            if(playerNum == 1){
                player1.setStamina(10);
            }else{
                player2.setStamina(10);
            }
            break;
        case 3:
            if(playerNum == 1){
                player1.setStamina(25);
            }else{
                player2.setStamina(25);
            }
            break;
        case 4:
            if(playerNum == 1){
                if(p1Diseased || p1Poisoned){
                    cout << "Your ailments have been cured by the cleansing potion" << endl;
                }else{
                    cout << "You are neither poisoned or diseased. Cleansing potion has been used regardless." << endl;
                }
                p1Diseased = false;
                p1Poisoned = false;
            }else{
                if(p2Diseased || p2Poisoned){
                    cout << "Your ailments have been cured by the cleansing potion" << endl;
                }else{
                    cout << "You are neither poisoned or diseased. Cleansing potion has been used regardless." << endl;
                }
                p2Diseased = false;
                p2Poisoned = false;
            }

            break;
        case 5:
            if(playerNum == 1){
                player1.setStamina(25);
                player1.setHealth(25);
            }else{
                player2.setStamina(25);
                player2.setHealth(25); 
            }
            break;
        case 6:
            if(playerNum == 1){
                player1.setStamina(10);
                player1.setHealth(10);
            }else{
                player2.setStamina(10);
                player2.setHealth(10);
            }
            break;
        case 7:
            if(playerNum == 1){
                player1.setAttackBonus(2);
                
            }else{
                player2.setAttackBonus(2);
            }
            break;
        case 8:
            if(playerNum == 1){
                player1.setAttackBonus(5);
                
            }else{
                player2.setAttackBonus(5);
            }
            break;
    }
}
//swaps equiped player items with player inventory
void Game::swapEquipment(int playerNum){
    bool invalidInput = true;
    string playerInput;
    int numChoices = 0;
    int itemNums[5];
    int placeholder;
    while(invalidInput){
        cout << "Do you want to swap your weapon (1) or shield (2):" << endl;
        getline(cin,playerInput);
        if(playerInput == "1"){
            invalidInput = false;
            for(int i = 0; i < 5; i++){
                if(playerNum == 1){
                    if(p1ExcessEquips[i] != -1){
                        if(equips[p1ExcessEquips[i]].type == 'D'){
                            numChoices += 1;
                            cout << i+1 << " " << equips[p1ExcessEquips[i]].name << endl;
                            itemNums[i] = 1;
                        } 
                    }
                }else{
                    if(p2ExcessEquips[i] != -1){
                        if(equips[p2ExcessEquips[i]].type == 'D'){
                            numChoices += 1;
                            cout << i+1 << " " << equips[p2ExcessEquips[i]].name << endl;
                            itemNums[i] = 1;
                        }  
                    }
                }
            }
            if(numChoices == 0){
                cout << "You have no unequiped weapons in your inventory" << endl;
                return;
            }else{
                cout << "Select the item number from your inventory to equip" << endl;
                getline(cin,playerInput);
                for(int  i = 0; i < 5; i++){
                    if(playerInput == to_string(i+1) && itemNums[i] == 1){
                        if(playerNum == 1){
                            if(p1Equiped[0] == -1){
                                cout << "Equipping " << equips[p1ExcessEquips[i]].name << endl;
                                p1Equiped[0] = p1ExcessEquips[i];
                                p1ExcessEquips[i] = -1;
                            }
                            cout << "Swapping " << equips[p1Equiped[0]].name << " with " << equips[p1ExcessEquips[i]].name << endl;
                            placeholder = p1ExcessEquips[i];
                            p1ExcessEquips[i] = p1Equiped[0];
                            p1Equiped[0] = placeholder;
                            return;
                        }else{
                            if(p2Equiped[0] == -1){
                                cout << "Equipping " << equips[p2ExcessEquips[i]].name << endl;
                                p2Equiped[0] = p2ExcessEquips[i];
                                p2ExcessEquips[i] = -1;
                            }
                            cout << "Swapping " << equips[p2Equiped[0]].name << " with " << equips[p2ExcessEquips[i]].name << endl;
                            placeholder = p2ExcessEquips[i];
                            p2ExcessEquips[i] = p2Equiped[0];
                            p2Equiped[0] = placeholder;
                            return;
                        }
                        
                    }
                }
                cout << "Invalid Input" << endl;
                cout << "Qutting Menu..." << endl;
                return;
            }
        }else if(playerInput == "2"){
            invalidInput = false;
            for(int i = 0; i < 5; i++){
                if(playerNum == 1){
                    if(p1ExcessEquips[i] != -1){
                        if(equips[p1ExcessEquips[i]].type == 'S'){
                            numChoices += 1;
                            cout << i+1 << " " << equips[p1ExcessEquips[i]].name << endl;
                            itemNums[i] = 1;
                        } 
                    }
                }else{
                    if(p2ExcessEquips[i] != -1){
                        if(equips[p2ExcessEquips[i]].type == 'S'){
                            numChoices += 1;
                            cout << i+1 << " " << equips[p2ExcessEquips[i]].name << endl;
                            itemNums[i] = 1;
                        }  
                    }
                }
            }
            if(numChoices == 0){
                cout << "You have no unequiped shields in your inventory" << endl;
                return;
            }else{
                cout << "Select the item number from your inventory to equip" << endl;
                getline(cin,playerInput);
                for(int  i = 0; i < 5; i++){
                    if(playerInput == to_string(i+1) && itemNums[i] == 1){
                        if(playerNum == 1){
                            if(p1Equiped[1] == -1){
                                cout << "Equipping " << equips[p1ExcessEquips[i]].name << endl;
                                p1Equiped[1] = p1ExcessEquips[i];
                                p1ExcessEquips[i] = -1;
                            }
                            cout << "Swapping " << equips[p1Equiped[1]].name << " with " << equips[p1ExcessEquips[i]].name << endl;
                            placeholder = p1ExcessEquips[i];
                            p1ExcessEquips[i] = p1Equiped[1];
                            p1Equiped[0] = placeholder;
                            return;
                        }else{
                            if(p2Equiped[1] == -1){
                                cout << "Equipping " << equips[p2ExcessEquips[i]].name << endl;
                                p2Equiped[1] = p2ExcessEquips[i];
                                p2ExcessEquips[i] = -1;
                            }
                            cout << "Swapping " << equips[p2Equiped[1]].name << " with " << equips[p2ExcessEquips[i]].name << endl;
                            placeholder = p2ExcessEquips[i];
                            p2ExcessEquips[i] = p2Equiped[1];
                            p2Equiped[0] = placeholder;
                            return;
                        }
                        
                    }
                }
                cout << "Invalid Input" << endl;
                cout << "Qutting Menu..." << endl;
                return;
            }
        }
    }
    
}
//variable setter for reaching ithaca
void Game::setReachIthaca(int playerNum){
    if(playerNum == 1){
        p1AtIthaca = true;
    }else{
        p2AtIthaca = true;
    }
}
//displays end of game player stats and game winner into text file
void Game::exitFile(){
    string winner;

    if(p1Dead && p2Dead){
        winner = "Both Players Died: Draw";
    }else if(p1AtIthaca == true){
        winner = "Player 1 has won";
    }else if(p2AtIthaca == true){
        winner = "Player 2 has won";
    }else{
        winner = "Game Quit Out: Draw";
    }

    ofstream myfile;
    myfile.open ("gameover.txt");

    myfile << winner << endl;
    myfile << endl;
    myfile << "Name: " << player1.getName() << endl;
    myfile << "HP: " << player1.getHP() << endl;
    myfile << "Stamina: " << player1.getStamina() << endl;
    myfile << "Defense: " << player1.getDefense() << endl;
    myfile << "Gold: " << player1.getGold() << endl;
    myfile << "Equiped Items: ";
    for(int i = 0; i < 2; i++){
        if(p1Equiped[i] >= 0){
            myfile << equips[p1Equiped[i]].name << " ";
        }
    }
    myfile << endl;
    myfile << "Inventory Items: ";
    for(int i = 0; i < 5; i++){
        if(p1ExcessEquips[i] >= 0){
            myfile << equips[p1ExcessEquips[i]].name << " ";
        }
    }
    myfile << endl;
    myfile << "Potions: ";
    for(int i = 0; i < 3; i++){
        if(p1Potions[i] >= 0){
            myfile << potions[p1Potions[i]].name << " ";
        }
    }
    myfile << endl;

    myfile << "----------------------------" << endl;

    myfile << "Name: " << player2.getName() << endl;
    myfile << "HP: " << player2.getHP() << endl;
    myfile << "Stamina: " << player2.getStamina() << endl;
    myfile << "Defense: " << player2.getDefense() << endl;
    myfile << "Gold: " << player2.getGold() << endl;
    myfile << "Equiped Items: ";
    for(int i = 0; i < 2; i++){
        if(p2Equiped[i] >= 0){
            myfile << equips[p2Equiped[i]].name << " ";
        }
    }
    myfile << endl;
    myfile << "Inventory Items: ";
    for(int i = 0; i < 5; i++){
        if(p2ExcessEquips[i] >= 0){
            myfile << equips[p2ExcessEquips[i]].name << " ";
        }
    }
    myfile << endl;
    myfile << "Potions: ";
    for(int i = 0; i < 3; i++){
        if(p2Potions[i] >= 0){
            myfile << potions[p2Potions[i]].name << " ";
        }
    }

    myfile.close();
}
//intiated epic combat where both players attack at same time
void Game::epicCombat(){
    cout << "Epic combat initiated" << endl;
    int randEpicEnemy = rand() % 3 + 7;
    cout << "You are fighting " << enemies[randEpicEnemy].getName() << endl;
    Entity epicEnemy = enemies[randEpicEnemy];

    string SItems = epicEnemy.getSItems();
    string items[2];
    spliter(SItems,',',items,5);
    for(int i = 0; i < 2; i++){
        if(i > 0){
            items[i] = items[i].substr(1,-1);
        }
        for(int g = 0; g < 15; g++){
            if(items[i] == equips[g].name){
                addEquip(g,3);
            }
        }
        if(items[i] == "Health Potion"){
            addPotion(0,3);
        }
        if(items[i] == "Tidal Charm of the Sirens"){
            addEquip(50,3);
        }
        if(items[i] == "Maul of the Giants"){
            addEquip(60,3);
        }
        
    }
    displayPlayerStats(1);
    displayPlayerStats(2);
    displayEnemyStats(epicEnemy);
    bool playerTurn = true;
    bool attacking = true;

    int playerAttack;
    int enemyAttack;

    string playerChoice;

    if(epicEnemy.getAdvantage() == "True"){
        playerTurn = false;
        cout << "Enemy has the advantage and attacks first" << endl;
    }else{
        cout << "You can attack first" << endl;
    }

    while(attacking){
        if(playerTurn){
            if(p1Dead == false){
                cout << "Player 1's Turn" << endl;
                cout << "1. Attack" << endl;
                cout << "2. Use Potion" << endl;
                cout << "3. Swap Weapon" << endl;

                getline(cin,playerChoice);
                if(playerChoice == "1"){
                    
                    if(p1Equiped[0] == -1){
                        playerAttack = 5;
                        cout << "You attacked with your fists";
                    }else{
                        playerAttack = equips[p1Equiped[0]].effectVal;
                        if(equips[p1Equiped[0]].type == epicEnemy.getWeakness()[0]){
                            playerAttack = playerAttack * 2;
                        }
                        cout << "You attacked with " << equips[p1Equiped[0]].name;
                    }
                    
                    playerAttack = rand() % playerAttack + 1;
                    playerAttack = playerAttack * 3.5;
                    playerAttack -= epicEnemy.getDefense();

                    if(playerAttack <= 0){
                        playerAttack = 1;
                    }
                    cout << " for " << playerAttack << " damage" << endl;
                    epicEnemy.setHealth(-playerAttack);
                    cout << epicEnemy.getName() << " has " << epicEnemy.getHP() << " HP" << endl;
                }else if(playerChoice == "2"){
                    int initialHealth; 
                    int initialStam;

                    initialHealth = player1.getHP();
                    initialStam = player1.getStamina();
                    
                    usePotion(1);

                    player1.setHealth(player1.getHP() - initialHealth);
                    player1.setStamina(player1.getStamina() - initialStam);

                }else if(playerChoice == "3"){
                    swapEquipment(1);
                }else{
                    cout << "Invalid selection" << endl;
                    continue;
                }
            }

            if(p2Dead == false){
                cout << "Player 2's Turn" << endl;
                cout << "1. Attack" << endl;
                cout << "2. Use Potion" << endl;
                cout << "3. Swap Weapon" << endl;

                getline(cin,playerChoice);
                if(playerChoice == "1"){
                    
                    if(p2Equiped[0] == -1){
                        playerAttack = 5;
                        cout << "You attacked with your fists";
                    }else{
                        playerAttack = equips[p2Equiped[0]].effectVal;
                        if(equips[p2Equiped[0]].type == epicEnemy.getWeakness()[0]){
                            playerAttack = playerAttack * 2;
                        }
                        cout << "You attacked with " << equips[p2Equiped[0]].name;
                    }
                    
                    playerAttack = rand() % playerAttack + 1;
                    playerAttack = playerAttack * 3.5;
                    playerAttack -= epicEnemy.getDefense();

                    if(playerAttack <= 0){
                        playerAttack = 1;
                    }
                    cout << " for " << playerAttack << " damage" << endl;
                    epicEnemy.setHealth(-playerAttack);
                    cout << epicEnemy.getName() << " has " << epicEnemy.getHP() << " HP" << endl;
                }else if(playerChoice == "2"){
                    int initialHealth; 
                    int initialStam;

                    initialHealth = player2.getHP();
                    initialStam = player2.getStamina();
                    
                    usePotion(2);

                    player1.setHealth(player2.getHP() - initialHealth);
                    player1.setStamina(player2.getStamina() - initialStam);

                }else if(playerChoice == "3"){
                    swapEquipment(2);
                }else{
                    cout << "Invalid selection" << endl;
                    continue;
                }
            }

        }else{
            cout << "--------------------------------" << endl;
            cout << "Enemy's Turn" << endl;
            enemyAttack = equips[enemyEquips[0]].effectVal;
            cout << "Enemy attacked with " << equips[enemyEquips[0]].name;
            enemyAttack = rand() % enemyAttack + 1;
            enemyAttack -= player1.getDefense();
            enemyAttack -= player2.getDefense();

            if(enemyAttack <= 0){
                enemyAttack = 1;
            }

            enemyAttack = enemyAttack * 2.5;

            cout << " for " << enemyAttack << " damage" << endl;
            player1.setHealth(-enemyAttack);
            player2.setHealth(-enemyAttack);

            cout << player1.getName() << " has " << player1.getHP() << " HP" << endl;
            cout << player2.getName() << " has " << player2.getHP() << " HP" << endl;

            cout << "--------------------------------" << endl;
        }
        if(player1.getHP() <= 0){
            cout << "Player 1 died" << endl;
            p1Dead = true;
        }
        if(player2.getHP() <= 0){
            cout << "Player 2 died" << endl;
            p2Dead = true;
        }
        if(p1Dead && p2Dead){
            return;
        }
        if(epicEnemy.getHP() <= 0){
            attacking = false;
            cout << "You won the fight!" << endl;
            cout << "Gained: " << epicEnemy.getGold() << " gold" << endl;

            if(enemyPotions[0] != -1){
                cout << "Gained: " << potions[enemyPotions[0]].name << " ";
                addPotion(enemyPotions[0],1);
                addPotion(enemyPotions[0],2);
            }
            if(enemyPotions[1] != -1){
                cout << potions[enemyPotions[1]].name << endl;
                addPotion(enemyPotions[1],1);
                addPotion(enemyPotions[1],2);
            }else{
                cout << endl;
            }

            if(enemyEquips[0] != -1){
                cout << "Gained: " << equips[enemyEquips[0]].name << endl;
                addEquip(enemyEquips[0],1);
                addEquip(enemyEquips[0],2);
            }
            
            player1.setGold(player1.getGold() + epicEnemy.getGold());
            player2.setGold(player2.getGold() + epicEnemy.getGold());
            cout << endl;
            return;
        }
        playerTurn = !playerTurn;
    }
}

