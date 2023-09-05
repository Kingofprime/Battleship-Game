#pragma once

#include <string>
#include "Logger.h"

class Mainmenu {
public:
    Mainmenu(Logger& logger);

    void display_menu();
    int get_user_choice();
    ~Mainmenu();
private:
    int choice;
    Logger& logger;
};


