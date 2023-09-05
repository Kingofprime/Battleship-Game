#include "Mainmenu.h"
#include <iostream>

Mainmenu::Mainmenu(Logger& logger) : logger(logger), choice(0) 
{
}
// Inital display when program is first run
void Mainmenu::display_menu() {
    logger<< "-------------------------------\n"
        << "AERSP 424 Project \n"
        << "By -Ankit Gupta & Nigam Bhavsar \n"
        << "Battleship  Menu Options\n"
        << "-------------------------------\n";
    logger << "1) player vs player\n";
    logger << "2) player vs cpu\n";
    logger << "Choice --> \n";
}

// Getting users choice of CPU or PvP
int Mainmenu::get_user_choice() {
    std::cin >> choice;
    logger << choice;
    return choice;
}
Mainmenu::~Mainmenu(){}
