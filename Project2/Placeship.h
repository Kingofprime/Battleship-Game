#pragma once
#include <string>
#include "Logger.h"
#include "Board.h"
#include "Player.h"


class Placeship {
public:
    Placeship(Logger& logger, Board& player1_board);
    void choice1();
    void choice2();
    void choice3();
    void choice4();
    ~Placeship();
private:
    Logger& logger;
    Board& player1_board;
};

