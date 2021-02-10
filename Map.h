#ifndef MAP_H
#define MAP_H
#include <iostream>

using namespace std;

class Map{
    
    public:
        Map();
        void readMap(string);
            // a text file can be read and the map array will be populated with characters
        
        // control the movement of the character
        void moveNorth();
        void moveSouth();
        void moveEast();
        void moveWest();
        
        // boolean value that determines if the character is allowed to move in a certain direction 
        bool canMove(int);
        
        // show a small segment of the map near the character
        void displayMap();
        
        // getters and setters for the longitude and latitude of the character's position
        int getLon();
        void setLon(int);
        int getLat();
        void setLat(int);
        
        // getter and setter for the elements of the map
        string getCharacter(int, int);
        void changeCharacter(int, int, string);
        
        
            //whenever the character tries to move, this must pass as true (i.e. the place they're trying to move to is valid)
            
        
    private:
        // 2D array that holds the map
        string terrain[30][20];
        
        // track the position of the map
        int longitude;
        int latitude;
            
    
};
#endif