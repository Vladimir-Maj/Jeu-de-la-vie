#include "core/gameEngine.hpp"
#include "core/src/fileManager.hpp"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include "core/cmd.hpp"

int main(int argc, char *argv[]) {
    cmd app(argc, argv);
    return app.run();
}
