#include "LevelFileReader.hpp"
#include <fstream>
#include "Cst.hpp"

LevelFileReader::LevelFileReader() {
}

LevelFileReader::~LevelFileReader() {}

void LevelFileReader::readFile() {

    auto filename = Cst::LEVEL_FILENAME;
    std::ifstream file(filename);
    if (!file.is_open()) {
        printf("Unable to open %s", filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        readLine(line);
    }

    file.close();
}

void LevelFileReader::readLine(std::string& line) {
    const int size = 10;

    std::string levelDatas[size];
    size_t pos = 0;
    for (int i = 0; i < size; ++i) {
        pos = line.find(Cst::CSV_SEPARATOR);
        if (pos == std::string::npos) {
            levelDatas[i] = line;
            break;
        }
        levelDatas[i] = line.substr(0, pos);
        line.erase(0, pos + Cst::CSV_SEPARATOR.length());
    }
    initEnemies(levelDatas);
}

void LevelFileReader::initEnemies(std::string* enemyData) {
    auto enemy = EnemiesPool::INSTANCE->get();
    enemy->radius = 45;
    enemy->setSprite("../art/ufo_" + enemyData[0] + ".png");
    enemy->setCoordinates(std::stof(enemyData[1]), std::stof(enemyData[2]));
    enemy->tx = (std::stof(enemyData[3]));
    enemy->ty = (std::stof(enemyData[4]));
}
