#include "Board.h"
#include "parameters.h"
#include <iostream>

Board::Board(Logger& logger) : logger(logger), points(POINTS)
{
    board.resize(BOARD_SIZE, std::string(BOARD_SIZE, '-'));
}
char Board::get_tile(int y, int x) const {
    return board[y][x];
}

void Board::set_tile(int y, int x, char value) {
    board[y][x] = value;
}
// Function for placing ships manually (S represents ship)
void Board::place_ships_manually() {
    logger << "Place your ships (total " << NUM_SHIPS << " ships, one cell each)\n";
    print();

    for (int i = 0; i < NUM_SHIPS; i++)
    {
        int x, y;
        while (true)
        {
            logger << "Enter coordinates for ship " << i + 1 << " (x): ";
            std::cin >> x;
            logger << x;
            logger << "\nEnter coordinates for ship " << i + 1 << " (y): ";
            std::cin >> y;
            logger << y;
            logger << "\n";
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[y][x] == 'S')
            {
                logger << "Invalid coordinates. Try again.\n";
            }
            else
            {
                break;
            }
        }
        board[y][x] = 'S';
        print();
    }
}

// Function for placing ships randomly (S represents ship)
void Board::place_ships_randomly()
{

    for (int i = 1; i <= NUM_SHIPS; i++)
    {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[y][x] == '-')
        {
            board[y][x] = 'S';
        }
        else
        {
            i--;
        }
    }
}

// Functions that searches for ships (S) on board when called
bool Board::all_ships_sunk() const {
    for (const auto& row : board)
    {
        if (row.find('S') != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

// Function that runs if player vs CPU is chosen, and tells you if the cpu missed or hit one of the players ships
int Board::cpu_turn() {

    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;

    if (board[y][x] == 'S')
    {
        board[y][x] = 'X';
        logger << "CPU hit a ship at (" << x << ", " << y << ")!\n";
        return 1;
    }
    else if (board[y][x] == 'X')
    {
        board[y][x] = 'X';
        logger << "CPU missed at (" << x << ", " << y << ").\n";
        return 0;
    }
    else 
    {
        board[y][x] = 'O';
        logger << "CPU missed at (" << x << ", " << y << ").\n";
        return 0;
    }
}
int Board::player_turn1() {
    int action;
    logger << "Choose an action (1): ";
   
        logger << "Attack\n";
        return attack_ship();
    
}
// Function to ask for player to choose type of attack
int Board::player_turn() {
    int action;
    logger << "Choose an action (1: Attack, 2: Carpet Bombing (costs " << CARPET_BOMB_COST << " points) , 3: 2x2 Bombing (costs " << BOMB_COST_2x2 << "points) , 4: Confirm Hit(costs " << CONFIRM_HIT_COST << "points)): ";
    std::cin >> action;
    logger << action << "\n";
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
        logger << "Attack\n";
        return attack_ship();
    }
}
int Board::get_points() const
{
    return points;
}
// Function to display board based off values in parameters.h
void Board::print() const
{
    logger << "Y |";
    logger << " X";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        logger << " | " << i;
    }
    logger << " |";
    int i = 0;
    for (const auto& row : board)
    {

        logger << "\n******************************************\n";

        logger << i << " | X | ";
        for (const auto& cell : row)
        {
            logger << cell << " | ";
        }
        logger << "\n";
        i++;
    }
}

    // Function to allow players to input the coordinates of location they wish to attack
    bool Board::get_coordinates(int& x, int& y) const
    {
        logger << "Enter coordinates (x): ";
        std::cin >> x;
        logger << x << "\n";
        logger << "\nEnter coordinates (y): ";
        std::cin >> y;
        logger << y << "\n";
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        {
            logger << "Invalid coordinates. Try again.\n";
            return false;
        }
        return true;
    }
    // Function that confirms whether player attack hits or misses
    int Board::attack_ship() {
        int x, y;
        while (!get_coordinates(x, y));

        if (board[y][x] == 'S')
        {
            board[y][x] = 'X';
            logger << "\nHit! \n";
            points++;
            return 1;
        }
        else
        {
            board[y][x] = 'O';
            logger << "\nMiss!\n";
            return 0;
        }
    }
    // Function for 2x2 bomb, asks for top left location of desired area and uses that to bomb a 2x2 area
    int Board::bomb_2x2_area()
    {
        int x, y;
        logger << "Enter the top-left corner coordinates for the 2x2 area (x, y): \n";
        while (!get_coordinates(x, y));

        int hits = 0;

        for (int i = y; i < y + 2 && i < BOARD_SIZE; i++) {
            for (int j = x; j < x + 2 && j < BOARD_SIZE; j++) {
                if (board[i][j] == 'S') {
                    board[i][j] = 'X';
                    hits++;
                }
                else if (board[i][j] == '-') {
                    board[i][j] = 'O';
                }
            }
        }

        points -= BOMB_COST_2x2;
        logger << "Bombing 2x2 area with top-left corner at (" << x << ", " << y << ") resulted in " << hits << " hits.\n";
        return hits;
    }
    // Function for carpet bomb, asks if you would like to bomb either row or column 
    int Board::bomb_row_or_column() {
        int choice, index;
        logger << "Choose (1: Bomb row, 2: Bomb column): ";
        std::cin >> choice;

        logger << "Enter " << (choice == 1 ? "row" : "column") << " index (0-" << BOARD_SIZE - 1 << "): ";
        std::cin >> index;

        int hits = 0;

        // If loop checks for row bomb
        if (choice == 1) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board[index][i] == 'S') {
                    board[index][i] = 'X';
                    hits++;
                }
                else if (board[index][i] == '-') {
                    board[index][i] = 'O';
                }
            }
        }
        // If player chooses to column bomb
        else {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board[i][index] == 'S') {
                    board[i][index] = 'X';
                    hits++;
                }
                else if (board[i][index] == '-') {
                    board[i][index] = 'O';
                }
            }
        }

        points -= CARPET_BOMB_COST;
        logger << "Bombing " << (choice == 1 ? "row" : "column") << " " << index << " resulted in " << hits << " hits.\n";
        return hits;
    }

    // Function that checks each hit spot and replaces S with X if the hit landed
    int Board::hit_ship(int x, int y) {
        if (board[y][x] == 'S') {
            board[y][x] = 'X';
            return 1;
        }
        return 0;
    }

    // Function for confirm hit bomb (ability) that guarantees a hit on one of the opponents ship
    int Board::confirm_hit() {
        std::vector<std::pair<int, int>> ship_coordinates;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 'S') {
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
    Board::~Board(){}