#include <iostream>
#include <fstream>
#include <ctime>
#include "Game.h"

using namespace std;

void displayStats(Game game){
    cout << game.cNa() << " // "; 
    cout << "Lvl: " << game.cLe() << " // "; 
    cout << "HP: " << game.cHp() << " // "; 
    cout << "Atk: " << game.cAt() << " // "; 
    cout << "Def: " << game.cDe() << " // "; 
    cout << "Mana: " << game.cMa() << endl;
}

void printWanderMenu(){         // need to add quit feature
    cout << "...Wandering..." << endl;
    cout << "1. Move" << endl;
    cout << "2. View Inventory" << endl;
    cout << "3. Change Weapon" << endl;
    cout << "4. Show Stats" << endl;
    cout << "5. Abandon your quest." << endl;
}

void printMovements(){
    cout <<"Where to move?" << endl;
    cout << "1. North // ";
    cout << "2. South // ";
    cout << "3. East // " ;
    cout << "4. West" << endl;
}

/**Algorithm: print out a list of things the player carries with them
 * 1. Print how much geld they have
 * 2. Display their weapons
 * 3. Tell them each skill they know 
 * @param: game object
 * @output: geld, weapons, and known skills
 * @reutrn: nothing
 * */

void printInventory(Game &game){
    cout << "...Inventory..." << endl;
    cout << "Geld: " << game.getGeld() << endl;
    game.displayWeapons();
    if (game.canHeal() == false) {
        cout << "You currently don't know any skills." << endl;
    } else{
        cout << "Known skills:" << endl;
        cout << "Heal: Recover some of your health during battle." << endl;
    }
    if (game.canFireBall()) cout << "Fireball: Create a great immolating bolt that deals massive damage and ignores enemy defenses." << endl;
    if (game.canWard()) cout << "Ward: Coat yourself in a protective barrier that strengthens your defenses, but fades over time." << endl;
    if (game.canSong()) cout << "Song of Despair: Use your flute to play a melody that has the chance to permanently sunder your opponents attack and defense." << endl;
}

/**Algorithm: when a character moves, give them a random chance to find a small amount of geld
 * 1. Get a random number between 1 and 10
 * 2. If that random number is 4 (10%), then they found money
 *      -get a random number between 1 and 4, and add that number to their ammount of geld
 * @param: game object
 * @output: if they found geld, tell them how much
 * @return: nothing
 * */

void testLuck(Game &game){
    srand(time(0));
    int l = rand() % 10;
    if (l == 4){
        int a = rand() % 4 + 1;
        cout << "You found " << a << "G in your travels." << endl;
        game.addGeld(a);
    }
}

/**Algorithm: randomly determine with a 50% chance of either way if a character will succesfully flee a battle
 * 1. Get a random number between 1 and 10
 * 2. If the number is above 5, they flee (true)
 *      -otherwise, they don't (false)
 * @param: nothing
 * @output: nothing
 * @return: true if they flee (>5), false if they don't (<= 5)
 * */

bool flee(){
    srand(time(0));
    int chance = rand() % 10 + 1;
    if (chance > 5){
        return true;
    } else {
        return false;
    }
}

/**Algorithm: determine how much health the character will recoveer from using heal
 * 1. Get a random number between 1 and 8
 * 2. Add this random value to 3 times the character's level and 6 and return this sum
 * @param: game obeject
 * @output: nothing
 * @return: random healing value
 * */

int heal(Game game){
    srand(time(0));
    int random_healing = rand() % 8 + 1;
    return 6 + (2 * game.cLe()) + random_healing;
}

/**Algorithm: determine how much damage the character deals with fire ball given their attack rating
 * 1. Divide the character's attack rating by 5.
 * 2. Get random number between 1 and 12
 * 3. Add the new divided attack rating and the random integer and return this 
 * @param: character's attack
 * @output: nothing
 * @return: fire ball damage
 * */

int fireBall(int attack){
    srand(time(0));
    attack = attack / 5;
    int random_damage = rand() % 12 + 1;
    return attack + random_damage;
}

/**Determine if the character's attempt to use the skill "Song of Despair" is effective.
 * 1. Get random number between 1 and 10
 * 2. If the number is less than 6 (60% chance), return true
 *      -otherwise return false
 * @param: nothing
 * @output: nothing
 * @return: boolean with 60% chance true, 40% chance false
 * */

bool song(){
    srand(time(0));
    int chance = rand() % 10 + 1;
    if (chance <= 6){
        return true;
    } else {
        return false;
    }    
    
}

