#ifndef BOSS_H
#define BOSS_H
#include <iostream>

using namespace std;

class Boss{
    
    public:
        Boss();
        Boss(string);
        // Boss(string, string, int, int, int);
        
        string getBName();
        string getBFT();
        int getBHP();
        int getBAtk();
        int getBDef();
        
        // first weapon
        string weapon1Name();
        int weapon1Damage();
        int weapon1Speed();
        
        // second weapon
        string weapon2Name();
        int weapon2Damage();
        int weapon2Speed();
    
    private:
    //bosses have much of the same rating types as the character
        string name;
        string flavor_txt;
        int health;
        int attack;
        int defense;
        Weapon bWeapons[2];
};
#endif