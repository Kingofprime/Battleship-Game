#include <string>
#include "Logger.h"
#include "Board.h"
#include "Player.h"

class Sorry {
public:
    Sorry(Logger& logger, Board& player1_board , Board& cpuboard);
    void sorry_menu(Board player1_board, Board cpuboard);
    void choice1(Board player1_board, Board cpuboard);
    void run_choice(Board player1_board, Board cpuboard);
    ~Sorry();
private:
    Logger& logger;
    Board& player1_board;
    Board& cpuboard;
};

