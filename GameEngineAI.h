#ifndef GAMEENGINEAI_H
#define GAMEENGINEAI_H

#include "Types.h"
#include "Player.h"
#include "PlayerBoard.h"
#include "GameBoard.h"
#include "LinkedList.h"
#include "GameEngine.h"

class GameEngineAI: public GameEngine{
    public:
        GameEngineAI(int seed);
        GameEngineAI(GameEngineAI& other);
        virtual ~GameEngineAI();

        virtual void playGame();

        virtual void createPlayers(std::string playerName1);

        virtual void saveGame(std::string saveName);

        void calculateMove(GameBoard* gameBoard, PlayerBoard* player2Board, Player* player2);

        //checks if there're any incomplete lines
        int check1(PlayerBoard* player2Board);

        //checks if there're factory wall with completed tiles
        int check2(PlayerBoard* player2Board);

        //checks for empty lines
        int check3(PlayerBoard* player2Board, int playerLine);

        bool insertLine(GameBoard* gameBoard, PlayerBoard* player2Board, int playerLine, Player* player2);



    //private:

};

#endif //GAMEENGINEAI_H