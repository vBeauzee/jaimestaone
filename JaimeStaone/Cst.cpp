#include "Cst.hpp"
#include "Bullet.hpp"

namespace Cst {
    // Windows Size
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    const int GAME_GRID = 64;

    const std::string PLAYER = "player";
    const std::string UFO = "ufo";
    const std::string BULLET = "bullet";

    const sf::Time FIRE_COOLDOWN = sf::seconds(0.1);

    const std::string LEVEL_FILENAME="../data/level.csv";
    const std::string CSV_SEPARATOR = ";";

    const float THRESHOLD_FLOAT = 0.02;
}
