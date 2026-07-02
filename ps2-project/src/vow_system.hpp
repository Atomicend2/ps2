/**
 * @file vow_system.hpp
 * @brief Core vow mechanics and Xyven's burden systems for 'The Seventh Vow'
 */

#ifndef SEVENTH_VOW_VOW_SYSTEM_HPP
#define SEVENTH_VOW_VOW_SYSTEM_HPP

#include <tyra>

namespace TheSeventhVow {

/**
 * @brief Represents the types of sacred vows a player can bind.
 */
enum VowType {
    TYR_PROTECTION,
    VALEN_JUSTICE,
    KARA_VALOR,
    ZAL_SACRIFICE
};

/**
 * @brief Represents the spiritual state of Xyven's soul as it fractures under burden.
 */
enum EchoState {
    HUMAN,
    FRACTURED,
    ECHO
};

/**
 * @brief Tracking structure for a character's active vow, power scaling, and body degradation.
 */
struct PlayerVow {
    VowType activeVow;
    EchoState soulState;
    float vowStrength;
    int burdenScars;
    float maxHealthModifier;
    float rawAttackDamage;

    // Default constructor
    PlayerVow() 
        : activeVow(TYR_PROTECTION),
          soulState(HUMAN),
          vowStrength(100.0f),
          burdenScars(0),
          maxHealthModifier(1.0f),
          rawAttackDamage(25.0f) {}
};

/**
 * @brief Processor class managing vows and their progression.
 */
class VowSystem {
public:
    /**
     * @brief Process a vow-breaking action or heroic deed when saving an ally.
     * @param vow The player's current vow state to modify.
     * @param allySaved True if an ally was rescued in combat, scaling raw stats.
     */
    static void processXyvenVowAction(PlayerVow& vow, bool allySaved);

    /**
     * @brief Helper to translate a VowType enum to a string.
     */
    static const char* getVowName(VowType type);

    /**
     * @brief Helper to translate an EchoState enum to a string.
     */
    static const char* getSoulStateName(EchoState state);
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_VOW_SYSTEM_HPP
