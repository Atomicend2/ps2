/**
 * @file meta_narrative.hpp
 * @brief Complete 9-Act story event loop, and immutable choice memory lockout engine (Chapter 5 override).
 */

#ifndef SEVENTH_VOW_META_NARRATIVE_HPP
#define SEVENTH_VOW_META_NARRATIVE_HPP

#include <tyra>
#include <string>
#include <vector>

namespace TheSeventhVow {

enum StoryAct {
    ACT_1_BELOVED_HEIR,
    ACT_2_CROWN_AND_STAIN,
    ACT_3_SACRAMENT_DUTY,
    ACT_4_WHISPERS_OF_COIL,
    ACT_5_SPIRE_GLITCH,      // Immutable lockout point
    ACT_6_BETRAYAL_REVEAL,
    ACT_7_THE_HERETIC_RAGE,
    ACT_8_DEATH_OF_THE_FIRST,
    ACT_9_FINAL_ARC_SACRIFICE
};

struct ActMetadata {
    StoryAct act;
    std::string title;
    std::string primaryObjective;
    bool holdsImmutableWitnessPoint;
};

class MetaNarrative {
public:
    MetaNarrative(Tyra::Engine* engine);
    ~MetaNarrative();

    void init();

    /**
     * @brief Steps the game loop forward to the next story act.
     */
    void progressAct();

    /**
     * @brief Processes controller input polling during crucial dialogue points.
     * Flags and blocks user choices if they occur during Chapter 5's memory lock override.
     * @param requestedChoiceIndex The option the user pressed (e.g. 0 or 1)
     * @return True if input was allowed, False if locked out by the SIF Chronos Override.
     */
    bool processDialogueChoiceInput(int requestedChoiceIndex);

    // Getters / Setters
    StoryAct getCurrentAct() const { return currentAct; }
    bool isGlitchActive() const { return isGlitching; }

    static const char* getActTitle(StoryAct act);

private:
    Tyra::Engine* engine;
    StoryAct currentAct;
    std::vector<ActMetadata> acts;
    bool isGlitching;

    void setupActs();
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_META_NARRATIVE_HPP