/**Algorithm: take a weapon's damage and speed values, and a being's attack rating and return a random amount of damage done
 * 1. Get a randon number in the range from 1 to the damage integer
 *      -add togeter each random number
 *      -get this random number for a number of cycles equal to the speed of the weapon
 * 2. Add together the bonus damage dealt from the being's attack rating
 *      -divdie their attack rating by 5 and subtract that by 5
 *      -add this bonus to the original sum
 * 3. Returh the sum
 * @param: weapon damage, weapon speed, and character attack rating
 * @output: nothing
 * @return: random damage done
 * */

int useWeapon(int damage, int speed, int attack){
    srand(time(0));
    int total = 0;
    
    for (int i = 0 ; i < speed ; i++){
        int r = rand() % damage + 1;
        total += r;
    }
    
    int bonus = attack / 5 - 5;
    total += bonus;
    
    return total;
    
}

/**Algorithm: take a damage value and something's defense value and apply how the defense reduces the damage
 * 1. Divide the defense value by 10 to get the integer that the damage dealth will be reduced by
 * 2. Subtract this integer from the damage and return the damage
 * @param: defense value and damage value
 * @output: nothing
 * @return: reduced damage value as integer
 * */

int takeDamage(int defense, int damage){
    int def = defense / 10;
    damage -= def;
    return damage;
}

/**Algorithm: have the player fight against a boss character
 * 1. Initialize with text and copy over the character's and the boss's stats to new variables for ease
 * 2. Enter an infinite while loop
 * 3. Display the stats of each
 *      -if the player has cast ward, display the character's stacks of protection
 *      -if the player has successfuly cast song of despain, display that the boss is debuffed
 * 4. Enter the player's turn
 *      -If the character has any stacks of protection, decrement the stack by 1 and decrement their defenses by 20
 *      -Display the player's choices: attack, use skill, or flee
 * 5. If attack, run the use weapon function with the equipped weapon's damage and speed value, run the return against the take damage function for the boss and apply the return to the boss's health
 * 6. If use a skill, ask them which skill to use
 *      -if the player knows no skills yet, their turn is forfeited. remove 8 mana
 *      -if heal, run heal function and apply the return value to the player's health
 *      -if fire ball, run fireball function and apply the damage return value to the boss's health regardless of their defenses. remove 13 mana
 *      -if ward, check to make sure they aren't already protected. if not, apply 3 stacks and increment defenses by 60. remove 16 mana
 *      -if song of despair, run song function. if passed, decrement the boss's attack and defenses by 20. remove 24 mana. if failed. don't change stats and remove 10 mana
 * 7. If flee run the flee function. if passed, the player flees, returning -1. if not, procees to boss's turn
 * 8. Check if the boss is at or below 0 health, if so return 1, otherwise continue
 * 8. Boss's turn
 *      -flip a coin to determine the weapon they'll use, run this weapon by the use weapon function, run that return by player's take damage function and apply the return to their health
 * 9. Check if the player's health is below or at 0, if so return 0, else, loop to player's turn
 * 10. Repeat until something's dead or the player flees
 * @param: game object and the index value of the boss we're fighting
 * @output: stats, options, outcomes
 * @return: -1 if flee, 0 if killed, 1 if triumphant
 * */

