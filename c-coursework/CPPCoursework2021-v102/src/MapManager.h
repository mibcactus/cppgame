#include <iostream>
#pragma once

class MapManager {
public:
    void writeMap(std::string filename);
    void writeEntities();
    void writeStage();

    //int** readMap(std::string mapurl);
    void readEntities();
    void readStage();

private:
    int* stringToIntArray(std::string);
};
