#pragma once

#ifndef CMD_HPP
#define CMD_HPP

#include <string>
#include <memory>
#include "gameEngine.hpp"

class cmd {
    private:
        int width = 0;
        int height = 0;
        bool useGraphicMode = false;
        bool makeconfig = false;
        std::string makeConfigPath;
        int iterationCount = 0;
        int iterationTime = 250;
        bool editionMode = false;
        bool emptyConfig = false;
        bool toricMode = false;

        bool shouldExit = false;
        int exitCode = 0;

        std::unique_ptr<GameEngine> game;

    public:
        cmd(int argc, char *argv[]);
        int run();
};

#endif