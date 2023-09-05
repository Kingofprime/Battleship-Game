#include "Pvp.h"
#include <iostream>

Pvp::Pvp(Logger& logger) : logger(logger), choice(0)
{
}
// Displaying options for ship placement
void Pvp::display_menu() {
    logger << "1) place ship manually\n";
    logger << "2) place ship randomly\n";
    logger << "Choice -->";
}

void Pvp::sorry_menu()
{
    logger << "1) place ship manually\n";
    logger << "2) place ship randomly\n";
    logger << "Choice --> \n";
    std::cin >> choice;
    std::system("cls");

    logger << "\n Sorry, Work in progress \n";
}

// Takes users input to choose placement
int Pvp::get_user_choice() {
    std::cin >> choice;
    return choice;
}
Pvp::~Pvp() {};