//Project 2
//James Rossano

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//equipment, potion, and riddle structs
struct Potion{
    string name;
    string desc;
    int effectVal;
    int price;
};

struct Equipment{
    string name;
    string desc;
    char type;
    char element;
    int effectVal;
    int price;
};

struct Riddle{
    string text;
    string answer;
};

class Entity{
    private:
        //entity (player/enemy) stats
        string name;
        char type;
        int health;
        int stamina;
        int defense;
        char condition;
        string advantage;
        string weakness;
        int gold; 
        string sItems; 
        string nItems; 
        string ultimate;
        int attackBonus = 0;
    
    public:
        //name|type|health|stamina|defense|condition|advantage|weakness|gold|starting items|number of items|ultimate
        //main intial entity setter
        void setCharacter(string, char, int, int, int, char, string, string, int, string, string, string);

        //entity getters
        string getName();
        char getType();
        int getHP();
        int getStamina();
        int getDefense();
        char getCondition();
        string getAdvantage();
        string getWeakness();
        int getGold();
        string getSItems();
        string getNItems();
        string getUltimate();
        int getAttackBonus();
        
        //entity setters
        void setHealth(int);
        void setStamina(int);
        void setAttackBonus(int);
        void setGold(int);
};

#endif