#include <iostream>
#include <fstream>
#include "Boss.h"

using namespace std;

/**Algorithm: divide a string into seperate strings using a delimiter and populate a new array with the divisions
 * 1.Loop up the sequence one character at a time
 * 2.So long as the analyzed character isn't the delimiter, the word count of that index increases by one
 *      -keep track of the word count as well as the starting position
 * 3.Once a delimiter is hit:
 *      -define the index in the array
 *      -reset the word count and reestablish the new starting point for the next index
 * 4.Keep track of how many indeces have been defined
 * 5.If the function tries to define too many indeces for the array, return -1
 * @param: sequence, the delimiter, an array for the components of the sequence, the size of the array
 * @output: nothing
 * @return: number of defined indeces in the array
 * */

int split(string sequence, char delimiter, string array[], int size){
    
    int start = 0;      //keeps track of the beginning position of each substring
    int wordlength = 0;      //keeps track of the length of each substring
    int ind_pos = 0;      //used to define the indeces of the array
    int counter = 0;
    
    for (int i = 0 ; i < sequence.length() ; i++){
        
        string index;       //defines the index currently being looked at
        
        if (sequence[i] != delimiter){          //if the analyzed character isn't the delimiter, the word count of the index increments by 1
            wordlength++;
        }
        
        if (sequence[i] == delimiter || i == sequence.length() - 1){        //creates an index once a delimiter is hit, or the end of the sequence is hit
            
            if (sequence.substr(start, wordlength).length() != 0 && counter < size){          //the index must have a length greater than 0
                
                index = sequence.substr(start, wordlength);         //defines the array index using a substring of the first parameter
            
                start = i + 1;      //new starting point is right after the last delimiter
                wordlength = 0;     //word count reset 
            
                array[ind_pos] = index;         //defines the index into the array
                ind_pos++;          //the next index to be defines will be added to the next position in the array
            
                counter++;      //keeps track of how many positions have been filled
                
            } else {        //takes care of circumstance where two delimiters are placed back to back: make a new starting point, and reset the word count, but don't do anything to the array or indeces
                start = i + 1;
                wordlength = 0;
            }
            if (counter == size) return (-1);
        }
    }
        return counter;
}

Boss::Boss(){
    name = "";
    flavor_txt = "";
    health = 0;
    attack = 0;
    defense = 0;
    bWeapons[0] = Weapon();
    bWeapons[1] = Weapon();
}

/**Algorithm: read a text file containing all of a boss's attributes and store this data
 * 1. Open the file from the string parameter
 * 2. Get the line (only one)
 * 3. Split the line into 11 segments
 * 4. Set each of the elements accordingly
 * @param: boss file name
 * @output: nothing
 * @retrun: nothing
 * */

Boss::Boss(string bFile){
    ifstream boss_file;
    boss_file.open(bFile);
    
    if (boss_file.is_open()){
        
        string line;
        
        while (getline(boss_file,line)){
            string temp[11];    // the number of attributes to each boss is 11
            split(line, '-', temp, 11);
            
            name = temp[0];
            flavor_txt = temp[1];
            health = stoi(temp[2]);
            attack = stoi(temp[3]);
            defense = stoi(temp[4]);
            bWeapons[0] = Weapon(temp[5],stoi(temp[6]), stoi(temp[7]));
            bWeapons[1] = Weapon(temp[8], stoi(temp[9]), stoi(temp[10]));
            
        }
            
    }
}

string Boss::getBName(){
    return name;
}

string Boss::getBFT(){
    return flavor_txt;
}

int Boss::getBHP(){
    return health;
}

int Boss::getBAtk(){
    return attack;
}

int Boss::getBDef(){
    return defense;
}

// each boss has two weapons

string Boss::weapon1Name(){
    return bWeapons[0].getWName();
}

int Boss::weapon1Damage(){
    return bWeapons[0].getWDamage();
}

int Boss::weapon1Speed(){
    return bWeapons[0].getWSpeed();
}

string Boss::weapon2Name(){
    return bWeapons[1].getWName();
}

int Boss::weapon2Damage(){
    return bWeapons[1].getWDamage();
}

int Boss::weapon2Speed(){
    return bWeapons[1].getWSpeed();
}