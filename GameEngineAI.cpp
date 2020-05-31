#include "GameEngineAI.h"
#include <fstream>
#include <iostream>

GameEngineAI::GameEngineAI(int seed):
    GameEngine::GameEngine(seed)
{
}

GameEngineAI::~GameEngineAI(){
}

void GameEngineAI::playGame(){
    if(!gameLoaded){
        gameBoard->generateTileOrder(randomSeed);
        gameBoard->fillTileBag(randomSeed);
        gameBoard->insertIntoFactory();
    }

    bool endGame = false;

        //fill up factories

        while(endGame == false){
        std::cout << HEADER1 << std::endl;    
        std::cout << "\u2ABB\u2ABB\u2ABB  ROUND START \u2ABC\u2ABC\u2ABC" << std::endl;
        std::cout << HEADER1 << "\n" << std::endl; 
        
            while(gameBoard->factoriesEmpty()==false){

                //Round start

                //Player1's turn
                
                if(player1Turn && gameBoard->factoriesEmpty()==false){

                    std::cout << "\n\u21E8 TURN FOR PLAYER: " << player1->getName() << std::endl <<std::endl;
                    player2->printPlayerBoard();
                    gameBoard->printFactory(); 
                    player1->printPlayerBoard();
                    std::string input;
                    do{
                        //do while input is invalid
                        std::cout << "> turn ";
                        std::getline(std::cin, input); 
                        if(input.find("save") == 0){
                            try{
                                input = input.substr(5);
                                saveGame(input);
                                gameLoaded = false;
                                return;
                            } catch(const std::exception& e){
                                std::cout << "Invalid save name\n";
                            }
                        }
                    }
                    while(processInput(input, gameBoard, player1)==false);
                    player1Turn = !player1Turn;
                    std::cout << std::endl;

                }

                //AI's turn
                if(!player1Turn && gameBoard->factoriesEmpty()==false){
                    
                    calculateMove(gameBoard, player2->getPlayerBoard(), player2);

                    player1Turn = !player1Turn;
                    std::cout << std::endl;   
                    
                }
                
            }
            std::cout << HEADER1 << std::endl; 
            std::cout << "\u2ABB\u2ABB\u2ABB  END OF ROUND \u2ABC\u2ABC\u2ABC" << std::endl;
            std::cout << HEADER1 << "\n" << std::endl; 
            
            //decide which player starts next round

            if(player1->firstPlayer() == true) {
                player1->setFirstPlayerMark(false);
                player1Turn = true;
            } else if(player2->firstPlayer() == true){
                player2->setFirstPlayerMark(false);
                player1Turn = false;
            }


            endRound(player1, player2);


            gameBoard->fillTileBagFromBoxLid();
            gameBoard->insertIntoFactory();

            endGame = checkEndGame(player1, player2);
        }


    std::cout << "=== END OF GAME ===" << std::endl;
        
        endGameScore(player1, player2);

        if(player1->getScore() > player2->getScore()){
        winner = player1;

        } else if (player1->getScore() < player2->getScore()) {
        winner = player2;
        }

        if( winner != nullptr){
            std::cout<< "The winner is "<< winner->getName()<< "."<<std::endl;
        } else{
            std::cout<< "It's a draw."<<std::endl;
        }

    saveGame("GameResult");
    gameLoaded = false;

}

int GameEngineAI::check1(PlayerBoard* player2Board){
    int check=-1;
    if(player2Board->checkFreeSpace(4)<5 && player2Board->checkFreeSpace(4)>0){
        std::cout<<player2Board->checkFreeSpace(4)<<std::endl;
        check=4;
    }
    else if(player2Board->checkFreeSpace(3)<4 && player2Board->checkFreeSpace(3)>0){
        check=3;
    }
    else if(player2Board->checkFreeSpace(2)<3 && player2Board->checkFreeSpace(2)>0){
        check=2;
    }
    else if(player2Board->checkFreeSpace(1)<2 && player2Board->checkFreeSpace(1)>0){
        check=1;
    }
    else if(player2Board->checkFreeSpace(0)==1 && player2Board->checkFreeSpace(0)>0){
        check=0;
    }
    return check;
}

int GameEngineAI::check2(PlayerBoard* player2Board){
    int check=-1;
    if(player2Board->checkMosaic(0)){
        check=0;
    }
    else if(player2Board->checkMosaic(1)){
        check=1;
    }
    else if(player2Board->checkMosaic(2)){
        check=2;
    }
    else if(player2Board->checkMosaic(3)){
        check=3;
    }
    else if(player2Board->checkMosaic(4)){
        check=4;
    }
    return check;
}

