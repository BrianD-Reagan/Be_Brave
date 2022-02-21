#include <iostream>
#include <fstream>
#include "Map.h"

using namespace std;

Map::Map(){
    latitude = 27;
    longitude = 17;
    
}

/**Algorithm: read a file that has the map so that it can be stored in a 2D array
 * 1. Open the file and get a line
 * 2. Use my split funtion to divide the elements of each line by the space between them
 * 3. Populate the elements in the second place of the 2D array
 * 4. Move to the next row
 * @param: file name
 * @output: nothing
 * @return: nothing
 * */

void Map::readMap(string fileName){
    ifstream mapFile;
    mapFile.open(fileName);
    
    if(mapFile.is_open()){
        string line;
        int read_row = 0;
        while (getline(mapFile, line)){
            string temp[20];
            split(line, ' ', temp, 20 );
            
            for (int i = 0 ; i < 20 ; i++){
                terrain[read_row][i] = temp[i];
            }
            
            read_row++;
            
        }
    } else cout << "Did not read map!" << endl;
    mapFile.close();
}

/**Algorithm: determine if the character can move in the desired function
 * 1. Determine which direction they're trying to go
 * 2. Determine how the terrain of the map one unit in that direction
 * 3. If that place is outside the map array or is a water 'w' or mountain '^' block, return false
 * 4. Otherwise return true
 * @param: direction (1 = north, 2 = south, 3 = east, 4 = west)
 * @output: nothing
 * @return: boolean value for if an obstacle blocks their path
 * */

bool Map::canMove(int direction){
    
    switch (direction){
        
        case 1 : 
            if (latitude - 1 < 0) return false;
            if (terrain[latitude - 1][longitude] == "w" || terrain[latitude - 1][longitude] == "^" ) return false;
            return true;
        
        case 2 : 
            if (latitude + 1 > 28) return false;
            if (terrain[latitude + 1][longitude] == "w" || terrain[latitude + 1][longitude] == "^" ) return false;
            return true;
        
        case 3 : 
            if (longitude + 1 > 18) return false;
            if (terrain[latitude][longitude + 1] == "w" || terrain[latitude][longitude + 1] == "^" ) return false;
            return true;
            
        case 4 : 
            if (longitude - 1 < 0) return false;
            if (terrain[latitude][longitude - 1] == "w" || terrain[latitude][longitude - 1] == "^" ) return false;
            return true;
        default :
            return false;
        
    }
    
}


void Map::moveNorth(){
    if (canMove(1)){
        latitude--;
    } else {
        cout << "You cannot move north here!" << endl;
    }
}

void Map::moveSouth(){
    if (canMove(2)){
        latitude++;
    } else {
        cout << "You cannot move south here!" << endl;
    }
}

void Map::moveEast(){
    if (canMove(3)){
        longitude++;
    } else {
        cout << "You cannot move east here!" << endl;
    }
}

void Map::moveWest(){
    if (canMove(4)){
        longitude--;
    } else {
        cout << "You cannot move west here!" << endl;
    }
}
// displays the entire map
// void Map::displayMap(){
//     for (int i = 0 ; i < 29 ; i++){
//         for (int j = 0 ; j < 19 ; j++){
//             if (i == latitude && j == longitude){
//                 cout << "@ ";
//             } else{
//             cout << terrain[i][j] << " ";
//             }
//         }
//         cout << endl;
//     }
    
// }

/**Algorithm: display a small portion of the map that is around the character
 * 1. Determine the height of the minimap (9), and create a for loop that lasts that long and is symmetrical
 * 2. Do the same thing for the width of the minimap
 * 3. The first for loop codes longitude and the second one codes latitude
 *      -Determine if the pair of the two exists within the map array
 *      -Display the character at that position if the position exist
 * 4. If both for loops' variables equal 0, display an '@' to represent the character
 * 5. End the line after each iteration of the second loop
 * @param: nothing
 * @output: a map around the character
 * @return: nothing
 * */
void Map::displayMap(){
    cout << endl;
    for (int i = -4 ; i <= 4 ; i++){
        for (int j = -7 ; j <= 7 ; j++){
            if (latitude + i >= 0 && longitude + j >= 0 && latitude + i < 29 && longitude + j < 19){
            if (i == 0 && j == 0){
                cout << "@ ";
            }else{
                cout << terrain[latitude + i][longitude + j] << " ";
            }
            }
        }
        if (latitude + i < 29)cout << endl;
    }
    
}

// get a place on the map
string Map::getCharacter(int lat, int lon){
    return terrain[lat][lon];
}

// change a place on the map
void Map::changeCharacter(int lat, int lon, string terr){
    terrain[lat][lon] = terr;
}

// get the character's longitude
int Map::getLon(){
    return longitude;
}

// set the character's longitude
void Map::setLon(int lon){
    longitude = lon;
}

// get the character's latitude
int Map::getLat(){
    return latitude;
}

// set the character's latitude
void Map::setLat(int lat){
    latitude = lat;
}