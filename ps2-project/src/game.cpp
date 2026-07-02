/**
 * @file game.cpp
 * @brief Game logic and rendering implementation for 'The Seventh Vow'
 * @details Implements DualShock 2 controls, audio setup, and render passes.
 */

#include "game.hpp"

namespace TheSeventhVow {

Game::Game(Tyra::Engine* t_engine) 
    : engine(t_engine), chapterManager(t_engine), dialogueEngine(t_engine) {
    currentState = GameState::Gameplay; // Jump directly to gameplay for direct interaction
    fpsCounter = 0;
    fpsTimer = 0.0f;
    playerPos.set(0.0f, 0.0f, 0.0f, 1.0f);
}

Game::~Game() {
    // Clean up allocated assets (textures, models, audio streams)
    TYRA_LOG("'The Seventh Vow' shutdown complete. Tyra deallocated.");
}

void Game::init() {
    TYRA_LOG("Initializing Game Subsystems for 'The Seventh Vow'...");

    // Initialize Pad / Controller subsystem
    // Tyra provides a built-in PAD driver to poll DualShock 2 controllers
    engine->pad.init();

    // Initialize Audio subsystem
    // Set up standard audsrv channels for background streams and SFX
    engine->audio.init();

    // Set light directions and ambient values for the 3D scene
    // Tyra supports directional lighting with up to 3 active light sources
    engine->renderer.renderer3D.utility.setLightAmbient(0.15f, 0.15f, 0.15f);

    // Initialize Core Gameplay Camera and Vow States
    camera.init();
    chapterManager.init();
    dialogueEngine.init();

    TYRA_LOG("[INIT] Camera loaded. Target orbit distance: %.1f", camera.getDistance());
    TYRA_LOG("[INIT] Vow status: %s | State: %s", 
             VowSystem::getVowName(playerVow.activeVow), 
             VowSystem::getSoulStateName(playerVow.soulState));

    TYRA_LOG("All PS2 subsystems successfully initialized. Enjoy the game!");
}

void Game::loop() {
    // 1. Calculate delta time (time elapsed since last frame in seconds)
    // Tyra's clock class tracks performance-counter accurate time delta
    float deltaTime = engine->info.getDeltaTime();

    // Track FPS
    fpsCounter++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0f) {
        TYRA_LOG("PS2 FPS: %u | Draw Calls: %u", fpsCounter, engine->renderer.getDrawCallsCount());
        fpsCounter = 0;
        fpsTimer = 0.0f;
    }

    // 2. Poll user inputs
    handleInput();

    // 3. Update game mechanics & animations
    updatePhysics(deltaTime);

    // 4. Draw graphics to the Graphics Synthesizer (GS) VRAM
    renderScene();
}

