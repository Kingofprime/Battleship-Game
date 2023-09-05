#include "Sorry.h"
#include <iostream>

Sorry::Sorry(Logger& logger, Board& player1_board , Board& cpuboard) : logger(logger), player1_board(player1_board) , cpuboard(cpuboard)
{
}
void Sorry::sorry_menu(Board player1_board, Board cpuboard)
{
    logger << "1) place ship manually\n";
    logger << "2) place ship randomly\n";
}
void Sorry::choice1(Board player1_board, Board cpuboard)
{
    logger << "Choice --> \n";
    int choice;
    std::cin >> choice;
    logger << choice << "\n";
    std::system("cls");
    if (choice == 1)
    {
        player1_board.place_ships_manually();
        cpuboard.place_ships_randomly();
        run_choice(player1_board, cpuboard);
    }
    else if (choice == 2)
    {
        player1_board.place_ships_randomly();
        cpuboard.place_ships_randomly();
        run_choice(player1_board, cpuboard);
    }
    else {
        logger << "Wrong option";
    }
}
void Sorry::run_choice(Board player1_board, Board cpuboard)
{
    int player_turns = 0;
    while (player1_board.all_ships_sunk()==false && cpuboard.all_ships_sunk()==false )
    {
        if (player_turns % 2 == 0)
        {
            logger << player_turns << " nd Turn\n";
            logger << "Player 1 turn\n";
            cpuboard.print();
            logger << "Player 1" << "\n";
            player1_board.player_turn1();
            std::system("pause");
            std::system("cls");
        }
        else
        {
            logger << "CPU turn\n";
            player1_board.print();
            logger << "CPU " << "\n";
            cpuboard.cpu_turn();
            std::system("pause");
            std::system("cls");
        }
        player_turns++;
    }
    if(cpuboard.all_ships_sunk()==true)
    {
        logger << "CPU " << " wins!\n";
        std::cout << "You can review the game in the output.txt ";
    }
    else
    {
        logger << "Player " << " wins!\n";
        std::cout << "You can review the game in the output.txt ";
    }   
}
Sorry::~Sorry(){}