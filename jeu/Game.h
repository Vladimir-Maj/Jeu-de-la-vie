#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "grille/Grille.h"
#include <cassert>
#include <sstream>
#include "cellule/Cellule.h"
#include "grille/Grille.h"


class Game {
private:
    std::string fichierEntree;
    std::string fichierEntree0;
    int iterations;
    int delai;
    bool modeConsole;
    bool choixGrille;

public:
    Game();  
    void lancer();  
};