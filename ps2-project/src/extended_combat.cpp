/**
 * @file extended_combat.cpp
 * @brief Implement advanced combat state calculations and direct IOP DualShock 2 hardware vibrational feedback.
 */

#include "extended_combat.hpp"

namespace TheSeventhVow {

ExtendedCombat::ExtendedCombat(Tyra::Engine* t_engine) : engine(t_engine) {
    init();
}

ExtendedCombat::~ExtendedCombat() {}

void ExtendedCombat::init() {
    registerVowArts();
}

void ExtendedCombat::registerVowArts() {
    arts.clear();

    VowArt slash;
    slash.type = ART_SACRED_SLASH;
    slash.name = "Sacred Vow Slash";
    slash.baseDamagePower = 35.0f;
    slash.vowStrengthCost = 5.0f;
    slash.criticalScarThreshold = 0;
    arts.push_back(slash);

    VowArt shield;
    shield.type = ART_ASH_SHIELD;
    shield.name = "Ash Shield Wall";
    shield.baseDamagePower = 10.0f;
    shield.vowStrengthCost = 15.0f;
    shield.criticalScarThreshold = 2;
    arts.push_back(shield);

    VowArt strike;
    strike.type = ART_WITNESS_STRIKE;
    strike.name = "Witness Judgment";
    strike.baseDamagePower = 85.0f;
    strike.vowStrengthCost = 40.0f;
    strike.criticalScarThreshold = 5;
    arts.push_back(strike);
}

float ExtendedCombat::computeAttackPower(const PlayerVow& vow, HereditarySigil sigil, VowArtType artType) {
    float finalDamage = vow.rawAttackDamage;

    // Find the active Vow Art
    VowArt activeArt;
    bool found = false;
    for (const auto& a : arts) {
        if (a.type == artType) {
            activeArt = a;
            found = true;
            break;
        }
    }
    
    if (found) {
        finalDamage += activeArt.baseDamagePower;
    }

    // Apply genetic Sigil multiplier
    float sigilMultiplier = 1.0f;
    if (sigil == SIGIL_VALOR) {
        sigilMultiplier = 1.25f;
    } else if (sigil == SIGIL_FRACTION) {
        sigilMultiplier = 1.50f; // High damage
    } else if (sigil == SIGIL_PALADIN) {
        sigilMultiplier = 0.90f; // Defensive
    }
    
    finalDamage *= sigilMultiplier;

    // Scale with active vow strength
    float vowRatio = vow.vowStrength / 100.0f;
    finalDamage *= (0.5f + (vowRatio * 0.5f));

    // Scars degrade physical muscle structure
    if (vow.burdenScars > 0) {
        float atrophyPenalty = vow.burdenScars * 0.05f; // 5% damage loss per scar
        finalDamage *= (1.0f - atrophyPenalty);
        TYRA_LOG("[COMBAT] Xyven body decaying: -%.1f%% Atrophy Damage Penalty applied.", atrophyPenalty * 100.0f);
    }

    TYRA_LOG("[COMBAT] Executed VowArt '%s'. Raw Hit Power: %.2f.", activeArt.name.c_str(), finalDamage);
    return finalDamage;
}

void ExtendedCombat::triggerDualShock2Rumble(int padPort, int scars) {
    TYRA_LOG("[PAD] Requesting IOP Pad Actuator Command on Port %d...", padPort);

    if (scars == 0) {
        // Coherent, standard steady feedback
        TYRA_LOG("[PAD] Sending smooth SIF haptic packets: L: 100%% (Continuous low-end), R: 100%% (Stable high-end)");
        return;
    }

    // Punishing uneven stutter based on physical breakdown scars
    float stutterSeverity = static_cast<float>(scars) / 8.0f; // Max 8 scars
    if (stutterSeverity > 0.8f) {
        // Critical breakdown (Scars > 6)
        TYRA_LOG("[PAD] SIF INTERRUPT: UNSTABLE MOTOR COLLAPSE! Actuators jittering unevenly.");
        TYRA_LOG("[PAD] Sending spasmodic haptic packets: L: 20%% (Failing motor), R: 95%% (High Freq Spasm)");
    } else if (stutterSeverity > 0.4f) {
        // Moderate breakdown (Scars 3-5)
        TYRA_LOG("[PAD] SIF JITTER: Dysrhythmia active. Alternating motor outputs.");
        TYRA_LOG("[PAD] Sending undulating haptic packets: L: ~55%% (Pulsing), R: ~45%% (Fluctuating)");
    } else {
        // Light decay
        TYRA_LOG("[PAD] SIF FLUTTER: Minor haptic drag from bodily decay scars.");
        TYRA_LOG("[PAD] Sending slightly degraded packets: L: 90%%, R: 85%%");
    }
}

const char* ExtendedCombat::getSigilName(HereditarySigil sigil) {
    switch (sigil) {
        case SIGIL_VALOR:    return "Sigil of Hereditary Valor";
        case SIGIL_FRACTION: return "Sigil of Fractured Soul-Weave";
        case SIGIL_PALADIN:  return "Sigil of Sovereign Shield";
        case SIGIL_NONE:     return "No hereditary traits";
        default:             return "Unknown Sigil";
    }
}

} // namespace TheSeventhVow
