#include "core/appManager.hpp"
#include "core/gameEngine.hpp"
#include "core/src/fileManager.hpp"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {
    AppManager app(argc, argv);
    return app.execute();
};