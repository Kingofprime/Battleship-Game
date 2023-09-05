#include <string>
#include "Logger.h"
#include "Board.h"
#include "Player.h"


class Game {
public:
    Game(Logger& logger);
    void run_choice(Board player1_board, Board player2_board);
    ~Game();
    
private:
    Logger& logger;
    
};
