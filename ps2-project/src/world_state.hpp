/**
 * @file world_state.hpp
 * @brief Represents the massive 7-region matrix and Holy Church politics engine.
 */

#ifndef SEVENTH_VOW_WORLD_STATE_HPP
#define SEVENTH_VOW_WORLD_STATE_HPP

#include <tyra>
#include <string>
#include <vector>

namespace TheSeventhVow {

enum ChurchRank {
    RANK_ASH,
    RANK_CINDER,
    RANK_FLAME,
    RANK_RADIANT,
    RANK_SERAPH,
    RANK_THRONE
};

enum RegionType {
    REGION_TYR,
    REGION_VALEN,
    REGION_SERIS,
    REGION_KAELOR,
    REGION_MORVAIN,
    REGION_LYS,
    REGION_ARDENT
};

struct RegionConfig {
    RegionType type;
    std::string name;
    std::string architecture;
    std::string primaryEnemyType;
    float vowScalingMultiplier;
    float environmentalDegradationFactor; // altered based on burdenScars
    std::string dominantSin;
};

struct ChurchStatus {
    ChurchRank currentRank;
    float zealScore;            // 0.0f - 100.0f
    float suspicionLevel;       // 0.0f - 100.0f (high susp increases Vow breakage penalty)
    bool inquisitionActive;
};

class WorldState {
public:
    WorldState();
    ~WorldState();

    void init();

    /**
     * @brief Progress story and shift global church stance/politics.
     */
    void updatePolitics(int chapterIndex);

    /**
     * @brief Retrieve configuration for a specific region.
     */
    RegionConfig getRegionConfig(RegionType region) const;

    /**
     * @brief Increase or decrease suspicion based on Xyven's dialogue actions.
     */
    void alterSuspicion(float amount);

    /**
     * @brief Translate rank enum to readable string.
     */
    static const char* getRankName(ChurchRank rank);

    // Getters / Setters
    ChurchStatus getChurchStatus() const { return church; }
    RegionType getActiveRegion() const { return activeRegion; }
    void setActiveRegion(RegionType region) { activeRegion = region; }

private:
    std::vector<RegionConfig> regions;
    ChurchStatus church;
    RegionType activeRegion;

    void setupRegions();
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_WORLD_STATE_HPP
