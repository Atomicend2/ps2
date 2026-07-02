/**
 * @file vow_system.cpp
 * @brief Implementation of Xyven's vow power-scaling and physical toll algorithms
 */

#include "vow_system.hpp"

namespace TheSeventhVow {

void VowSystem::processXyvenVowAction(PlayerVow& vow, bool allySaved) {
    if (allySaved) {
        // Boost vow powers
        vow.vowStrength += 25.0f;
        vow.rawAttackDamage += 15.0f;
        
        // Take physical toll - increment scars and permanently reduce max health modifier by 5%
        vow.burdenScars += 1;
        vow.maxHealthModifier -= 0.05f;
        if (vow.maxHealthModifier < 0.10f) {
            vow.maxHealthModifier = 0.10f; // Limit minimum multiplier to 10%
        }

        // Determine spiritual transformation state based on burden scars
        EchoState oldState = vow.soulState;
        if (vow.burdenScars == 0) {
            vow.soulState = HUMAN;
        } else if (vow.burdenScars > 0 && vow.burdenScars <= 5) {
            vow.soulState = FRACTURED;
        } else {
            vow.soulState = ECHO;
        }

        // Log actions to Emotion Engine standard console output
        TYRA_LOG("=======================================================");
        TYRA_LOG(" [VOW SYSTEM] Action processed: Ally Saved!");
        TYRA_LOG(" [VOW SYSTEM] Vow Strength: %.2f (+25.0)", vow.vowStrength);
        TYRA_LOG(" [VOW SYSTEM] Raw Attack Damage: %.2f (+15.0)", vow.rawAttackDamage);
        TYRA_LOG(" [VOW SYSTEM] Burden Scars: %d (Incremented)", vow.burdenScars);
        TYRA_LOG(" [VOW SYSTEM] Max Health Modifier: %.2f (-5%% permanent degradation)", vow.maxHealthModifier);
        
        if (vow.soulState != oldState) {
            TYRA_LOG(" [VOW SYSTEM] WARNING: Soul transformed from [%s] to [%s]!", 
                     getSoulStateName(oldState), getSoulStateName(vow.soulState));
        }
        TYRA_LOG("=======================================================");
    } else {
        TYRA_LOG("[VOW SYSTEM] Action processed: Minor conflict updated.");
    }
}

const char* VowSystem::getVowName(VowType type) {
    switch (type) {
        case TYR_PROTECTION: return "Tyr's Protection";
        case VALEN_JUSTICE:  return "Valen's Justice";
        case KARA_VALOR:     return "Kara's Valor";
        case ZAL_SACRIFICE:  return "Zal's Sacrifice";
        default:             return "Unknown Vow";
    }
}

const char* VowSystem::getSoulStateName(EchoState state) {
    switch (state) {
        case HUMAN:     return "HUMAN (Pure)";
        case FRACTURED: return "FRACTURED (Degrading)";
        case ECHO:      return "ECHO (Phantasmal/Vessel)";
        default:        return "Unknown State";
    }
}

} // namespace TheSeventhVow
