#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <list>
#include <string>
#include <random>
#include <iostream>
#include <cstdio>
#include "Types.h"
#include "LinkedList.h"

class GameBoard{
    public:
    GameBoard();
    ~GameBoard();

    //use factory number to return specific factory 0-5
    char* retrieveFactory(int factoryNumber);

    //adds tiles into factory offers from tileBag
    void insertIntoFactory();

    //generate a shuffled R,L,Y,B,U into the tileOrder string 
    void generateTileOrder(int randomSeed);

    //fills the tile bag at the beginning of the game
    void fillTileBag(int randomSeed);

    //fills up tilebag at the end of a round
    //fills tile bag with tiles from the box lid, may need to randomise tiles but uncertain as assignment spec says to only randomise tiles once
    void fillTileBagFromBoxLid();

    //prints out the factories
    void printFactory();

    //checks if factories are empty
    bool factoriesEmpty();

    //checks if factories except centre are empty
    bool factoriesEmpty2();

    //checks if given factory is empty
    bool factoryEmpty(int factoryNumber);

    //takes a tile from selected factory
    int takeTile(int factoryNumber, char tile);

    //adds something into centre factory
    void addIntoCentre(char tile);

    //checks if centre has an F
    bool checkCentre();

    //takes the first player marker away from centre factory
    void takeFirstMarker();

    //returns a box lid
    LinkedList* getBoxLid();

    //returns what is currently in the factories as a string to store in the player save
    std::string factoryOutput(int factoryIndex);

    //returns tilebag contents as a string to store in the player save
    std::string tileBagString();

    //returns boxlid contents as a string to store in the player save
    std::string boxLidString();

    //print tileBag for testing
    void printTileBag();

    //load game functions, inserts values from save game to restore previous game state
    bool loadFactory(std::string loadInput, int rowIndex);
    bool loadTileBag(std::string loadInput);
    bool loadBoxLid(std::string loadInput);


    private:
    char factory0[CENTRE_FACTORY], factory1[FACTORY_SIZE], factory2[FACTORY_SIZE], factory3[FACTORY_SIZE], factory4[FACTORY_SIZE], factory5[FACTORY_SIZE];
    char factoryTiles[FACTORY_SIZE];
    LinkedList* tileBag;
    LinkedList* boxLid;
    std::string tileOrder;
    int centreSize;

};

#endif // GAMEBOARD_H