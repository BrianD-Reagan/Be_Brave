#include <iostream>
#include "Character.h"

using namespace std;

// default everything at 0
Character::Character(){
    name = "";
    level = 0;
    maxHP = 0;
    base_attack = 0;
    base_defense = 0;
    base_mana = 0;
}

// most of the setter functions here only apply to when the game is initialized, as they are normally changed by leveling up

string Character::getName(){
    return name;
}

void Character::setName(string name){
    this->name = name;
}

int Character::getLevel(){
    return level;
}

void Character::setLevel(){
    level = 0;
}

// change the character's stats whenever they level up
void Character::levelUp(){
    level++;
    maxHP += 10;
    base_attack += 6;
    base_defense += 6;
    base_mana += 7;
    
    cout << "LEVEL UP!" << endl;
}

int Character::getMaxHP(){
    return maxHP;
}

void Character::setMaxHP(){
    maxHP = 35;
}

int Character::getBaseAttack(){
    return base_attack;
}

void Character::setBaseAttack(){
    base_attack = 45;
}

int Character::getBaseDefense(){
    return base_defense;
}

void Character::setBaseDefense(){
    base_defense = 45;
}

int Character::getBaseMana(){
    return base_mana;
}

void Character::setBaseMana(){
    base_mana = 25;
}