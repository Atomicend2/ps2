/**
 * @file level_builder.hpp
 * @brief Spatial coordinates layout, collision boundaries, and level assembly for Act I.
 */

#ifndef SEVENTH_VOW_LEVEL_BUILDER_HPP
#define SEVENTH_VOW_LEVEL_BUILDER_HPP

#include <tyra.h>
#include <string>
#include <vector>
#include "asset_adapter.hpp"

namespace TheSeventhVow {

struct LevelMeshNode {
    std::string name;
    Tyra::Vec4 position;
    Tyra::Vec4 rotation;
    Tyra::Vec4 scale;
    std::string assetPath;
    MeshAnimationAdapter animAdapter;
};

struct LevelTrigger {
    Tyra::Vec4 minBound;
    Tyra::Vec4 maxBound;
    std::string actionType;
    bool isTriggered;
};

struct LevelLayout {
    int sceneId;
    std::string sceneTitle;
    std::vector<LevelMeshNode> staticMeshes;
    std::vector<LevelMeshNode> props;
    std::vector<LevelMeshNode> enemySpawns;
    std::vector<LevelTrigger> triggers;
};

class LevelBuilder {
public:
    LevelBuilder();
    ~LevelBuilder();

    /**
     * @brief Generates Act I Scene 1.1 (Border Garrison Courtyard) coordinates
     */
    LevelLayout buildScene1_1_Courtyard();

    /**
     * @brief Generates Act I Scene 1.2 (Grand Strategy Hall) coordinates
     */
    LevelLayout buildScene1_2_StrategyHall();

    /**
     * @brief Generates Act I Scene 1.3 (Burning Battlements) coordinates
     */
    LevelLayout buildScene1_3_Battlements();

    /**
     * @brief Generates Act II Scene 2.1 (The Rainy Basalt Perimeter) coordinates
     */
    LevelLayout buildScene2_1_RainyBasalt();

    /**
     * @brief Generates Act II Scene 2.2 (The Obsidian Panopticon) coordinates
     */
    LevelLayout buildScene2_2_ObsidianPanopticon();

    /**
     * @brief Generates Act II Scene 2.3 (The Execution Scaffold) coordinates
     */
    LevelLayout buildScene2_3_ExecutionScaffold();

    /**
     * @brief Generates Act III Scene 3.1 (The Immaculate Limestone Promenade) coordinates
     */
    LevelLayout buildScene3_1_LimestonePromenade();

    /**
     * @brief Generates Act III Scene 3.2 (The Seris Sanctum Sanctuary) coordinates
     */
    LevelLayout buildScene3_2_SanctumSanctuary();

    /**
     * @brief Generates Act III Scene 3.3 (The Soul-Harvesting Under-Lab) coordinates
     */
    LevelLayout buildScene3_3_UnderLab();

    /**
     * @brief Generates Act IV Scene 4.1 (The Frozen Cliff Path) coordinates
     */
    LevelLayout buildScene4_1_FrozenCliff();

    /**
     * @brief Generates Act IV Scene 4.2 (The Grand Archives) coordinates
     */
    LevelLayout buildScene4_2_GrandArchives();

    /**
     * @brief Generates Act IV Scene 4.3 (The Clockwork Astrolabe) coordinates
     */
    LevelLayout buildScene4_3_ClockworkAstrolabe();

    /**
     * @brief Generates Act V Scene 5.1 (The Petrified Forest Entry) coordinates
     */
    LevelLayout buildScene5_1_PetrifiedForest();

    /**
     * @brief Generates Act V Scene 5.2 (The Red Clearing Boss Arena) coordinates
     */
    LevelLayout buildScene5_2_RedClearing();

    /**
     * @brief Generates Act VI Scene 6.1 (The Misty Marsh Shore) coordinates
     */
    LevelLayout buildScene6_1_MistyMarsh();

    /**
     * @brief Generates Act VI Scene 6.4 (The Sunken Baptistry) coordinates
     */
    LevelLayout buildScene6_4_SunkenBaptistry();

    /**
     * @brief Generates Act VII Scene 7.2 (The Assembly Belts) coordinates
     */
    LevelLayout buildScene7_2_AssemblyBelts();

    /**
     * @brief Generates Act VII Scene 7.3 (The Smelting Core Cathedral) coordinates
     */
    LevelLayout buildScene7_3_SmeltingCore();

    /**
     * @brief Generates Act VIII Scene 8.1 (The Celestial Citadel) coordinates
     */
    LevelLayout buildScene8_1_CelestialCitadel();

    /**
     * @brief Generates Act VIII Scene 8.3 (The Star-Chamber Nave) coordinates
     */
    LevelLayout buildScene8_3_StarChamber();

    /**
     * @brief Generates Act IX Scene 9.1 (The Infinite Mirror Plane) coordinates
     */
    LevelLayout buildScene9_1_InfiniteMirror();

    /**
     * @brief Generates Act IX Scene 9.2 (The True Altar) coordinates
     */
    LevelLayout buildScene9_2_TrueAltar();

    /**
     * @brief Prints diagnostic coordinates to Serial Console
     */
    void logLevelDiagnostics(const LevelLayout& layout) const;
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_LEVEL_BUILDER_HPP
