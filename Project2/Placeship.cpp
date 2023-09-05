#include "Placeship.h"
#include <iostream>
#include "Game.h"
#include "Board.h"

Placeship::Placeship(Logger& logger, Board& player1_board) : logger(logger), player1_board(player1_board)
{
}
// Placing ships for player 1 for manual placement
void Placeship::choice1() {
    logger << "Player 1:";
    player1_board.place_ships_manually();
}
// Placing ships for player 2 for manual placement
void Placeship::choice2() {
    logger << "Player 2:";
    player1_board.place_ships_manually();
}
// Placing ships for player 1 for random placement
void Placeship::choice3() {
    player1_board.place_ships_randomly();
}
// Placing ships for player 2 for random placement
void Placeship::choice4() {
    player1_board.place_ships_randomly();
}
Placeship::~Placeship(){}