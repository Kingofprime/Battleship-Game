#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "Logger.h"
#include "Board.h"
#include "Player.h"
#include "Mainmenu.h"
#include "Pvp.h"
#include "Game.h"
#include "Placeship.h"
#include "Sorry.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    Logger logger("output.txt");
    Board player1_board(logger);
    Board player2_board(logger);
    Board cpu_board(logger);
    Mainmenu mainmenu(logger);
    mainmenu.display_menu();
    int choice = mainmenu.get_user_choice();
    if (choice == 1)
    {
        Pvp pvp(logger);
        pvp.display_menu();
        int choice1 = pvp.get_user_choice();
        logger << choice1 << "\n";
        std::system("cls");
        if (choice1 == 1)
        {
            Placeship g1(logger, player1_board);
            g1.choice1();
            std::system("pause");
            std::system("cls");
            Placeship g2(logger, player2_board);
            g2.choice2();
            std::system("pause");
            std::system("cls");
        }
        else if (choice1 == 2)
        {
            Placeship g3(logger, player1_board);
            g3.choice3();
            Placeship g4(logger, player2_board);
            g4.choice4();  
        }
        else
        {
            return false;
        }
        std::system("cls");
        Player player1(player1_board);
        Player player2(player2_board);
        Game game(logger);
        game.run_choice(player1_board,player2_board);
    }
    else if (choice == 2)
    {
        Player player1(player1_board);
        Player player2(cpu_board);
        Sorry sorry(logger, player1_board, cpu_board );
        sorry.sorry_menu(player1_board, cpu_board);
        sorry.choice1(player1_board, cpu_board);
        
    }
    else {
        return false;
    }
    return 0;
}