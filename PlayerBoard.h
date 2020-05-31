#ifndef PLAYERBOARD_H
#define PLAYERBOARD_H
#include <vector>
#include <list>
#include <iostream>
#include <string>

#include "Types.h"
#include "LinkedList.h"

class PlayerBoard{

  public:
    //creating char/vectors for the players wall
    PlayerBoard();
    ~PlayerBoard();

    //will move tiles from the factory lines into the wall, passing through boxLid to add extra tiles into the lid
    void insertIntoWall(LinkedList* boxLid);

    //specifies the line to move the tiles into out of the players lines, adds extra tiles to the boxLid
    bool insertIntoLine(int mosaicLineNumber, LinkedList* boxLid, char factoryTiles);

    //overloaded function for when pulling from discard tiles as opposed to factory offers
    //void insertIntoLine(int factoryLineNumber, LinkedList* boxLid, std::list<char> discardTiles);

    //checks if a wall line contains the given tile
    bool checkWall(int wallLine, char tile);

    //checks if a line contains the given tile
    bool checkLine(int line, char tile);

    //checks how much free space in a line
    int checkFreeSpace(int line);

    //return a char that exists in a line
    char tileInLine(int line);

    //check mosaic has an uppercase
    bool checkMosaic(int line);

    //function to print current status of player board
    void printMosaic();

    //helps print a line of the wall for the mosaic
    void printWall(int x);

    //helps find tile to replace in wall
    void findTile(char x, int wall);

    //checks newly added tile in factory wall and sets score accordingly
    void calculateScore(int row, int col);

    //checks if given tile is empty or not
    bool empty(char x);

    //retrieve score
    int getScore();

    //convert player mosaic into string for save game file
    std::string playerMosaicString(int rowIndex);

    //convert player lines into string for save game file
    std::string playerLineString(int rowIndex);

    //convert broken tiles to a string for the save game file
    std::string brokenTileString();

    //sets score to zero
    void clearScore();

    //checks for a horizontal line thats full, used to check for endgame.
    bool checkEnd();

    //calculates end of game scoring
    void endScoring();
    void colorScoring(char tile);
    
    //functions for loading data from a save file to restore game state
    bool loadMosaicLines(std::string loadInput, int rowIndex);
    bool loadFactoryWall(std::string loadInput, int rowIndex);
    bool loadBrokenTiles(std::string loadInput);

  private:
    char r;
    char e;
    char y;
    char b;
    char l;
    char u;
    
    int score;
    std::vector<std::vector<char>> mosaicLines;
    char factoryWall[5][5];
    char broken[7];
    
};
  



#endif //PLAYERBOARD_H