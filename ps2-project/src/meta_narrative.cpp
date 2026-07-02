/**
 * @file meta_narrative.cpp
 * @brief Implements full 9-Act narrative game loop and Chapter 5 input lockout interrupts.
 */

#include "meta_narrative.hpp"

namespace TheSeventhVow {

MetaNarrative::MetaNarrative(Tyra::Engine* t_engine) 
    : engine(t_engine), currentAct(ACT_1_BELOVED_HEIR), isGlitching(false) {
    init();
}

MetaNarrative::~MetaNarrative() {}

void MetaNarrative::init() {
    setupActs();
}

void MetaNarrative::setupActs() {
    acts.clear();

    acts.push_back({ACT_1_BELOVED_HEIR, "Act I: The Beloved Heir", "Accept the Holy Scepter of Tyr.", false});
    acts.push_back({ACT_2_CROWN_AND_STAIN, "Act II: Crown and Stain", "Cleanse the first heretic den.", false});
    acts.push_back({ACT_3_SACRAMENT_DUTY, "Act III: Sacrament of Duty", "Escort the Oracle to Valen's Citadel.", false});
    acts.push_back({ACT_4_WHISPERS_OF_COIL, "Act IV: Whispers of the Coil", "Investigate the underground Spires.", false});
    acts.push_back({ACT_5_SPIRE_GLITCH, "Act V: Spires of Manipulation", "Confront Grand Cardinal Thorne.", true});
    acts.push_back({ACT_6_BETRAYAL_REVEAL, "Act VI: The Betrayal", "Discover Aevior's secrets.", false});
    acts.push_back({ACT_7_THE_HERETIC_RAGE, "Act VII: The Heretic's Rage", "Raze the Flayed Cathedrals.", false});
    acts.push_back({ACT_8_DEATH_OF_THE_FIRST, "Act VIII: Death of the First Oracle", "Defeat the celestial guardian.", false});
    acts.push_back({ACT_9_FINAL_ARC_SACRIFICE, "Act IX: The Final Arc Sacrifice", "Bind the final seventh vow.", false});
}

void MetaNarrative::progressAct() {
    int nextIdx = static_cast<int>(currentAct) + 1;
    if (nextIdx <= static_cast<int>(ACT_9_FINAL_ARC_SACRIFICE)) {
        currentAct = static_cast<StoryAct>(nextIdx);
        isGlitching = false;
        TYRA_LOG("[NARRATIVE] Progressing story to Act: %s", getActTitle(currentAct));
        TYRA_LOG("[NARRATIVE] Active Objective: %s", acts[nextIdx].primaryObjective.c_str());
    } else {
        TYRA_LOG("[NARRATIVE] All 9 Acts resolved. The Seventh Vow is bound. Ending execution cycle.");
    }
}

bool MetaNarrative::processDialogueChoiceInput(int requestedChoiceIndex) {
    // If we are in Act V / Spires of Manipulation (Chapter 5)
    if (currentAct == ACT_5_SPIRE_GLITCH) {
        isGlitching = true;
        
        TYRA_LOG("=====================================================================");
        TYRA_LOG(" [CRITICAL ERROR] CHRONOS OVERRIDE INTERRUPT LOADED ON SIF!");
        TYRA_LOG(" [IOP] pad_driver: Latching registers. Hard lock engaged.");
        TYRA_LOG(" [EE] dialogue_engine: BLOCKING CHOICE INPUT INDEX: %d", requestedChoiceIndex);
        TYRA_LOG(" [EE] dialogue_engine: REASON: IMMUTABLE MEMORY WITNESS POINT DETECTED.");
        TYRA_LOG(" [EE] SCRIPT PARSER: The history of Elyndra cannot be rewritten!");
        TYRA_LOG(" [GS] Applying full screen red overlay tint (VRAM addr 0x3F0000)...");
        TYRA_LOG("=====================================================================");

        return false; // Lockout input!
    }

    isGlitching = false;
    TYRA_LOG("[NARRATIVE] User chose option %d. Permitted by story module.", requestedChoiceIndex);
    return true;
}

const char* MetaNarrative::getActTitle(StoryAct act) {
    switch (act) {
        case ACT_1_BELOVED_HEIR:        return "Act I: The Beloved Heir";
        case ACT_2_CROWN_AND_STAIN:     return "Act II: Crown and Stain";
        case ACT_3_SACRAMENT_DUTY:      return "Act III: Sacrament of Duty";
        case ACT_4_WHISPERS_OF_COIL:    return "Act IV: Whispers of the Coil";
        case ACT_5_SPIRE_GLITCH:        return "Act V: Spires of Manipulation";
        case ACT_6_BETRAYAL_REVEAL:     return "Act VI: The Betrayal";
        case ACT_7_THE_HERETIC_RAGE:    return "Act VII: The Heretic's Rage";
        case ACT_8_DEATH_OF_THE_FIRST:  return "Act VIII: Death of the First Oracle";
        case ACT_9_FINAL_ARC_SACRIFICE: return "Act IX: The Final Arc Sacrifice";
        default:                        return "Unknown Act";
    }
}

} // namespace TheSeventhVow
