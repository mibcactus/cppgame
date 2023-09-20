#include "MapManager.h"

#include <iostream>
#include <fstream>
#include <string>

void MapManager::writeMap(std::string filename) {
    std::ofstream file;
    file.open(filename);

    if(file.is_open()) {
        file.close();
    }
}

int* MapManager::stringToIntArray(std::string str) {
    std::string temp_str;
    int num_array[16];
    int cur = 0;
    
    for(char i : str) {
        if(i == ',') {
            num_array[cur] = stoi(temp_str);
            cur++;
            temp_str = "";
        } else {
            temp_str = temp_str + i;
        }
    }

    return num_array;
}

/*
int** MapManager::readMap(std::string mapurl) {
    std::string line;
    std::ofstream file;
    file.open(mapurl);

    int tile_array[13][16];
    int cur = 0;
    
    if(file.is_open()) {
        while(std::getline(file, line)) {
            std::cout << line << "\n";
            //tile_array[cur] = stringToIntArray(line);
            //memcpy(tile_array[cur], stringToIntArray(line), sizeof(tile_array[cur]));
            int *temp_array = stringToIntArray(line);
            for(int i = 0; i < 16; i++) {
                tile_array[cur][i] = temp_array[i];
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open map.\n";
    }

    return tile_array;
}*/


