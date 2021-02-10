#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include "Character.h"

using namespace std;

class Weapon{
    
    public:
         Weapon();
         Weapon(string,int,int);
            // initialize with name, damage, speed
         
         string getWName();
         int getWDamage();
         int getWSpeed();
    
    private:
        
        string weapon;
        int damage;
        int speed;
        
};
#endif