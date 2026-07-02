/**
 * @file game.hpp
 * @brief Primary Game class for 'The Seventh Vow'
 * @details Declares core game lifecycle, state machine, and engine systems.
 */

#ifndef SEVENTH_VOW_GAME_HPP
#define SEVENTH_VOW_GAME_HPP

#include <tyra>
#include "vow_system.hpp"
#include "camera.hpp"
#include "chapter_manager.hpp"
#include "dialogue_engine.hpp"

namespace TheSeventhVow {

class Game : public Tyra::Game {
public:
    /**
     * @brief Constructor for 'The Seventh Vow' Game Class
     * @param t_engine Pointer to the running Tyra Engine instance
     */
    Game(Tyra::Engine* t_engine);
    
    /**
     * @brief Destructor, handles resource deallocation on exit
     */
    ~Game();

    /**
     * @brief Called once by the engine during startup. Handles asset preloading, 
     *        lighting setups, pad configurations, and rendering systems.
     */
    void init() override;

    /**
     * @brief Called once per frame. Handles player controller polling, 
     *        physics/collision update, camera movement, and drawing commands.
     */
    void loop() override;

private:
    Tyra::Engine* engine;

    // Core Game States
    enum class GameState {
        Intro,
        MainMenu,
        Gameplay,
        GameOver
    };
    GameState currentState;

    // Subsystem helper functions
    void handleInput();
    void updatePhysics(float deltaTime);
    void renderScene();

    // Diagnostics / Frame Rate Counter
    u32 fpsCounter;
    float fpsTimer;

    // Core Gameplay Systems
    Camera camera;
    PlayerVow playerVow;
    Tyra::Vec4 playerPos;
    ChapterManager chapterManager;
    DialogueEngine dialogueEngine;
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_GAME_HPP
