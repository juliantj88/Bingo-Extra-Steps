#include "GameEngine.h"
#include <fstream>
#include <iostream>

GameEngine::GameEngine(int seed){
    winner = nullptr;
    gameBoard = new GameBoard();
    player1 = new Player("Player 1");
    player2 = new Player("Player 2");
    player1Turn = true;
    randomSeed = seed;
    gameLoaded = false;
}

GameEngine::~GameEngine(){
    delete winner;
    delete gameBoard;
}

void GameEngine::createPlayers(std::string playerName1, std::string playerName2){
    player1 = new Player(playerName1);
    player2 = new Player(playerName2);
}

void GameEngine::playGame(){
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

                //Player2's turn
                if(!player1Turn && gameBoard->factoriesEmpty()==false){

                    std::cout << "\n\u21E8 TURN FOR PLAYER: " << player2->getName() << std::endl << std::endl;
                    player1->printPlayerBoard();
                    gameBoard->printFactory();
                    player2->printPlayerBoard();
                    std::string input2;
                
                    do{
                        //do while input is invalid
                        std::cout << "> turn ";
                        std::getline(std::cin, input2); 
                        if(input2.find("save") == 0){
                            try{
                                input2 = input2.substr(5);
                                saveGame(input2);
                                gameLoaded = false;
                                return;
                            } catch(const std::exception& e){
                                std::cout << "Invalid save name\n";
                            }
                        }
                    }
                    while(processInput(input2, gameBoard, player2)==false);
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

bool GameEngine::processInput(std::string input, GameBoard* gameBoard, Player* player){
    bool check=false;
    if(checkInput(input, gameBoard, player)){
        //breaking down the string into int, char, int
        int factory = (int)input[0]-'0';
        char tile = char(input[2]);
        int line = 0;
        if(input[4]!='B'){
        line = (int)input[4]-'0';
        } else {
            line = 6;
        }

        
        //checks if colour exists in the line
        if(player->getPlayerBoard()->checkLine(line-1, tile)==true){

            //if the selected tile exists in the factory, remove same color tiles from factory
            //int numTiles = gameBoard->takeTile(factory, tile);
            int numTiles = gameBoard->checkTile(factory, tile);
            if(numTiles>0){
                //If user is taking tiles from centre factory with F player marker
                if(factory==0 && gameBoard->checkCentre()==true){
                    player->getPlayerBoard()->insertIntoLine(line-1, gameBoard->getBoxLid(), 'F');
                    for(int x=0;x<numTiles;x++){
                        if(player->getPlayerBoard()->insertIntoLine(line-1, gameBoard->getBoxLid(), tile)==true){
                            check=true;
                            
                            gameBoard->takeTile(factory,tile);

                            gameBoard->takeFirstMarker();
                            player->setFirstPlayerMark(true);
                        }
                        else{
                            check=false;
                            std::cout << "Tile exists in wall" << std::endl;
                        }
                    }
                }   
                //If centre factory doesn't have an F
                else{ 
                    for(int x=0;x<numTiles;x++){
                        if(player->getPlayerBoard()->insertIntoLine(line-1, gameBoard->getBoxLid(), tile)==true){
                            check=true;

                            gameBoard->takeTile(factory,tile);
                        }
                        else{
                            check=false;
                            std::cout << "Tile exists in wall" << std::endl;
                        }
                    }
                }
            }
            else{
                std::cout << "Tile not found" << std::endl;
                check=false;
            }
        }
        else{
            check=false;
        } 
    }
    else if(input=="help"){
        processHelp(gameBoard, player);
        check=false;
    }
    else{
        check=false;
    }
    if(check==false && input!="help"){
        std::cout << "Invalid Input" << std::endl;
        return false;
    }
    else if(input=="help"){
        return false;
    }
    else{
        return true;
    }
}

void GameEngine::processHelp(GameBoard* gameBoard, Player* player){
    if(gameBoard->factoriesEmpty2()){
        if(gameBoard->checkCentre()){
            help2();
        }
        else{
            help3();
        }
    }
    else if(!gameBoard->checkCentre()){
        help4();
    }
    else{
        help1();
    }
}

void GameEngine::help1(){
    std::cout << "\n" << RED << HELPBLOCK <<
    "\n Choose a factory number (e.g. 1), a tile colour (e.g Y) \n" <<
    " Select a line in your mozaic (e.g. 1) \n" <<
    " Your final input must be like: >turn 1 Y 1 \n" <<
    " [Warning: Drawing from centre factory now will get you \n" <<
    " the first player marker] \n\n" << RESET;
}

void GameEngine::help2(){
    std::cout << "\n" << RED << HELPBLOCK <<
    "\n You'll have to draw from the centre factory now! \n" <<
    " The first player marker (F) will go into your broken \n" <<
    " tiles.  \n\n" << RESET;
}

void GameEngine::help3(){
    std::cout << "\n" << RED << HELPBLOCK <<
    "\n You'll have to draw from the centre factory now! \n\n" << RESET;
}

void GameEngine::help4(){
    std::cout << "\n" << RED << HELPBLOCK <<
    "\n Choose a factory number (e.g. 1), a tile colour (e.g Y) \n" <<
    " Select a line in your mozaic (e.g. 1) \n" <<
    " Your final input must be like: >turn 1 Y 1 \n" << RESET;
}


bool GameEngine::checkInput(std::string input, GameBoard* gameBoard, Player* player){
    //check if input string is valid (1-5, RYBLUF, and 1-5)
    if(input[0]=='0' || input[0]=='1' || input[0]=='2' || input[0]=='3' || input[0]=='4' || input[0]=='5'){
        if(input[1]==' ' && input[3]==' '){
            if(input[2]=='R' || input[2]=='Y' || input[2]=='B' || input[2]=='L' || input[2]=='U'){
                if(input[4]=='0' || input[4]=='1' || input[4]=='2' || input[4]=='3' || input[4]=='4' || input[4]=='5'|| input[4]=='B'){
                    return true;
                } else{
                    return false;
                }
            } else{
                return false;
            }
        } else{
            return false;
        }
    } else{
        return false;
    }
}

bool GameEngine::checkEndGame(Player* player1, Player* player2){
    bool retValue = false;
    
    if(player1->getPlayerBoard()->checkEnd() || player2->getPlayerBoard()->checkEnd()){
        retValue = true;
    }

    return retValue;
}

void GameEngine::endRound(Player* player1, Player* player2){

            player1->getPlayerBoard()->insertIntoWall(gameBoard->getBoxLid());
            player2->getPlayerBoard()->insertIntoWall(gameBoard->getBoxLid());
            std::cout<<std::endl;
            player1->printPlayerBoard();
            std::cout << "Score for player " << player1->getName()<< " during previous round: ";
            std::cout << player1->getPlayerBoard()->getScore()<<std::endl;
            player1->setScore();
            std::cout << "Total Score for player " << player1->getName()<< " : ";
            std::cout << player1->getScore()<<std::endl<<std::endl;
            player2->printPlayerBoard();
            std::cout << "Score for player " << player2->getName()<< " during previous round: ";
            std::cout << player2->getPlayerBoard()->getScore()<<std::endl;
            player2->setScore();
            std::cout << "Total Score for player " << player2->getName()<< " : ";
            std::cout << player2->getScore()<<std::endl<<std::endl;

}

void GameEngine::endGameScore(Player* player1, Player* player2) {

            player1->getPlayerBoard()->endScoring();
            player2->getPlayerBoard()->endScoring();
            std::cout<<std::endl;
            player1->printPlayerBoard();
            std::cout << "Score for player " << player1->getName()<< " after end of game scoring: ";
            std::cout << player1->getPlayerBoard()->getScore()<<std::endl;
            player1->setScore();
            std::cout << "Total Score for player " << player1->getName()<< " : ";
            std::cout << player1->getScore()<<std::endl<<std::endl;
            player2->printPlayerBoard();
            std::cout << "Score for player " << player2->getName()<< " after end of game scoring: ";
            std::cout << player2->getPlayerBoard()->getScore()<<std::endl;
            player2->setScore();
            std::cout << "Total Score for player " << player2->getName()<< " : ";
            std::cout << player2->getScore()<<std::endl<<std::endl;

}



bool GameEngine::returnPlayerTurn(){
    return player1Turn;
}

int GameEngine::returnRandomSeed(){
    return randomSeed;
}

bool GameEngine::loadPlayerTurn(std::string loadInput){
    int testInput;
    try{
        testInput = std::stoi(loadInput);
    } catch (const std::exception& e) {
        std::cout << "Player turn data invalid, cancelling load.";
        return false;
    }

    if( testInput == 0 || testInput == 1){
        player1Turn = testInput;
        return true;
    }

    std::cout << "Player turn data invalid, cancelling load.";
    return false;
}

bool GameEngine::loadRandomSeed(std::string loadInput){
    try{
        randomSeed = std::stoi(loadInput);
    } catch (const std::exception& e) {
        std::cout << "Random seed data invalid, cancelling load.";
        return false;
    }
    
    return true;
}

void GameEngine::saveGame(std::string saveName){
    
    std::ofstream saveFile;
    saveFile.open(saveName + ".txt");
    
    saveFile << player1->getName() << "\n" << player2->getName() << "\n" << player1->getScore() << "\n" << player2->getScore() << "\n" << player1Turn << "\n";

    for(int i = 0; i <= 5 ; i++){
        saveFile << gameBoard->factoryOutput(i) << "\n";        
    }

    PlayerBoard* player1Board = player1->getPlayerBoard();
    PlayerBoard* player2Board = player2->getPlayerBoard();

    for(int i = 0; i < 5; i++){
        saveFile << player1Board->playerMosaicString(i) << "\n";
    }
    for(int i = 0; i < 5; i++){
        saveFile << player2Board->playerMosaicString(i) << "\n";
    }

    for(int i = 0; i < 5; i++){
        saveFile << player1Board->playerLineString(i) << "\n";
    }
    for(int i = 0; i < 5; i++){
        saveFile << player2Board->playerLineString(i) << "\n";
    }

    saveFile << player1Board->brokenTileString() << "\n";
    saveFile << player2Board->brokenTileString() << "\n";

    saveFile << gameBoard->boxLidString() << "\n";

    saveFile << gameBoard->tileBagString() << "\n";

    saveFile << randomSeed;

    std::cout << "Game saved to " << saveName << ".txt\n";
}

bool GameEngine::loadGame(){
    std::string saveName = {};
    std::cout << "Please enter the name of your save game (not including .txt): \n";
    std::cin.ignore(100000, '\n');
    std::getline(std::cin, saveName);
    std::ifstream saveFile(saveName + ".txt");

    if(!saveFile){
        std::cout << "Save file does not exist. Returning to main menu.\n";
        return false;
    }

    std::string parseInput = {};

    std::getline(saveFile, parseInput, '\n');
    if(!player1->loadPlayerName(parseInput)){ return false; }
    std::getline(saveFile, parseInput, '\n');
    if(!player2->loadPlayerName(parseInput)){ return false; }

    std::getline(saveFile, parseInput, '\n');
    if(!player1->loadPlayerScore(parseInput)){ return false; }    
    std::getline(saveFile, parseInput, '\n');
    if(!player2->loadPlayerScore(parseInput)){ return false; } 

    std::getline(saveFile, parseInput, '\n');
    if(!loadPlayerTurn(parseInput)){ return false; }
    

    for(int i = 0; i <= 5; i++){
        std::getline(saveFile, parseInput, '\n');
        if(!gameBoard->loadFactory(parseInput, i)){ return false; }
    }

    PlayerBoard* loadBoard = new PlayerBoard();

    loadBoard = player1->getPlayerBoard();
    for(int i = 0; i < 5; i++){
        std::getline(saveFile, parseInput, '\n');
        if(!loadBoard->loadFactoryWall(parseInput, i)){ return false; }
    }
    loadBoard = player2->getPlayerBoard();
    for(int i = 0; i < 5; i++){
        std::getline(saveFile, parseInput, '\n');
        if(!loadBoard->loadFactoryWall(parseInput, i)){ return false; }
    }

    loadBoard = player1->getPlayerBoard(); 
    for(int i = 0; i < 5; i++){
        std::getline(saveFile, parseInput, '\n');
        if(!loadBoard->loadMosaicLines(parseInput, i)){ return false; }
    }
    loadBoard = player2->getPlayerBoard(); 
    for(int i = 0; i < 5; i++){
        std::getline(saveFile, parseInput, '\n');
        if(!loadBoard->loadMosaicLines(parseInput, i)){ return false; }
    }

    loadBoard = player1->getPlayerBoard();
    std::getline(saveFile, parseInput, '\n');
    if(!loadBoard->loadBrokenTiles(parseInput)){ return false; }

    loadBoard = player2->getPlayerBoard();
    std::getline(saveFile, parseInput, '\n');
    if(!loadBoard->loadBrokenTiles(parseInput)){ return false; }

    std::getline(saveFile, parseInput, '\n');
    if(!gameBoard->loadBoxLid(parseInput)){ return false; }
    std::getline(saveFile, parseInput, '\n');
    if(!gameBoard->loadTileBag(parseInput)){ return false; }

    std::getline(saveFile, parseInput, '\n');
    if(!loadRandomSeed(parseInput)){ return false; }

    gameLoaded = true;
    return true;
}