void Game::handleInput() {
    // Poll active pads from Tyra
    auto& pads = engine->pad.getClickedPads();
    
    float rx = 0.0f;
    float ry = 0.0f;
    float deltaTime = engine->info.getDeltaTime();

    bool dialogueMode = dialogueEngine.isDialogueActive();
    bool cutsceneActive = chapterManager.isCutsceneActive();

    for (auto& pad : pads) {
        // Read Right Analog Stick values: values return in range [0, 255] (128 is neutral/centered)
        float rightJoyX = (static_cast<float>(pad.getRightJoyX()) - 128.0f) / 128.0f;
        float rightJoyY = (static_cast<float>(pad.getRightJoyY()) - 128.0f) / 128.0f;

        // Apply deadzone threshold (15% filter) to prevent analog drift
        if (std::abs(rightJoyX) > 0.15f) rx = rightJoyX;
        if (std::abs(rightJoyY) > 0.15f) ry = rightJoyY;

        if (pad.isClicked(Tyra::Button::Start)) {
            TYRA_LOG("START pressed. Toggling pause state.");
        }

        // Triangle: Test Chapter Progression & trigger chapter-specific dialogues
        if (pad.isClicked(Tyra::Button::Triangle)) {
            chapterManager.nextChapter();
            DialogueNode node;
            switch (chapterManager.getCurrentChapter()) {
                case CHAPTER_1_HOLY_WAR:
                    node = { "Valerius Priest", "Xyven, do you swear to protect the Cathedral and sacrifice your blood?", "Yes, on my honor.", "Is this merely a cage?" };
                    break;
                case CHAPTER_2_MILITARY_RANKS:
                    node = { "General Vance", "Obey. Order your squad to hold the line at all costs (Wrath).", "I will shield my squad.", "Tactical retreat is wiser." };
                    break;
                case CHAPTER_3_DARK_ORIGINS:
                    node = { "Ancient Echo", "The vows are a fracture of your soul. Do you accept the scar?", "I accept the scar.", "Is there no other way?" };
                    break;
                case CHAPTER_4_WHISPERING_EXPERIMENTATION:
                    node = { "Inquisitor Malakor", "We extract their vows. This is holy mercy, Xyven!", "Stop this horror!", "Are we any different?" };
                    break;
                case CHAPTER_5_SPIRES_OF_MANIPULATION:
                    node = { "Lady Lys", "Your brother is molded into a sacrifice. Will you save him?", "I will burn this kingdom!", "I will find another way." };
                    break;
                case CHAPTER_6_THE_BETRAYAL:
                    node = { "Aevior (Brother)", "Xyven, stop! I must complete the ritual. Why don't you trust me?", "Because they are using you!", "If you choose them, we clash!" };
                    break;
                case CHAPTER_7_THE_TYRANT:
                    node = { "The Tyrant God-Mind", "The ritual requires an anchor. Submit and sacrifice the vessel!", "Sacrifice her (Canon).", "Refuse and fight!" };
                    break;
            }
            dialogueEngine.setActiveNode(node);
        }

        if (dialogueMode) {
            // Dialogue option selection: Cross selects Option A, Circle selects Option B
            if (pad.isClicked(Tyra::Button::Cross)) {
                dialogueEngine.processPlayerChoice(0, chapterManager.getCurrentChapter());
                if (chapterManager.getCurrentChapter() != CHAPTER_7_THE_TYRANT) {
                    chapterManager.setCutsceneActive(false); // Dismiss cutscene lock
                }
            }
            if (pad.isClicked(Tyra::Button::Circle)) {
                dialogueEngine.processPlayerChoice(1, chapterManager.getCurrentChapter());
                if (chapterManager.getCurrentChapter() != CHAPTER_7_THE_TYRANT) {
                    chapterManager.setCutsceneActive(false); // Dismiss cutscene lock
                }
            }
            // Press Square to dismiss Chapter 7 tragic choice witness mode
            if (pad.isClicked(Tyra::Button::Square) && chapterManager.getCurrentChapter() == CHAPTER_7_THE_TYRANT) {
                TYRA_LOG("[SYS] Releasing Witness Mode control lock.");
                dialogueEngine.closeDialogue();
                chapterManager.setCutsceneActive(false);
            }
        } else {
            // Standard Gameplay Input block
            if (cutsceneActive) {
                TYRA_LOG("[INPUT LOCK] Controls locked during Chapter Cutscene. Press Triangle/Square to interact.");
                if (pad.isClicked(Tyra::Button::Square)) {
                    TYRA_LOG("[INPUT] Square pressed: Skipping active cutscene.");
                    chapterManager.setCutsceneActive(false);
                }
            } else {
                if (pad.isClicked(Tyra::Button::Cross)) {
                    TYRA_LOG("[INPUT] Cross pressed: Executing heroic protection - Ally Saved!");
                    // Execute vow system calculations with an ally saved action
                    VowSystem::processXyvenVowAction(playerVow, true);
                }

                if (pad.isClicked(Tyra::Button::Circle)) {
                    // Cycle through available vows for testability
                    int nextVowInt = (static_cast<int>(playerVow.activeVow) + 1) % 4;
                    playerVow.activeVow = static_cast<VowType>(nextVowInt);
                    TYRA_LOG("[INPUT] Circle pressed: Cycle Vows. Active Vow set to: %s", 
                             VowSystem::getVowName(playerVow.activeVow));
                }
            }
        }
    }

    // Update camera orbital mathematics (slow cinematic orbit during cutscene, active orbit during gameplay)
    if (cutsceneActive) {
        camera.update(0.12f, 0.0f, playerPos, deltaTime);
    } else {
        camera.update(rx, ry, playerPos, deltaTime);
    }
}

void Game::updatePhysics(float deltaTime) {
    dialogueEngine.update(deltaTime);

    switch (currentState) {
        case GameState::Intro:
            // Update camera panning animations
            break;
        case GameState::Gameplay:
            // Update player positions, animations, enemy AI behavior
            break;
        default:
            break;
    }
}

void Game::renderScene() {
    // Begin frame rendering. Clears framebuffers and sets up draw registers.
    engine->renderer.beginFrame();

    // Render 3D and 2D elements depending on game state
    switch (currentState) {
        case GameState::Intro:
            // Render beautiful Title Logo
            break;
        case GameState::Gameplay:
            // Render 3D meshes (Level geometry, Player model, Enemies)
            // Tyra uses standard rendering pipelines (3D static, 3D animated, 2D sprites)
            
            // Render cinematic subtitles layer on top of gameplay scene
            dialogueEngine.render(chapterManager.getCurrentChapter());
            break;
        default:
            break;
    }

    // Finalize rendering. Swaps page buffers (v-sync) and pushes vertices to GS.
    engine->renderer.endFrame();
}

} // namespace TheSeventhVow
