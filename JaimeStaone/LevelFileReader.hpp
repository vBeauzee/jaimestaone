#pragma once
#include <string>

class LevelFileReader {
public:
    LevelFileReader();
    ~LevelFileReader();

    void readFile();
    void readLine(std::string& line);
    void initEnemies(std::string* enemyData);
};
