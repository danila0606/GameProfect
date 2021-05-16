#include "Headers/Game.h"

int main() {

    try {
        Game game("Images//Background.png", "Images//level.tmx");
        game.Load();
    }
    catch (std::exception& e) {
        std::cerr<<e.what()<<std::endl;
        exit(1);
    }

    return 0;
}