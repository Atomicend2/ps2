/**
 * @file chapter_manager.hpp
 * @brief Story chapter state and streaming asset loader under PS2 32MB RAM constraints
 */

#ifndef SEVENTH_VOW_CHAPTER_MANAGER_HPP
#define SEVENTH_VOW_CHAPTER_MANAGER_HPP

#include <tyra.h>

namespace TheSeventhVow {

/**
 * @brief The linear story chapters of 'The Seventh Vow'.
 */
enum StoryChapter {
    CHAPTER_1_HOLY_WAR,
    CHAPTER_2_MILITARY_RANKS,
    CHAPTER_3_DARK_ORIGINS,
    CHAPTER_4_WHISPERING_EXPERIMENTATION,
    CHAPTER_5_SPIRES_OF_MANIPULATION,
    CHAPTER_6_THE_BETRAYAL,
    CHAPTER_7_THE_TYRANT
};

/**
 * @brief Describes Elyndra's region settings for the current chapter
 */
struct RegionData {
    const char* regionName;
    const char* architectureStyle;
    const char* localReligionName;
    const char* dominantSin;
};

class ChapterManager {
public:
    ChapterManager(Tyra::Engine* engine);
    ~ChapterManager();

    /**
     * @brief Initialize chapter manager and load initial chapter.
     */
    void init();

    /**
     * @brief Progress to the next chapter.
     */
    void nextChapter();

    /**
     * @brief Load configurations, assets, and flush VRAM for a specific chapter
     */
    void loadChapterSetup(StoryChapter chapter);

    // Getters
    StoryChapter getCurrentChapter() const { return currentChapter; }
    const RegionData& getCurrentRegion() const { return currentRegion; }
    const char* getChapterTitle() const { return getChapterTitle(currentChapter); }
    bool isCutsceneActive() const { return cutsceneActive; }
    void setCutsceneActive(bool active) { cutsceneActive = active; }

    // Helpers
    static const char* getChapterTitle(StoryChapter chapter);

private:
    Tyra::Engine* engine;
    StoryChapter currentChapter;
    RegionData currentRegion;
    bool cutsceneActive;

    void updateRegionDataForChapter(StoryChapter chapter);
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_CHAPTER_MANAGER_HPP
