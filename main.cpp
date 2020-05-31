#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "PlayerBoard.h"
#include "Player.h"
#include "GameBoard.h"
#include "GameEngine.h"
#include "GameEngineAI.h"

//for processing file input
class Args{   
public:
  std::string operation;

};

void printHelp();
void printMenu();
void showCredits();
void azulGame(GameEngine* engine);
void singlePlayer(GameEngineAI* engine);
bool loadGame(GameEngine* engine1, GameEngine* engine2);


int main(int argc, char** argv){
    std::string userInput;
    int randomSeed = 0;
    
    std::cout << std::endl;
    std::cout << 
    MAINHEADER <<
    "WELCOME TO " << AZUL <<
    MAINHEADER; 

    for(int i = 0; i < argc; i++){
        if(std::string(argv[i]) == "-s"){
            if(i + 1 < argc){
                i++;
                try{
                    randomSeed = std::stoi(argv[i]);
                } catch (const std::exception& e) {
                    std::cout << "Random seed invalid.\n";
                    randomSeed = 0;
                }
                std::cout << "Random seed set as: " << randomSeed << std::endl;

            }
        }
    }

    while (userInput != "5" ){

        GameEngine* engine = new GameEngine(randomSeed);
        GameEngineAI* engine2 = new GameEngineAI(randomSeed);

        printMenu();

        
        std::getline(std::cin, userInput);
   
        if (userInput == "1") {
            azulGame(engine);

        } 
        
        else if(userInput == "2"){
            singlePlayer(engine2);
        }

        else if (userInput == "3") {
            loadGame(engine, engine2);

        } else if (userInput == "4") {
            showCredits();

        } else if (userInput == "5") {
            std::cout<<"Thanks for playing"<<std::endl;

        } 
          else if(userInput == "help"){
            printHelp();
        }
          else {
          std::cout<<"Invalid Input"<<std::endl;
          userInput = "0";
        }
    }
    return EXIT_SUCCESS;
}

bool loadGame(GameEngine* engine1, GameEngine* engine2){
    bool retVal = false;

    std::string saveName = {};
    std::cout << "Please enter the name of your save game (not including .txt): \n";
    //std::cin.ignore(100000, '\n');
    std::getline(std::cin, saveName);
    std::ifstream saveFile(saveName + ".txt");

    if(!saveFile){
        std::cout << "Save file does not exist. Returning to main menu.\n";
        retVal=false;
    }

    std::string parseInput = {}; 

    std::getline(saveFile, parseInput, '\n');
    
    std::cout << parseInput << std::endl;

    if(parseInput == "Multi"){
        engine1->loadGame(saveName);
        engine1->playGame();
    }
    else if(parseInput == "AI"){
        engine2->loadGame(saveName);
        engine2->playGame();
    }
    else{
        std::cout << "Invalid save file" << std::endl;
    }
    return retVal;
}

void singlePlayer(GameEngineAI* engine){
    //std::cin.ignore(100000, '\n');
    std::string playerName1;
    std::cout << "Enter a name for Player I" << std::endl << ">";
    std::getline(std::cin, playerName1);

    std::cout << std::endl << "LET'S PLAY! \n\n" << std::endl << std::endl;

    engine->createPlayers(playerName1);
    //std::cin.ignore(100000, '\n');
    engine->playGame();
}

void printHelp(){
    std::cout << "\n" << LIGHTBLUE << HELPSECTIONUP <<  
    "\n Welcome! Azul is a simple yet fun board game where \n" <<
    " you'd need take coloured tiles form given factory \n" <<
    " into your own board. Winner is the first to complete \n" <<
    " a single line in their mosaic horizontally! \n" <<
    " You can input 'help' in-game to ask for help \n" <<
    " Press 1 to start a new game. \n" <<
     HELPSECTIONDOWN << RESET <<
    std::endl;
}
void printMenu(){
    std::cout << 
    "\nMenu \n" <<
    "---- \n" <<
    "1 " << MENUDOT << " New Game (Multi Player) \n" <<
    "2 " << MENUDOT << " New Game (Single Player) \n" <<
    "3 " << MENUDOT << " Load Game \n" <<
    "4 " << MENUDOT << " Credits (Show student information) \n" <<
    "5 " << MENUDOT << " Quit \n \n";
}

void azulGame(GameEngine* engine){

    //std::cin.ignore(100000, '\n');
    std::string playerName1, playerName2;
    std::cout << "Enter a name for Player I" << std::endl << ">";
    std::getline(std::cin, playerName1);
    std::cout << "Enter a name for Player II" << std::endl << ">";
    std::getline(std::cin, playerName2);

    std::cout << std::endl << "LET'S PLAY! \n\n" << std::endl << std::endl;

    engine->createPlayers(playerName1, playerName2);
    //std::cin.ignore(100000, '\n');
    engine->playGame();
}

void showCredits(){
    std::cout << 
    "---------------------------------- \n" <<
    "Name: Cass Ilangantileke \n" <<
    "Student ID: s3742928\n" <<
    "Email: S3742928@student.rmit.edu.au\n";

    std::cout << 
    "\nName: Julian Tjiong \n" <<
    "Student ID: S3786866 \n" <<
    "Email: S3786866@student.rmit.edu.au \n";

    std::cout << 
    "\nName: Matthew Andric \n" <<
    "Student ID: S3506698   \n" <<
    "Email: S3506698@student.rmit.edu.au\n" <<
    "----------------------------------\n\n";
}