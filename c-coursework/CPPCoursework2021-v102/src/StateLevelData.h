#pragma once
#include <vector>

#include "ForegroundData.h"
#include "MobData.h"

// saves all entity data in a level
struct StateLevelData {
        bool initialised = false;
        
        int level_ID = 0;
        int mob_amount = 0;
        int fg_count = 0;
        int x_offset = 0;
        int y_offset = 0;

        // Player data
        int player_hp = 0;
        int player_x = 0;
        int player_y = 0;

        // enemy data
        std::vector<MobData> mob_data;
        // detail data
        std::vector<fg_data> detail_data;
    
        void addDetailData(fg_data fg) {
            detail_data.push_back(fg);
            fg_count++;
        }

        void addMobData(MobData md) {
            mob_data.push_back(md);
            mob_amount++;
        }

        std::vector<fg_data> getDetailData() {
            return detail_data;
        }
    
        std::vector<MobData> getMobDataVector() {
            return mob_data;
        }

        void printPlayerDataConsole() {
            printf("HP: %d\nLocation: (%d, %d)\n", player_hp, player_x, player_y);
        }

        std::string playerDataString() {
            std::string str = "HP: " + std::to_string(player_hp) + " Location: (" + std::to_string(player_x) + ", " + std::to_string(player_y) + ")";
            return str;
        }
};