int battle(Game &game, int b){
    cout << endl;
    cout << "Fate chooses you, hero!" << endl;
    cout << endl;
    cout << game.bNa(b) << ", " << game.bFt(b) << " " << "challenges your bravery!" << endl;
    
    int player_health = game.cHp();
    int player_attack = game.cAt();
    int player_defense = game.cDe();
    int player_mana = game.cMa();
    int protect = 0;
    
    int boss_health = game.bHp(b);
    int boss_attack = game.bAt(b);
    int boss_defense = game.bDe(b);
    bool despaired = false;
    
    while(true){

        if (protect > 0){
            if (protect == 1){
                player_defense -= 60;
                cout << "Your barrier fades away." << endl;
                protect--;
            } else{
                protect--;
                cout << "Your barrier fades..." << endl;
            }
        }
        
        cout << endl;
        cout << game.cNa() << " // HP: " << player_health << " // Atk: " << player_attack << " // Def: " << player_defense << " // Mana: " << player_mana << " ";
            if (protect > 0) cout << "Protected";
            cout << endl;
        cout << game.bNa(b) << " // HP: " << boss_health << " // Atk: " << boss_attack << " // Def: " << boss_defense << " ";
            if (despaired == true) cout << "Despaired";
            cout << endl;
        cout << endl;
        
        // character's turn
        cout << "Your turn..." << endl;
        cout << endl;
        
        cout << "What is your action?" << endl;
        cout << "1. Attack with your " << game.wNa() << "." << endl;
        cout << "2. Use a skill." << endl;
        if (game.canHeal() == false) cout << "     Warning: trying to use a skill when you don't know one will forfeit your turn!" << endl;
        cout << "3. Flee from the fight." << endl;
        
        int action;
        cin >> action;
            while(action < 1 || action > 3){
                cout << "Invalid action choice!" << endl;
                cin.clear();
                cin.ignore();
                cin >> action;
            }
        
        switch(action){
            case 1 :        // attack with your equipped weapon
            {
                int damage = useWeapon(game.wDa(), game.wSp(), player_attack);
                int taken = takeDamage(boss_defense, damage);
                
                boss_health -= taken;
                
                cout << endl;
                cout << "You dealt " << taken << " damage to " << game.bNa(b) << " with your " << game.wNa() << "!" << endl;
                break;
            }    
            case 2 :        // cast a skill
            {
                int skill;
                if (game.canHeal() == false){
                    cout << "You don't know any skills." << endl;
                    break;
                } else {
                    if (game.canHeal()) cout << "1) Cast heal (8 mana)" << endl;
                    if (game.canFireBall()) cout << "2) Cast fireball! (13 mana)" << endl;
                    if (game.canWard()) cout << "3) Create ward! (19 mana)" << endl;
                    if (game.canSong()) cout << "4) Cast song of despair! (24 mana)" << endl;
                
                cin >> skill;
                
                while (skill < 1 || skill > game.numSkillsKnown()){
                    cout << "Invalid skill selection!" << endl;
                    cin.clear();
                    cin.ignore();
                    cin >> skill;
                }
                }
                
                switch (skill){
                    case 1 :        // heal
                    {
                        if (player_mana < 8){
                            cout << "You don't have enough mana to cast Heal!" << endl;
                        } else {
                            cout << endl;
                            int health_addition = heal(game);
                            player_health += health_addition;
                            if (player_health > game.cHp()) player_health = game.cHp();
                        
                            cout << "A bright, yellow light glows from your heart!" << endl;
                            cout << "You healed " << health_addition << " hit points for 8 mana!" << endl;
                            player_mana -= 8;
                        }
                        
                        break;
                    }
                    case 2 :        //fireball
                    {
                        if (player_mana < 13){
                            cout << "You don't have enough mana to cast Fireball!" << endl;
                        }else{
                            cout << endl;
                            int fire_damage = fireBall(player_attack);
                            boss_health -= fire_damage;
                            player_mana -= 13;
                            cout << "An infernal bolt erupts forth from your hand!" << endl;
                            cout << game.bNa(b) << " suffered " << fire_damage << " damage from your flame!" << endl;
                            cout << "Fireball used 13 mana!" << endl;
                        }
                        
                        break;
                    }
                    case 3 :
                    {
                        if (player_mana < 19){
                            cout << "You don't have enough mana to cast Ward!" << endl;
                        } else if(protect > 0) {
                            cout << "You are already protected by Ward!" << endl;
                        } else {
                            cout << endl;
                            player_defense = player_defense + 60;
                            player_mana -= 16;
                            cout << "A shimmering barrier envelops the space around you, protecting you from damage!" << endl;
                            cout << "Ward used 19 mana!" << endl;
                            protect = 4;
                        }
                        
                        break;
                    }
                    case 4 : 
                    {
                        if (player_mana < 24){
                            cout << "You don't have enough mana to cast Song of Despair!" << endl;
                        } else if (despaired == true){
                            cout << game.bNa(b) << " is already despaired!" << endl;
                        } else {
                            cout << endl;
                            cout << "You pull out your flute and try to charm " << game.bNa(b) << " with a song!" << endl;
                            bool despair = song();
                            if (despair == true){
                                cout << "Your song resonates through the battlefield and sunders " << game.bNa(b) << "!" << endl;
                                boss_attack -= 20;
                                boss_defense -= 20;
                                despaired = true;
                                player_mana -= 24;
                                cout << "Song of Despair used 24 mana!";
                            } else {
                                cout << "Your song fails to enchant " << game.bNa(b) << endl;
                                player_mana -= 10;
                                cout << "You lost 10 mana!" << endl;
                            }
                        }
                        cout << endl;
                        
                        break;
                    }
                    
                }
            }
            
            break;
            
            case 3 :        // flee from battle
            {
                bool coward = flee();
                if (coward == true) {
                    cout << "You run from the battle. Both you and " << game.bNa(b) << " recover completley." << endl;
                    if (game.bNa(b) == "Reksis" || game.bNa(b) == "The Nightmare Savath'ul") {
                        game.mN();
                    } else {
                        game.mS();
                    }
                    return -1;
                } else {
                    cout << "You failed to flee, the battle continues!" << endl;
                }
            }
        }
        
        if (boss_health <= 0) return 1;
        
        // boss's turn
        
        cout << endl;
        cout << "The enemy's turn..." << endl;
        cout << endl;
        srand(time(0));
        int enemy_attack = rand() % 2;
        
        int dmg;
        
        if (enemy_attack == 0){
            cout << game.bNa(b) << " attacks you with " << game.bw1Na(b) << "!" << endl;
            dmg = useWeapon(game.bw1Da(b), game.bw1Sp(b), boss_attack);
        } else {
            cout << game.bNa(b) << " uses " << game.bw2Na(b) << "!" << endl;
            dmg = useWeapon(game.bw2Da(b), game.bw2Sp(b), boss_attack);
        }
        
        int tkn = takeDamage(player_defense, dmg);
        if (tkn < 0) tkn = 0;
        player_health -= tkn;
        
        cout << "You took " << tkn << " damage!" << endl;
        
        if (player_health <= 0) return 0;
        
    }
}

