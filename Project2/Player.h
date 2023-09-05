#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <vector>
#include <utility>
#include <fstream>

class Player
{
public:
    Player(Board& player_board);

    int player_turn();
    int cpu_turn();
    int get_points() const;
    bool get_coordinates(int& x, int& y);
    int attack_ship();
    int confirm_hit();
    int bomb_2x2_area();
    int bomb_row_or_column();
    int hit_ship(int x, int y);
    ~Player();
private:
    Board& board;
    int points;
    std::ofstream logger;
    //Logger& logger;
   
};

#endif // PLAYER_H

