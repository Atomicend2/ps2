// =================================================================
// SYSTEM REVISION: GENERIC ASSET & ANIMATION ALIAS CONTROLLER
// =================================================================
#ifndef ASSET_ADAPTER_HPP
#define ASSET_ADAPTER_HPP

namespace TheSeventhVow {

enum GenericAnimState {
    STATE_IDLE   = 0,
    STATE_WALK   = 1,
    STATE_ATTACK = 2,
    STATE_HIT    = 3,
    STATE_DEATH  = 4
};

struct MeshAnimationAdapter {
    int animationIndexMap[5]; // Maps internal GenericAnimState to the asset's raw track index
    
    // Automatically assigns default indices (0, 1, 2, 3...) if track names don't match
    void assignGenericTracks(int totalTracks) {
        for (int i = 0; i < 5; i++) {
            animationIndexMap[i] = (i < totalTracks) ? i : 0; 
        }
    }
};

} // namespace TheSeventhVow

#endif // ASSET_ADAPTER_HPP