/**Algorithm: allow the character to buy weapons from a wandering merchant
 * 1. Display the merchant's offers, and ask if the player like to buy anything
 * 2. If they decline, exit the function
 * 3. If they accept, ask what they'd like to buy and get an input
 *      -if the input is invalid, display an error
 * 4. Check if the player has enough money
 *      -if not, tell them so
 *      -if they do, add the weapon to the vector
 * 5. Bid them farewell and move them north
 * @param: game object
 * @output: the merchant's options
 * @return: nothing
 * */

void merchant(Game &game){
    cout << endl;
    cout << "A wandering merchant offers you goods, if you have the geld." << endl;
    cout << endl;
        cout << "You have " << game.getGeld() << "G" << endl;
        cout << "1) 15G Daggers // 3 Damage // 4 Speed" << endl;
        cout << "2) 30G Mace // 4 Damage // 3 Speed" << endl;
        cout << "3) 45G Pike // 4 Damage // 4 Speed" << endl;
        cout << "4) 60G War Hammer // 6 Damage // 3 Speed" << endl;
        cout << endl;
    
    cout << "Would you like to purchase a weapon?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    
    int agree;
        cin.clear();
        cin.ignore();
        cin >> agree;
        
        while (agree < 1 || agree > 2){
            cout << "The merchant scoffs..." << endl;
            cin.clear();
            cin.ignore();
            cin >> agree;
        }
    switch (agree){
        case 1 :
        {
            int selection;
            cout << "What do you wish to buy?" << endl;
            cin.clear();
            cin.ignore();
            cin >> selection;
                while (selection < 1 || selection > 4){
                    cout << "The merchant scoffs..." << endl;
                    cin.clear();
                    cin.ignore();
                    cin >> selection;
                }
            switch(selection){
                case 1 :
                {
                    if (game.getGeld() >= 15){
                        cout << "You now own Daggers!" << endl;
                        game.addWeapon("Daggers", 3, 4);
                        game.subtractGeld(15);
                    } else {
                        cout << "You do not have enough geld for Daggers!" << endl;
                    }
                    break;
                }
                case 2 : 
                {
                    if (game.getGeld() >= 30){
                        cout << "You now own a Mace!" << endl;
                        game.addWeapon("Mace",4,3);
                        game.subtractGeld(30);
                    } else{
                        cout << "You do not have enough geld for a Mace!" << endl;
                    }
                    break;
                }
                case 3 :
                {
                    if (game.getGeld() >= 45){
                        cout << "You now own a Pike!" << endl;
                        game.addWeapon("Pike",4,4);
                        game.subtractGeld(45);
                    } else{
                        cout << "You do not have enough geld for a Pike!" << endl;
                    }
                    break;
                }
                case 4 :
                {
                    if (game.getGeld() >= 60){
                        cout << "You now own a War Hammer!" << endl;
                        game.addWeapon("War Hammer",6,3);
                        game.subtractGeld(60);
                    } else{
                        cout << "You do not have enough geld for a War Hammer!" << endl;
                    }
                    break;
                } 
            }
        }   
        case 2 :
            break;
    }
    cout << "The merchant bids you farewell." << endl;
    game.mN();
        
}

