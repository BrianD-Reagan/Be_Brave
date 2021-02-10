#include <iostream>
#include "Weapons.h"

using namespace std;

// default weapon if hands
Weapon::Weapon(){
    weapon = "Fists";
    damage = 2;
    speed = 4;
}

Weapon::Weapon(string name, int damage, int speed){
    weapon = name;
    this->damage = damage;
    this->speed = speed;
}

// get name
string Weapon::getWName(){
    return weapon;
}

// get damage value
int Weapon::getWDamage(){
    return damage;
}

// get speed value
int Weapon::getWSpeed(){
    return speed;
}