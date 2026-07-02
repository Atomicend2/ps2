// =================================================================
// SYSTEM ADDITION: MEMORY CARD PACKED BINARY SERIALIZER
// =================================================================
#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <tamtypes.h>
#include <stdio.h>
#include <stdint.h>

namespace TheSeventhVow {

struct __attribute__((packed)) PS2SaveBlock {
    char magic[4];            // "7VOW"
    uint8_t currentAct;       // 1-9
    uint8_t currentScene;     // Active level map ID
    uint16_t vowScarFlags;    // Packed stats
    float position[3];        // X, Y, Z coordinates
    uint8_t churchSuspicion[7]; // 7-Region Matrix values
    int8_t factionRep[7];     // Regional politics scores
    uint32_t itemBitmask;     // Unlocked inventory flags
    uint32_t crc32;           // Integrity check
};

class SaveManager {
public:
    static bool writeSaveGame(int slot, const PS2SaveBlock& data) {
        char path[64];
        // Targeting Memory Card Slot 1, project directory
        sprintf(path, "mc0:/BISCUS-97000/SAVE%d.DAT", slot);
        
        FILE* file = fopen(path, "wb");
        if (!file) return false;
        
        size_t written = fwrite(&data, 1, sizeof(PS2SaveBlock), file);
        fclose(file);
        
        return (written == sizeof(PS2SaveBlock));
    }
};

} // namespace TheSeventhVow

#endif // SAVE_MANAGER_HPP