/**Algorithm: check to see if there's anything important happening at the player's location i.e bosses or merchant
 * 1. Determine if the character is at precent important locations on the map
 * 2. If they're at the merchant, run the merchant function
 * 3. If they're at a boss location, determine if they've defeated it before: "!" = they have not, "X" = they have 
 *      -if they haven't battle if the player is at a high enough level for the fight
 *          -if the player wins the battle, change the character of the terrain to a "X" and display winning text, give them geld, level up, and move them to a safe location
 *          -if the player loses, display losing text and teleport them to the beginning of the map
 * @param: game object
 * @output: story text 
 * @return: nothing
 * */

void checkPosition(Game &game){

    int pos[2] = {game.getLatitude(), game.getLongitude()};
    
    if (pos[0] == 25 && pos[1] == 5){
        merchant(game);
    }
    
    // the postion for Kinder Wallace, the first boss
    if (pos[0] == 22 && pos[1] == 14 && game.getTerrain(22,14) == "!"){
        int fight = -1;
        // must be at least level 0
        if (game.cLe() >= 0){
            cout << endl;
            cout << "You come across an abandoned fort based against the mountains. Spiderwebs cloak the walls in silk tapestries. This place has been empty for a long time." << endl;
            cout << "You turn to leave, but beneath the gate where you entered now stands a tall ranger donning sword and shield. He lifts his blade, and points it straight at you." << endl;
            
            fight = battle(game, 0);
        } else {
            cout << "You're destiny is not here yet, hero." << endl;
            game.mS();
        }
        
        if (fight == 1){
            cout << endl;
            cout << "Kinder Wallace falls before your might, hero. Having felled the champion of the past, you may continue on your quest." << endl;
            cout << "On the champion's body, you see a small scroll sticking out from one of his side pockets." << endl;
            cout << "You look at it, and see scribbled together a small assortment of witness statements and accounts collected by the ranger about a heinous shadow lurking in the west." << endl;
            cout << "Perhaps it is worth investigating..." << endl;
            cout << endl;
            game.cLvlUp();
            cout << "You've learned Heal! Use magic during a fight to restore your lost health." << endl;
            game.setTerrain(22,14,"X");
            game.addGeld(13);
            game.mS();
            return;
        } else if(fight == 0){
            cout << "Kinder Wallace is a mighty fighter known far and wide. You injuries are yoo great, and you pass out from exhaustion." << endl;
            cout << "You wake and find yourself on the outskirts of the village, just as you were when your quest began." << endl;
            cout << "Nevertheless, your bravery persists, and you continue along your quest." << endl;
            game.setLatitude(27);
            game.setLongitude(17);
            return;
        }
        
    }
    
    if (pos[0] == 20 && pos[1] == 1 && game.getTerrain(20,1) == "!"){
        int fight = -1;
        if (game.cLe() >= 1){
            cout << "Your travels bring you to a long forgotten farmland What was once a lush field of crops and plants is now nothing but soft mounds of dirt." << endl;
            cout << "As you tread forward, you begin to hear voices coming from all sides." << endl;
            cout << "Suddenly, a ghoulish, skeletal figure erupts from the ground before you, and their eyes lock with yours..." << endl;
            
            fight = battle(game, 1);
        } else {
            cout << "You're destiny is not here yet, hero." << endl;
            game.mS();
        }
        
        if (fight == 1){
            cout << endl;
            cout << "Your final blow finishes off the hateful phantom, and it slowly dissipates into a fading fog." << endl;
            cout << "Among a pile of Hänis's stolen plunder, you see a knight's shield, but it's been warped and mishapen by some sort of flame." << endl;
            cout << "There's only one kind of fire that could have humbled such a weapon in the midst of batle. A dragon lurks in your path, hero." << endl;
            cout << endl;
            game.cLvlUp();
            cout << "You've learned Fireball! Cast forth a firey ball of destruction during battle to deal damage which ignores the enemy's defenses." << endl;
            game.setTerrain(20,1,"X");
            game.addGeld(19);
            game.mS();
            return;
        } else if(fight == 0){
            cout << "Hänis proves too great a threat for you; all you can remember is your vision fading to black as you succumbed to his supernatural might." << endl;
            cout << "You wake and find yourself on the outskirts of the village, just as you were when your quest began." << endl;
            cout << "Nevertheless, your bravery persists, and you continue along your quest." << endl;
            game.setLatitude(27);
            game.setLongitude(17);
            return;
        }
        
    }
    
    if (pos[0] == 12 && pos[1] == 12 && game.getTerrain(12,12) == "!"){
        int fight = -1;
        if (game.cLe() >= 2){
            cout << "You enter a cave at the base of a mountain. A rotting smell curses your senses, but you continue onward nevertheless. Mountains of gold and bones rise high along" << endl;
            cout << "the cavern walls. A thundering voice bellows from the cave, 'THIEF!', and the large central pile before you erupts into a gleaming shower of gold coins," << endl;
            cout << "behind which is a dragon..." << endl;
            
            fight = battle(game, 2);
        } else {
            cout << "You're destiny is not here yet, hero." << endl;
            game.mW();
        }
        
        if (fight == 1){
            cout << endl;
            cout << "The earth aches in a terrible rattle as the dragon crashes to the ground. To kill a dragon is no small task, hero, your bravery is truly song worthy." << endl;
            cout << "Looking around the Reksis's cavern fortress, you notice a small pile of statues of men, women and children all in a frightened panic, as if they're trying to run from something." << endl;
            cout << "Upon investigating, you learn that one statue was not completley stone, and a sickly man grabs for you with a look of terror in his eyes." << endl;
            cout << "He cries, 'It's not dead! It's not dead! It's not dead!' before coiling himself back up and fading into silence." << endl;
            cout << "These people were human once, you realize, and it wasn't the dragon that doomed them to stone. Something far worse lies ahead..." << endl;
            cout << endl;
            game.cLvlUp();
            cout << "You've learned Ward! Create a barrier around yourself which dampens the damage dealt by the enemy." << endl;
            game.setTerrain(12,12,"X");
            game.addGeld(23);
            game.mW();
            return;
        } else if(fight == 0){
            cout << "Reksis expells your threat from his cave, and you pass out from the exhaustion of the battle." << endl;
            cout << "You wake and find yourself on the outskirts of the village, just as you were when your quest began." << endl;
            cout << "Nevertheless, your bravery persists, and you continue along your quest." << endl;
            game.setLatitude(27);
            game.setLongitude(17);
            return;
        }
        
    }
    
    if (pos[0] == 5 && pos[1] == 7 && game.getTerrain(5,7) == "!"){
        int fight = -1;
        if (game.cLe() >= 3){
            cout << "You come across a lavish port city against the coast. The pompous, beautiful architecture tells you that this was at one point a gleaming city, but " << endl;
            cout << "now it lies empty. You find the city center that overlooks a shimmering sunset, and just as you begin to relax, your gut sinks. You watch the shadows around" << endl;
            cout << "you move against light to coalesce into the form of a terrible horned demon. It shrieks an awful cry, and turns its eyes to you..." << endl;
            
            fight = battle(game, 3);
        } else {
            cout << "You're destiny is not here yet, hero." << endl;
            game.mE();
        }
        
        if (fight == 1){
            cout << endl;
            cout << "The shadows shriek a terrible cry as you deal the killing blow to Savath'ul. The nightmate boils away, and the shade which gave it form returns to its proper place hiding from sunlight. " << endl;
            cout << "Looking around, though, you still see a hollow town filled with empty buildings and forgotten bones. This place will always remember what happened; even long after people return." << endl;
            cout << "You wonder why this place was left at the mercy of the nightmare, so you investigate the city barracks. There, you discover a note from the king ordering a retreat back to the castle to the north" << endl;
            cout << "Perhaps it's now time you pay that castle a visit." << endl;
            cout << endl;
            game.cLvlUp();
            cout << "You've learned Song of Despair! Charm your opponent with your flute, permanetly sundering their attack and defense." << endl;
            game.setTerrain(5,7,"X");
            game.addGeld(26);
            game.mE();
            return;
        } else if(fight == 0){
            cout << "The shrieking cries of the nightmare drain you of your energy until your consciousness eventually fades away." << endl;
            cout << "You wake and find yourself on the outskirts of the village, just as you were when your quest began." << endl;
            cout << "Nevertheless, your bravery persists, and you continue along your quest." << endl;
            game.setLatitude(27);
            game.setLongitude(17);
            return;
        }
        
    }
    
    if (pos[0] == 1 && pos[1] == 16 && game.getTerrain(1,16) == "!"){
        int fight = -1;
        if (game.cLe() >= 4){
            cout << "The drawbridge to the northern castle layed open, and you entered the castle grounds without a fuss. The courtyard tells the tale of a place that's been forgotten " << endl;
            cout << "and left to collect dust. You push open the large door to the throne room, where you gawk in horror at the sight hundreds of bodies lieing cold the floor. Sounds of a wimpering " << endl;
            cout << "cry pull your eyes to the throne, where a king sits sobbing into bloody hands. He wipes away his tears and returns eye contact. 'I had no choice', he mumbles before " << endl;
            cout << "grabbing for his sword, and standing to face you..." << endl;
            
            fight = battle(game, 4);
        } else {
            cout << "You're destiny is not here yet, hero." << endl;
            game.mS();
        }
        
        if (fight == 1){
            cout << endl;
            game.setTerrain(1,16,"X");
            game.cLvlUp();
            return;
        } else if(fight == 0){
            cout << "You, too, are subject to Flavian's divinity, hero. The battle is too much for you, and you pass out from exhaustion." << endl;
            cout << "You wake and find yourself on the outskirts of the village, just as you were when your quest began." << endl;
            cout << "Nevertheless, your bravery persists, and you continue along your quest." << endl;
            game.setLatitude(27);
            game.setLongitude(17);
            return;
        }
        
    }
}