void GameEngineAI::calculateMove(GameBoard* gameBoard, PlayerBoard* player2Board, Player* player2){
    bool counter=false;
    do{

        if(check1(player2Board)>-1){
            std::cout<< "check  1" <<std::endl;
            if(counter==false){
                if(insertLine(gameBoard, player2Board, check1(player2Board), player2)){                
                    counter=true;                
                }
            }
        }
        if(check2(player2Board)>-1){
            if(counter==false){
                std::cout<< "check  2" <<std::endl;
                if(insertLine(gameBoard, player2Board, check2(player2Board), player2)){
                    counter=true;
                }
            }
        }
        if(counter==false){
            std::cout<< "check  3" <<std::endl;
            int countstop=0;
            char tiles[5] = {'R', 'L', 'Y', 'B', 'U'};
            //Player lines
            for(int i=0; i<5; i++){
                //Factories
                for(int j=5; j>-1; j--){
                    //Tiles
                    for(char tile : tiles){
                        if(countstop==0){
                                
                            //std::cout<< "loop PLAYER_LINE:"<< i << " FACTORY: " << j << tile <<std::endl;

                            //Checks if tile colour valid for the line
                            if(player2Board->checkLine(i,tile)==true){                                       
                                
                                int numTiles = gameBoard->checkTile(j,tile);
                                if(gameBoard->checkTile(j, tile) == player2Board->checkFreeSpace(i)){

                                    if(j==0 && gameBoard->checkCentre()==true){
                                        
                                        bool FplayerCheck=false;
                                        
                                        //Put in the tiles
                                        for(int k=0;k<numTiles;k++){
                                            if(player2Board->insertIntoLine(i, gameBoard->getBoxLid(), tile) == true){
                                                countstop=1;
                                                gameBoard->takeTile(j, tile);
                                                counter=true;
                            
                                                FplayerCheck=true;
                                                
                                                std::cout << "\n" << j << " " << tile << " " << i+1 << std::endl;
                                            } 
                                        }
                                        if(FplayerCheck){
                                            gameBoard->takeFirstMarker();
                                            player2->setFirstPlayerMark(true);
                                            player2Board->insertIntoLine(i, gameBoard->getBoxLid(), 'F');
                                            std::cout << "put in f "<<std::endl;
                                        }
                                    }
                                    else{
                                        //Put in the tiles
                                        for(int k=0;k<numTiles;k++){
                                            if(player2Board->insertIntoLine(i, gameBoard->getBoxLid(), tile) == true){
                                                countstop=1;
                                                gameBoard->takeTile(j, tile);
                                                counter=true;
                                                std::cout << "\n" << j << " " << tile << " " << i+1 << std::endl;
                                            } 
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //If no more criteria is met then random move
        //else{
        if(counter==false){
            std::cout<< "check  4" <<std::endl;
            for(int i=0; i<5; i++){
                if(counter==false){
                    if(insertLine(gameBoard, player2Board, i, player2)==true){
                        counter=true;
                    }
                }
            }
        }
        //}

    }while(counter!=true);
}

bool GameEngineAI::insertLine(GameBoard* gameBoard, PlayerBoard* player2Board, int playerLine, Player* player2){
    bool counter = false;
    int countstop=0;
    char tiles[5] = {'R', 'L', 'Y', 'B', 'U'};
    //Factories
    for(int i=5;i>-1;i--){
        //Tiles
        for(char tile : tiles){
            if(countstop==0){

                //Checks if colour valid for player line
                if(player2Board->checkLine(playerLine, tile)){

                    //Checks if tile exists in gameBoard
                    if(gameBoard->checkTile(i, tile)>-1){
                        int numTiles=gameBoard->checkTile(i,tile);
                        //If user is taking tiles from centre factory with F player marker
                        if(i==0 && gameBoard->checkCentre()==true){

                            bool FplayerCheck=false;
                                            
                            for(int j=0;j<numTiles;j++){
                                if(player2Board->insertIntoLine(playerLine, gameBoard->getBoxLid(), tile) == true){
                                    countstop=1;
                                    gameBoard->takeTile(i, tile);
                                    counter=true;       
                                    FplayerCheck=true;
                                    std::cout << "\n" << i << " " << tile << " " << playerLine+1 << std::endl;
                                }
                            }
                            if(FplayerCheck){
                                gameBoard->takeFirstMarker();
                                player2->setFirstPlayerMark(true);
                                player2Board->insertIntoLine(playerLine, gameBoard->getBoxLid(), 'F');
                            }
                        }
                        else{
                            //Put in tiles
                            for(int j=0;j<numTiles;j++){
                                if(player2Board->insertIntoLine(playerLine, gameBoard->getBoxLid(), tile) == true){
                                    countstop=1;
                                    gameBoard->takeTile(i, tile);
                                    counter=true;       
                                    std::cout << "\n" << i << " " << tile << " " << playerLine+1 << std::endl;
                                }
                            }
                        }
                    }
                }               
            }
        }
    }
    return counter;
}

void GameEngineAI::createPlayers(std::string playerName1){
    player1 = new Player(playerName1);
    player2 = new Player("[Bot] Jim");
}

