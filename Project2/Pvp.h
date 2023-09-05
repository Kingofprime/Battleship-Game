#pragma once

#include <string>
#include "Logger.h"

class Pvp {
public:
    Pvp(Logger& logger);

    void display_menu();
    int get_user_choice();
    void sorry_menu();
    ~Pvp();
private:
    int choice;
    Logger& logger;
};


