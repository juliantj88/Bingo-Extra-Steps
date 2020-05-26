#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Types.h"
#include "Player.h"
#include "PlayerBoard.h"
#include "GameBoard.h"
#include "LinkedList.h"

class GameEngine{
    public:
    GameEngine(int seed);
    ~GameEngine();

    //The gameplay method
    void playGame();

    //Returns the number of colors found in the factory
    bool processInput(std::string input, GameBoard* gameBoard, Player* player);
    
    bool intoMozaic(std::string input, Player* player, int sameColorTiles);

    bool checkInput(std::string input, GameBoard* gameBoard, Player* player);

    //creates player to store into game engine
    void createPlayers(std::string playerName1, std::string playerName2);

    //help message 1
    void help1();

    //Returns a winner
    Player* getWinner();

    //end of round processing
    void endRound(Player* player1, Player* player2);

    //end of game processing
    void endGameScore(Player* player1, Player* player2);

    //returns values for save game functionality
    bool returnPlayerTurn();
    int returnRandomSeed();

    //functions for restoring game from save file
    bool loadPlayerTurn(std::string loadInput);
    bool loadRandomSeed(std::string loadInput);

    //save/load game functionality
    void saveGame(std::string saveName);
    bool loadGame();

    //checks if game ended
    bool checkEndGame(Player* player1, Player* player2);



    private:
    GameBoard* gameBoard;
    Player* winner;
    LinkedList* tileBag;
    Player* player1;
    Player* player2;
    int randomSeed;
    bool player1Turn;
    bool gameLoaded;

};

#endif //GAMEENGINE_H