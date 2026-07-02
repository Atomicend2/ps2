/**
 * @file extended_combat.hpp
 * @brief Dynamic combat systems featuring Vow Arts, genetic Sigil modifiers, and DualShock 2 actuator stuttering.
 */

#ifndef SEVENTH_VOW_EXTENDED_COMBAT_HPP
#define SEVENTH_VOW_EXTENDED_COMBAT_HPP

#include <tyra.h>
#include <string>
#include <vector>
#include "vow_system.hpp"

namespace TheSeventhVow {

enum VowArtType {
    ART_SACRED_SLASH,
    ART_ASH_SHIELD,
    ART_WITNESS_STRIKE,
    ART_ECHO_PUNISHMENT
};

enum HereditarySigil {
    SIGIL_VALOR,       // Damage boost
    SIGIL_FRACTION,    // Increased critical multiplier but faster decay
    SIGIL_PALADIN,     // Guard threshold scaling
    SIGIL_NONE
};

struct VowArt {
    VowArtType type;
    std::string name;
    float baseDamagePower;
    float vowStrengthCost;
    int criticalScarThreshold;
};

class ExtendedCombat {
public:
    ExtendedCombat(Tyra::Engine* engine);
    ~ExtendedCombat();

    void init();

    /**
     * @brief Computes physical slash stats modifying for Sigil, Vow state, and active scars.
     */
    float computeAttackPower(const PlayerVow& vow, HereditarySigil sigil, VowArtType art);

    /**
     * @brief Execute physically punishing rumble actuators on DualShock 2.
     * Stutters asynchronously based on burdenScars threshold to translate bodily degradation.
     * @param padPort The physical port of the gamepad (normally 0 or 1)
     * @param scars Count of scars breaking down the physical body
     */
    void triggerDualShock2Rumble(int padPort, int scars);

    /**
     * @brief Helper to translate Sigil to text representation.
     */
    static const char* getSigilName(HereditarySigil sigil);

private:
    Tyra::Engine* engine;
    std::vector<VowArt> arts;

    void registerVowArts();
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_EXTENDED_COMBAT_HPP
