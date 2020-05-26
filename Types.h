#ifndef TYPES_H
#define TYPES_H

typedef char* DefaultTiles[5];
typedef char* Red;
typedef char* Yellow;
typedef char* DBlue;
typedef char* LBlue;
typedef char* Black;
typedef char* FPlayer;
typedef char* Empty;

//maximum tiles inside tilebag
#define MAX_TILES 100
//number of factores except the centre one
#define NUM_FACTORIES 5
//size of a factory
#define FACTORY_SIZE 4
//number of all factories
#define ALL_FACTORES 6
//default random engine value
#define RANDOM_ENGINE 10
//maximum number of tiles in the centre factory
#define CENTRE_FACTORY 16

//defined colours for tiles
#define RESET       "\033[0m"
#define BLACK       "\033[90m"      
#define RED         "\033[31m"     
#define YELLOW      "\033[33m"     
#define DARKBLUE    "\033[34m"     
#define LIGHTBLUE   "\033[1m\033[34m"      
#define ORANGE      "\033[91m" 

//unicode symbols
#define ARROW " \u25BA "
#define DIAMOND " \u2588"
#define DIAMOND2 "\u2666"
#define HELPBLOCK "\u3016 HELP \u3017 "
#define HEADER1 "\u2ABB \u2ABB \u2ABB \u2ABB \u2ABB  \u2ABC \u2ABC \u2ABC \u2ABC \u2ABC"
#define PLAYERBLOCK "\u2585 \u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585\u2585"
#define HELPSECTIONUP "\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7  H E L P \u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8"
#define HELPSECTIONDOWN "\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF7\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8\u2AF8"


#endif //TYPES_H