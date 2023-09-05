#include <iostream>
#include "Game.h"

Game::Game(Logger& logger) : logger(logger)
{
}

// Function that runs during game and checks ships
void Game::run_choice(Board player1_board, Board player2_board) {
    int player_turns = 0;
    // Loop that runs as long as both players have unsunk on board
    while (!player1_board.all_ships_sunk() && !player2_board.all_ships_sunk())
    {
        logger << "Player " << (player_turns % 2 + 1) << "'s turn\n";

        if (player_turns % 2 == 0) {
            player2_board.print();
            logger << "Player 1 points: " << player1_board.get_points() << "\n";
            player1_board.player_turn();
            std::system("pause");
            std::system("cls");
        }
        else
        {
            player1_board.print();
            logger << "Player 2 points: " << player2_board.get_points() << "\n";
            player2_board.player_turn();
            std::system("pause");
            std::system("cls");
        }
        player_turns++;
    }
    // If loop that detects when one player has all their ships sunk and displays the winner
    if (player1_board.all_ships_sunk() == true)
    {
        logger << "Player 1 " << " wins!\n";
        std::cout << "You can review the game in the output.txt ";
    }
    else
    {
        logger << "Player 2 " << " wins!\n";
        std::cout << "You can review the game in the output.txt ";
    }
}
Game::~Game(){}

