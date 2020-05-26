#include "Player.h"

Player::Player(std::string playerName) :
    playerScore(0)
{
    this->playerName =  playerName;
    playerBoard = new PlayerBoard();
    this->firstPlayerMark = false;
}

Player::~Player(){
    delete playerBoard;
}

void Player::printPlayerBoard(){
    std::cout<<"Mosaic for "<< playerName<<std::endl;
    playerBoard->printMosaic();
    //uncomment below to see score changing along with each mosaic. For testing.
    //std::cout<<"Current Score " << getScore() <<std::endl<<std::endl;
}

std::string Player::getName(){
    return playerName;
}

void Player::setScore(){
    int score = playerBoard->getScore();
    playerScore += score;
    playerBoard->clearScore();
    }


int Player::getScore(){
    return playerScore;
}

PlayerBoard* Player::getPlayerBoard(){
    return playerBoard;
}

void Player::setFirstPlayerMark(bool set){
    firstPlayerMark=set;
}

bool Player::firstPlayer(){
    return firstPlayerMark;
}

bool Player::loadPlayerName(std::string loadInput){
    if(loadInput == ""){
        std::cout << "Player name data invalid, cancelling load.";
        return false;
    }
    playerName = loadInput;
    return true;
}

bool Player::loadPlayerScore(std::string loadInput){
    try{
        playerScore = std::stoi(loadInput);
    } catch (const std::exception& e){
        std::cout << "Player score data invalid, cancelling load.";
        return false;
    }
    return true;
}