#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "logger.h"

class Board {
public:
    Board(Logger& logger);

    char get_tile(int y, int x) const;
    void set_tile(int y, int x, char value);
    void place_ships_manually();
    void place_ships_randomly();
    bool all_ships_sunk() const;
    int cpu_turn();
    int player_turn();
    int player_turn1();
    int get_points() const;
    void print() const;
    ~Board();

private:
    int points;
    std::vector<std::string> board;
    Logger& logger;
    friend class Game;

    bool get_coordinates(int& x, int& y) const;
    int attack_ship();
    int bomb_2x2_area();
    int bomb_row_or_column();
    int confirm_hit();
    int hit_ship(int x, int y );

};

#endif // BOARD_H