/**Algorithm: display the minimap to the player and print a list of their options, get their choice for these options and proceed accordingly
 * 1. Within an infinite loop, print the minimap and the menu for wandering
 * 2. Get a choice from the player
 *      -display an error if the choice is invalid
 * 3. Split the choices in a switch case
 * 4. Continue this loop forever until they quit, or they kill the final boss
 * @param: the game object
 * @output: menus, possible errors
 * @return: 0 if they quit, 1 if they win
 * */

int wander(Game &game){
    while (true){
        game.printMap();
        printWanderMenu();
        
        int choice;
            cin >> choice;
            
        while (choice <= 0 || choice > 5){
            cout << "Invalid input! Choose agan." << endl;
            cin.clear();
            cin.ignore();
            cin >> choice;
        }
        
        switch (choice){
            case 1 :
            /**Display a menu of the movemets
             * Get a choice from the user
             *      if the choice is invalid, print an error while the input is invald
             * Move in the desired direction
             * After the character has moved, run the test luck function
             * */
            {
                printMovements();
                
                int movement;
                cin.clear();
                cin.ignore();
                cin >> movement;
            
                while (choice <= 0 || choice > 4){
                cout << "Invalid input! Choose agan." << endl;
                cin.clear();
                cin.ignore();
                cin >> movement;
                }
                
                switch(movement){
                    case 1 :
                        game.mN();
                        testLuck(game);
                        break;
                    case 2 :
                        game.mS();
                        testLuck(game);
                        break;
                    case 3 :
                        game.mE();
                        testLuck(game);
                        break;
                    case 4 :
                        game.mW();
                        testLuck(game);
                        break;
                    default :
                        cout << "Invalid direction!" << endl;
                        cin.clear();
                        cin.ignore();
                }
                break;
            }
            
            case 2 :        // print the contents of the character's inventory
                cout << endl;
                printInventory(game);
                break;
            case 3 :        // change the character's equiped weapon
                cout << endl;
                game.changeEquippedWeapon();
                break;
            case 4 :        // display the character's stats
                cout << endl;
                displayStats(game);
                break;
            case 5 :
                
                /**The player opts to quit
                 * Verify that they want to quit
                 * Their choice must be valid, otherwise print an error 
                 * If they do opt to quit, return 0 to main 
                 * */
            
                cout << endl;
                cout << "Are you sure you wish to abandon your quest, hero?" << endl;
                cout << "1. No, I must continue." << endl;
                cout << "2. Yes, I cannot go further." << endl;
                
                int quit;
                cin.clear();
                cin.ignore();
                cin >> quit;
            
                while (quit <= 0 || quit > 2){
                    cout << "You must make up your mind, hero." << endl;
                    cin.clear();
                    cin.ignore();
                    cin >> quit;
                }
                
                if (quit == 1) {
                    cout << "Then continue, hero!" << endl;
                    break;
                } else{
                    return 0;
                }
                
        }
        
        checkPosition(game);        // this checks if there is anything of note at the character's placement
            if (game.getTerrain(1,16) == "X") return 1;     // if the Flavian Arturo, the final boss, has been killed, return 1 to main
    }
}

