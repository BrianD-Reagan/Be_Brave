#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>

using namespace std;

class Character{
    
    public:
        Character();
        
        string getName();
        
        int getLevel();
        void levelUp();
        
        // get the character's stats
        int getMaxHP();
        int getBaseAttack();
        int getBaseDefense();
        int getBaseMana();
        
        // used to initialize
        void setName(string);
        void setLevel();
        void setMaxHP();
        void setBaseAttack();
        void setBaseDefense();
        void setBaseMana();
    
    private:
        // about the character
        string name;
        // leveling stats
        int level;
        // battle stats:
        int maxHP;
        int base_attack;
        int base_defense;
        int base_mana;
    
};
#endif