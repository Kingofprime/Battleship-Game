#include "Player.h"
#include <iostream>
#include "parameters.h"

Player::Player(Board& player_board) : board(player_board), points(10) {}
int Player::player_turn() {
    int action;
    logger << "Choose an action (1: Attack, 2: Carpet Bombing (costs " << CARPET_BOMB_COST << " points) , 3: 2x2 Bombing (costs " << BOMB_COST_2x2 << "points) , 4: Confirm Hit(costs " << CONFIRM_HIT_COST << "points)): ";
    std::cin >> action;

    if (action == 2 && points >= CARPET_BOMB_COST) {
        return bomb_row_or_column();
    }
    if (action == 3 && points >= BOMB_COST_2x2) {
        return bomb_2x2_area();
    }
    if (action == 4 && points >= CONFIRM_HIT_COST) {
        return confirm_hit();
    }
    else {
        logger << "Wrong option - Attack\n";
        return attack_ship();
    }
}

int Player::cpu_turn() {
    return 0;
}


int Player::get_points() const
{
    return points;
}


bool Player::get_coordinates(int& x, int& y) {
        logger << "Enter coordinates (x): ";
        std::cin >> x;
        logger << "\nEnter coordinates (y): ";
        std::cin >> y;
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        {
            logger << "Invalid coordinates. Try again.\n";
            return false;
        }
        return true;
    }
int Player::attack_ship() {
        int x, y;
        while (!get_coordinates(x, y));

        if (board.get_tile(y, x) == 'S')
        {
            board.set_tile(y, x, 'X');
            logger << "\nHit! \n";
            points--;
            return 1;
        }
        else
        {
            board.set_tile(y, x, 'O');;
            logger << "\nMiss!\n";
            return 0;
        }
    }
int Player::bomb_2x2_area() {
        int x, y;
        logger << "Enter the top-left corner coordinates for the 2x2 area (x, y): \n";
        while (!get_coordinates(x, y));

        int hits = 0;

        for (int i = y; i < y + 2 && i < BOARD_SIZE; i++) {
            for (int j = x; j < x + 2 && j < BOARD_SIZE; j++) {
                if (board.get_tile(i, j) == 'S') {
                    board.set_tile(i, j, 'X');
                    hits++;
                }
                else if (board.get_tile(i, j) == '-') {
                    board.set_tile(i, j, 'O');
                }
            }
        }

        points -= BOMB_COST_2x2;
        logger << "Bombing 2x2 area with top-left corner at (" << x << ", " << y << ") resulted in " << hits << " hits.\n";
        return hits;
    }
int Player::bomb_row_or_column()
    {
        int choice, index;
        logger << "Choose (1: Bomb row, 2: Bomb column): ";
        std::cin >> choice;

        logger << "Enter " << (choice == 1 ? "row" : "column") << " index (0-" << BOARD_SIZE - 1 << "): ";
        std::cin >> index;

        int hits = 0;

        if (choice == 1) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board.get_tile(index, i) == 'S') {
                    board.set_tile(index, i, 'X');
                    hits++;
                }
                else if (board.get_tile(index, i) == '-') {
                    board.set_tile(index, i, 'O');
                }
            }
        }
        else {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board.get_tile(i, index) == 'S') {
                    board.set_tile(i, index, 'X');
                    hits++;
                }
                else if (board.get_tile(i, index) == '-') {
                    board.set_tile(i, index, 'O');
                }
            }
        }

        points -= CARPET_BOMB_COST;
        logger << "Bombing " << (choice == 1 ? "row" : "column") << " " << index << " resulted in " << hits << " hits.\n";
        return hits;
    }
int Player::hit_ship(int x, int y) {
    if (board.get_tile(y,x) == 'S') {
        board.set_tile(y,x,'X');
        return 1;
    }
    return 0;
}

int Player::confirm_hit() {
    std::vector<std::pair<int, int>> ship_coordinates;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board.get_tile(i,j) == 'S') {
                ship_coordinates.push_back({ j, i });
            }
        }
    }

    if (ship_coordinates.empty()) {
        logger << "No ships found.\n";
        return 0;
    }

    int index = rand() % ship_coordinates.size();
    int x = ship_coordinates[index].first;
    int y = ship_coordinates[index].second;

    if (hit_ship(x, y)) {
        logger << "Confirmed: There is a ship at (" << x << ", " << y << "). Ship hit!\n";
        points -= CONFIRM_HIT_COST;
        return 1;
    }
    else {
        logger << "Confirmed: There is a ship at (" << x << ", " << y << "). But it has already been hit.\n";
        points -= CONFIRM_HIT_COST;
        return 0;
    }
}
Player::~Player(){}