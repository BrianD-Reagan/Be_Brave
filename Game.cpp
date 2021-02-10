#include <iostream>
#include "Game.h"

using namespace std;

Game::Game(){
    // initialize the character
    character.setName("Nemo");
    character.setLevel();
    character.setMaxHP();
    character.setBaseAttack();
    character.setBaseDefense();
    character.setBaseMana();
    // initialize money
    geld = 0;
    // initialize beginning weapon
    weapons.push_back(Weapon());
    equipped = 0;
    // initialize the bosses from text file
    bosses[0] = Boss("kw.txt");
    bosses[1] = Boss("ha.txt");
    bosses[2] = Boss("rk.txt");
    bosses[3] = Boss("nm.txt");
    bosses[4] = Boss("fa.txt");
    // initialize map from text file
    map.readMap("Map.txt");
    // initialize skills as false at the start
    heal = false;
    fireBall = false;
    ward = false;
    song = false;
}

Game::Game(string hero_name){
    // set the character's name and stats
    character.setName(hero_name);
    character.setLevel();
    character.setMaxHP();
    character.setBaseAttack();
    character.setBaseDefense();
    character.setBaseMana();
    // initialize money
    geld = 0;
    // initialize beginning weapon
    weapons.push_back(Weapon("Sword", 5 , 2));
    equipped = 0;
    // initialize the bosses from text file
    bosses[0] = Boss("kw.txt");
    bosses[1] = Boss("ha.txt");
    bosses[2] = Boss("rk.txt");
    bosses[3] = Boss("nm.txt");
    bosses[4] = Boss("fa.txt");
    // initialize map from text file
    map.readMap("Map.txt");
    // initialize skills as false by default
    heal = false;
    fireBall = false;
    ward = false;
    song = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-character member functios

string Game::cNa(){
    return character.getName();
}

int Game::cLe(){
    return character.getLevel();
}

void Game::cLvlUp(){
    character.levelUp();
    // learn the different skills as you level up
    if (character.getLevel() == 1) heal = true;
    if (character.getLevel() == 2) fireBall = true;
    if (character.getLevel() == 3) ward = true;
    if (character.getLevel() == 4) song = true;
}

int Game::cHp(){
    return character.getMaxHP();
}

int Game::cAt(){
    return character.getBaseAttack();
}

int Game::cDe(){
    return character.getBaseDefense();
}

int Game::cMa(){
    return character.getBaseMana();
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-money member functions

int Game::getGeld(){
    return geld;
}

// find geld from fighting bosses and traveling around
void Game::addGeld(int newGeld){
    geld += newGeld;
    cout << "You now have " << geld << "G" << endl;
}

// when you buy weapons from the merchant, you loose geld
void Game::subtractGeld(int dif){
    geld -= dif;
    cout << "You now have " << geld << "G" << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-weapon member functions
// to make a new weapon, it needs a name, damage value, and speed value
void Game::addWeapon(string wName, int wDamage, int wSpeed){
    weapons.push_back(Weapon(wName,wDamage,wSpeed));
}

/**Algorithm: change the value of the equipped variable to associate with a new weapon
 * 1. Display all the weapons that the character owns
 * 2. Get an integer value from player that correlates with the new weapon the want to equip
 *      -if the value isn't correlated with a weapon in the vector, display an error and get a new value
 * 3. Change the value of the equipped variable to correlate with the weapon choice
 *      - player's input - 1
 * 4. Verify the weapon that the character is now wielding
 * @param: nothing 
 * @output: list of owned weapons, possible error, the weapon the character is now wielding
 * @return: nothing
 * */

void Game::changeEquippedWeapon(){
    
    cout << "Please select a new weapon: " << endl;
    
    // displays all of the character's owned weapons
    for (int i = 0 ; i < weapons.size() ; i++){
        cout << i + 1 << ") " << weapons[i].getWName() << endl;
    }
    
    int newE;
    cin >> newE;
    
    // the user must select a valid choice for a new weapon
    while (newE <= 0 || newE > weapons.size()){
        cout << "Invalid input! Choose agan." << endl;
        cin.clear();
        cin.ignore();
        cin >> newE;
    }
    
    equipped = newE - 1;
    
    cout << "You now wield your " << weapons[equipped].getWName() << "!" << endl;
    
}

string Game::wNa(){
    return weapons[equipped].getWName();
}

int Game::wDa(){
    return weapons[equipped].getWDamage();
}

int Game::wSp(){
    return weapons[equipped].getWSpeed();
}

int Game::getWSize(){
    return weapons.size();
}

// loop through all the weapons in the vector and display them and their stats
void Game::displayWeapons(){
    for (int i = 0 ; i < weapons.size() ; i++){
        if (i == equipped) cout << "(Equipped) ";
        cout << weapons[i].getWName() << " // " << weapons[i].getWDamage() << " Dmg // " << weapons[i].getWSpeed() << " Spd " << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-boss member functions

string Game::bNa(int index){
    return bosses[index].getBName();
}

string Game::bFt(int index){
    return bosses[index].getBFT();
}

int Game::bHp(int index){
    return bosses[index].getBHP();
}

int Game::bAt(int index){
    return bosses[index].getBAtk();
}

int Game::bDe(int index){
    return bosses[index].getBDef();
}

string Game::bw1Na(int index){
    return bosses[index].weapon1Name();
}

int Game::bw1Da(int index){
    return bosses[index].weapon1Damage();
}

int Game::bw1Sp(int index){
    return bosses[index].weapon1Speed();
}

string Game::bw2Na(int index){
    return bosses[index].weapon2Name();
}

int Game::bw2Da(int index){
    return bosses[index].weapon2Damage();
}

int Game::bw2Sp(int index){
    return bosses[index].weapon2Speed();
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-map member functions

void Game::mN(){
    map.moveNorth();
}

void Game::mS(){
    map.moveSouth();
}

void Game::mE(){
    map.moveEast();
}

void Game::mW(){
    map.moveWest();
}

// call the map member function that prints the map
void Game::printMap(){
    map.displayMap();
}

//  return the character at a latitude-longitude location
string Game::getTerrain(int lat, int lon){
    return map.getCharacter(lat,lon);
}

// change the character at a latitued-longitued location
void Game::setTerrain(int lat , int lon, string terr){
    map.changeCharacter(lat,lon,terr);
}    

// longitude value of the character
int Game::getLongitude(){
    return map.getLon();
}

// change the character's longitude value
void Game::setLongitude(int newLon){
    map.setLon(newLon);
}

// latitude value of the character
int Game::getLatitude(){
    return map.getLat();
}

// change the latitude value of the character
void Game::setLatitude(int newLat){
    map.setLat(newLat);
}

//////////////////////////////////////////////////////////////////////////////////////////
// game-skills member functions

bool Game::canHeal(){
    return heal;
}

bool Game::canFireBall(){
    return fireBall;
}

bool Game::canWard(){
    return ward;
}

bool Game::canSong(){
    return song;
}

// add up all the skills the character knows
int Game::numSkillsKnown(){
    int total = 0;
    if (canHeal()) total++;
    if (canFireBall()) total++;
    if (canWard()) total++;
    if (canSong()) total++;
    return total;
}