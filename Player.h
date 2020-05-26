#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include "PlayerBoard.h"

class Player{
    public:
        Player(std::string playerName);
        ~Player();
        int getScore();
        void setScore();
        PlayerBoard* getPlayerBoard();
        std::string getName();
        void printPlayerBoard();
        void setFirstPlayerMark(bool set);
        bool firstPlayer();

        //loads data from save into player variables
        bool loadPlayerName(std::string loadInput);
        bool loadPlayerScore(std::string loadInput);

    private:
        PlayerBoard* playerBoard;
        int playerScore;
        std::string playerName;
        bool firstPlayerMark;
};

#endif // PLAYER_H