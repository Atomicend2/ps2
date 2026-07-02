/**
 * @file world_state.cpp
 * @brief Implement 7-region matrix and Holy Church state tracking.
 */

#include "world_state.hpp"

namespace TheSeventhVow {

WorldState::WorldState() : activeRegion(REGION_TYR) {
    init();
}

WorldState::~WorldState() {}

void WorldState::init() {
    setupRegions();
    
    // Default Church stance starting in Act 1 / Chapter 1
    church.currentRank = RANK_ASH;
    church.zealScore = 15.0f;
    church.suspicionLevel = 5.0f;
    church.inquisitionActive = false;
}

void WorldState::setupRegions() {
    regions.clear();

    // 1. Tyr
    RegionConfig tyr;
    tyr.type = REGION_TYR;
    tyr.name = "Tyr";
    tyr.architecture = "Gothic High Spire";
    tyr.primaryEnemyType = "CHURCH_HERALD";
    tyr.vowScalingMultiplier = 1.0f;
    tyr.environmentalDegradationFactor = 0.0f;
    tyr.dominantSin = "Pride";
    regions.push_back(tyr);

    // 2. Valen
    RegionConfig valen;
    valen.type = REGION_VALEN;
    valen.name = "Valen";
    valen.architecture = "Baroque Fortified Keep";
    valen.primaryEnemyType = "IRON_PALADIN";
    valen.vowScalingMultiplier = 1.2f;
    valen.environmentalDegradationFactor = 0.1f;
    valen.dominantSin = "Gluttony";
    regions.push_back(valen);

    // 3. Seris
    RegionConfig seris;
    seris.type = REGION_SERIS;
    seris.name = "Seris";
    seris.architecture = "Byzantine Sun Shrine";
    seris.primaryEnemyType = "LIGHTNING_ACOLYTE";
    seris.vowScalingMultiplier = 1.1f;
    seris.environmentalDegradationFactor = 0.05f;
    seris.dominantSin = "Lust";
    regions.push_back(seris);

    // 4. Kaelor
    RegionConfig kaelor;
    kaelor.type = REGION_KAELOR;
    kaelor.name = "Kaelor";
    kaelor.architecture = "Cyclopean Obsidian Obelisks";
    kaelor.primaryEnemyType = "VOID_WALKER";
    kaelor.vowScalingMultiplier = 1.4f;
    kaelor.environmentalDegradationFactor = 0.25f;
    kaelor.dominantSin = "Sloth";
    regions.push_back(kaelor);

    // 5. Morvain
    RegionConfig morvain;
    morvain.type = REGION_MORVAIN;
    morvain.name = "Morvain";
    morvain.architecture = "Decaying Subterranean Crypts";
    morvain.primaryEnemyType = "DECAYED_INQUISITOR";
    morvain.vowScalingMultiplier = 1.5f;
    morvain.environmentalDegradationFactor = 0.4f;
    morvain.dominantSin = "Envy";
    regions.push_back(morvain);

    // 6. Lys
    RegionConfig lys;
    lys.type = REGION_LYS;
    lys.name = "Lys";
    lys.architecture = "Ivory Shimmering Citadel";
    lys.primaryEnemyType = "CELESTIAL_ECHO";
    lys.vowScalingMultiplier = 1.3f;
    lys.environmentalDegradationFactor = 0.2f;
    lys.dominantSin = "Greed";
    regions.push_back(lys);

    // 7. Ardent
    RegionConfig ardent;
    ardent.type = REGION_ARDENT;
    ardent.name = "Ardent";
    ardent.architecture = "Flayed Scorched Cathedrals";
    ardent.primaryEnemyType = "SACRAMENT_JUDGE";
    ardent.vowScalingMultiplier = 2.0f;
    ardent.environmentalDegradationFactor = 0.8f;
    ardent.dominantSin = "Wrath";
    regions.push_back(ardent);
}

void WorldState::updatePolitics(int chapterIndex) {
    TYRA_LOG("[POLITICS] Progressing story. Recalculating Church power stance...");
    
    // Shift Church rank based on chapters/acts
    switch (chapterIndex) {
        case 0:
            church.currentRank = RANK_ASH;
            church.zealScore = 20.0f;
            break;
        case 1:
            church.currentRank = RANK_CINDER;
            church.zealScore = 35.0f;
            church.suspicionLevel += 10.0f;
            break;
        case 2:
            church.currentRank = RANK_FLAME;
            church.zealScore = 50.0f;
            church.suspicionLevel += 15.0f;
            break;
        case 3:
            church.currentRank = RANK_RADIANT;
            church.zealScore = 65.0f;
            church.suspicionLevel += 10.0f;
            break;
        case 4:
            church.currentRank = RANK_SERAPH;
            church.zealScore = 80.0f;
            church.suspicionLevel += 20.0f;
            church.inquisitionActive = true;
            TYRA_LOG("[POLITICS] WARNING: Holy Inquisition is now ACTIVE! Heresy hunt intensified.");
            break;
        case 5:
        case 6:
            church.currentRank = RANK_THRONE;
            church.zealScore = 100.0f;
            church.suspicionLevel = 100.0f;
            church.inquisitionActive = true;
            TYRA_LOG("[POLITICS] CRITICAL: Maximum suspicious levels reached. Inquisition hunts Xyven.");
            break;
    }

    TYRA_LOG("[POLITICS] Church State: [Rank: %s] [Zeal: %.1f%%] [Suspicion: %.1f%%] [Inquisition: %s]",
             getRankName(church.currentRank),
             church.zealScore,
             church.suspicionLevel,
             church.inquisitionActive ? "ACTIVE" : "INACTIVE");
}

RegionConfig WorldState::getRegionConfig(RegionType region) const {
    for (const auto& config : regions) {
        if (config.type == region) {
            return config;
        }
    }
    return regions[0];
}

void WorldState::alterSuspicion(float amount) {
    church.suspicionLevel += amount;
    if (church.suspicionLevel < 0.0f) church.suspicionLevel = 0.0f;
    if (church.suspicionLevel > 100.0f) church.suspicionLevel = 100.0f;
    
    TYRA_LOG("[POLITICS] Suspension level changed by %.1f. Current suspicion: %.1f%%", amount, church.suspicionLevel);
}

const char* WorldState::getRankName(ChurchRank rank) {
    switch (rank) {
        case RANK_ASH:     return "Ash (Mendicant)";
        case RANK_CINDER:  return "Cinder (Prelate)";
        case RANK_FLAME:   return "Flame (Grand Inquisitor)";
        case RANK_RADIANT: return "Radiant (Bishop)";
        case RANK_SERAPH:  return "Seraph (Cardinal Council)";
        case RANK_THRONE:  return "Throne (Pontiff / Executioner)";
        default:           return "Unknown";
    }
}

} // namespace TheSeventhVow
