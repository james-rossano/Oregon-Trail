//Project 2
//James Rossano

#include "Entity.h"

//character/enemy setter
void Entity::setCharacter(string _name, char _type, int _health, int _stamina, int _defense, char _condition, string _advantage, string _weakness, int _gold, string _sItems, string _nItems, string _ultimate){
    name = _name;
    type = _type;
    health = _health;
    stamina = _stamina;
    defense = _defense;
    condition = _condition;
    advantage = _advantage;
    weakness = _weakness;
    gold = _gold; 
    sItems = _sItems; 
    nItems = _nItems; 
    ultimate = _ultimate;
}

//entity getters
string Entity::getName(){
    return name;
}
char Entity::getType(){
    return type;
}
int Entity::getHP(){
    return health;
}
int Entity::getStamina(){
    return stamina;
}
int Entity::getDefense(){
    return defense;
}
char Entity::getCondition(){
    return condition;
}
string Entity::getAdvantage(){
    return advantage;
}
string Entity::getWeakness(){
    return weakness;
}
int Entity::getGold(){
    return gold;
}
string Entity::getSItems(){
    return sItems;
}
string Entity::getNItems(){
    return nItems;
}
string Entity::getUltimate(){
    return ultimate;
}

//updates character's gold
void Entity::setGold(int amount){
    gold = amount;
}

//updates character's health (chose to allow characters to have more than 100 health)
void Entity::setHealth(int amount){
    health += amount;
    if(health <= 0){
        health = 0;
    }
}
//updates character's stamina (chose to allow characters to have more than 100 stamina)
void Entity::setStamina(int amount){
    stamina += amount;
    if(stamina <= 0){
        stamina = 0;
    }
}
//return attack bonus if character gets damage buff from hidden treasure
int Entity::getAttackBonus(){
    return attackBonus;
}
//updates character attack bonus
void Entity::setAttackBonus(int amount){
    attackBonus += amount;
}