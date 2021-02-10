#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Character.h"
#include "Weapons.h"
#include "Boss.h"
#include "Map.h"
#include <vector>

using namespace std;

class Game{
  
    public:
        Game();
        // take the hero's name to initialize the game object
        Game(string);
        
        // getters for all the character information
        string cNa(); // name
        int cLe(); // level
        int cHp(); // health
        int cAt(); // attack
        int cDe(); // defense
        int cMa(); // mana
        
        // level up the character
        void cLvlUp();
        
        // getters and setters for geld
        int getGeld();
        void addGeld(int);
        void subtractGeld(int);
        
        // add weapons to the vector and change the equipped weapon
        void addWeapon(string, int, int); // weapon name, damage value, speed value
        void changeEquippedWeapon(); // change the value of 'equipped' to a new index for the weapons vector
        // getters for the equipped weapon
        string wNa();
        int wDa();
        int wSp();
        // get the size of the weapons vector
        int getWSize();
        // display the weapons and their stats
        void displayWeapons();
        
        // getters for bosses, parameter is the index for the boss array
        string bNa(int); // name
        string bFt(int); // flavor text
        int bHp(int); // health
        int bAt(int); // attack
        int bDe(int); // defense
        string bw1Na(int); // name of first weapon
        int bw1Da(int); // damage value of first weaopn
        int bw1Sp(int); // speed value of first weapon
        string bw2Na(int); // name of second weapon
        int bw2Da(int); // damage value of second weapon
        int bw2Sp(int); // speed value of second weapon
        
        // map member functions
        void mN(); // move north
        void mS(); // move south
        void mE(); // move east 
        void mW(); // move west
        void printMap(); // prints a 15x5 map centered on the character's position
        int getLongitude(); // get east-west location of the character
        void setLongitude(int); // set the character's east-west location
        int getLatitude(); // get north-south location of the character
        void setLatitude(int); // set the character's north-south location
        string getTerrain(int, int); // get the character in the map array at a coordinate location
        void setTerrain(int, int, string); // change the character in the map array at a coordinate location
        
        //skills
        bool canHeal(); // learn heal at level one
        bool canFireBall(); // learn fireball at level two
        bool canWard(); // learn ward at level three
        bool canSong(); // learn song of despair at level four
        int numSkillsKnown(); // how many skills does the character know
        
    private:
        Character character;
        
        // geld is the money of the world
        int geld;
        
        vector <Weapon> weapons;
        // for battles, equipped tracks the weapon in the vector that the character is wielding
        int equipped;
        
        // 5 bosses have their stats read from text files
        Boss bosses[5];
        
        Map map;
        
        // tracks if the character has learned the skill yet
        bool heal; 
        bool fireBall;
        bool ward;
        bool song;
    
};
#endif