/**Algorithm: save the player's notable stats to a file
 * 1. Open the file "heroes.txt" with the intent to append rather than overwrite
 * 2. Save the character's name and level
 * 3. Save the name of each boss the hero has killed by checking to see if the boss's map character has been replaced with "X"
 * */

void quit(Game game){
    fstream save;
    save.open("heroes.txt", fstream::app);
    
    if (save.is_open()){
        save << game.cNa() << " Lvl: " << game.cLe() << " ; ";
        if (game.getTerrain(22,14) == "X"){
            save << "Enemies vanquished: Kinder Wallace, History's Champion";
        }
        if (game.getTerrain(20,1) == "X") save << " // Hänis, A Hateful Phantom";
        if (game.getTerrain(12,12) == "X") save << " // Reksis, The Dragon of the Mountain";
        if (game.getTerrain(5,7) == "X") save << " // The Nightmare Savath'ul, Fear Given Form";
        if (game.getTerrain(1,16) == "X") save << " // Flavian Arturo, The Forgotten King";
        
        save << endl;
        save.close();
        
    } else {
        return;
    }
}

/**Algorithm: display the contents of the file containing the past heroes
 * 1. Open the file "heroes.txt"
 * 2. Display the contents of each line
 * */

void displayHeroes(){
    ifstream heroes;
    heroes.open("heroes.txt");
    
    if (heroes.is_open()){
        
        cout << "The remembered: " << endl;
        string line;
        while (getline(heroes, line)){
            cout << line << endl;
        }
        heroes.close();
        return;
    } else {
        return;
    }
    
}

int main(){
    
    cout << "~~~BE BRAVE~~~" << endl;
    cout << endl;
    cout << "What is your hero's name?" << endl;
        string hero_name_start;
        getline(cin,hero_name_start);
        
        // initialize the game object with the entered name
        Game game(hero_name_start);
        
        // beginning story text
        cout << endl;
        cout << "Tales of monsters and cruel men have haunted the dreams of children all throughout history. Beasts with teeth that could cut through metal. Men who wander the wilds looking"<< endl;
        cout << " only to pillage the weak. But here, these tales curse the land with an awful truth. You've lived your whole life in a small town beneath mountains, hiding from this along with" << endl;
        cout << " everyone you've ever known. Recently, though, thing's have begun to change. The air feels heavier with darkness and the sky cloaks the land in dread. Rumors come to light that" << endl;
        cout << " the terrible shadows are growing stronger than ever, and their hunger turns their eyes to the village. With the people's hope left shattered and beaten, plans are set in motion" << endl;
        cout << " to evacuate the land and abandon their lives here. But a feeling in you tells you that this is not right. These terrors will not cease until someone decides to face against them." << endl;
        cout << " But who would take on such a dangerous task? Who would dare face the shadows as a warrior if the light? And that's when a little spark of fire ignites deep within your chest, and" << endl;
        cout << " you know that it must be you who stands for the people when all hope seems lost. And so, as your friends around you prepare to give up on this land, you don armour and sword and take" << endl;
        cout << " off to the west on a quest to fight back against these terrors."<< endl;
        cout << endl;
        cout << "Be brave, hero." << endl;
        cout << endl;
        
        // wander starts interactive component of the game
        int outcome = wander(game);
        
        // if wander returns 0, the player quit early
        if (outcome == 0){
            if (game.getTerrain(22,14) == "!") {        // if Kinder Wallace is still alive, don't save their data
                cout << "You turn your back to your quest, and the valley of the village falls to the darkness." << endl;
                cout << "History has forgoten you." << endl;
                return 0;
            } else {        // otherwise, save their stats and display the contents of this save file
                cout << endl;
                cout << "You turn your back to your quest, and the valley of the village falls to the darkness." << endl;
                cout << "But worry not, hero, your mark has been made." << endl;
                cout << endl;
                quit(game);
                displayHeroes();
                return 0;
            }
            
        }
        
        // if wander returns 1, the player defeated Flavian Arturo
        // finish the story, save and display the past heroes
        if (outcome == 1){
            cout << "Flavian Arturo collapses to his knees and lets out one last longing cry before his wounds take him. As the forgotten king takes his last breaths, you notice the light inside you" << endl;
            cout << " burning brighter than ever. Your bravery has become one to contest the will of monsters and kings. You step out just past the drawbridge and look out over the land. The terrors of" << endl;
            cout << " the land have been ushered away from the village. The people there may now have the will to laugh and dance and sing once again. A hero like you comes only once in a thousand years." << endl;
            cout << endl;
            cout << "History remembers you, hero." << endl;
            cout << endl;
            quit(game);
            displayHeroes();
            return 0;
        }
}