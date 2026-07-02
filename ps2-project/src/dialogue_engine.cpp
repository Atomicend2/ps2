/**
 * @file dialogue_engine.cpp
 * @brief Implementing dialogue box subroutines, glitch rendering, and tragic overrides
 */

#include "dialogue_engine.hpp"

namespace TheSeventhVow {

DialogueEngine::DialogueEngine(Tyra::Engine* t_engine) 
    : engine(t_engine), active(false), glitchIndicator(false), glitchTimer(0.0f) {
    // Load a default introductory dialogue
    currentNode = {
        "Paladin Commander",
        "We strike the border at sunrise. Xyven, is your vow of protection ready?",
        "Yes, I will shield all.",
        "Perhaps we should wait."
    };
}

DialogueEngine::~DialogueEngine() {}

void DialogueEngine::init() {
    active = true;
    glitchIndicator = false;
    glitchTimer = 0.0f;
}

void DialogueEngine::update(float deltaTime) {
    if (glitchIndicator) {
        glitchTimer -= deltaTime;
        if (glitchTimer <= 0.0f) {
            glitchIndicator = false;
        }
    }
}

void DialogueEngine::setActiveNode(const DialogueNode& node) {
    currentNode = node;
    active = true;
}

void DialogueEngine::processPlayerChoice(int selectedOption, StoryChapter currentChapter) {
    if (!active) return;

    if (currentChapter == CHAPTER_7_THE_TYRANT) {
        // Red visual glitch triggered
        glitchIndicator = true;
        glitchTimer = 2.0f;

        // CRITICAL: Force Xyven's tragic canon destiny regardless of chosen input option
        TYRA_LOG(" [SYS] D-Pad/Cross press captured. Evaluation vector triggered...");
        TYRA_LOG("=======================================================");
        TYRA_LOG(" SYSTEM WARNING: Witness Mode Active. Timeline Immutable.");
        TYRA_LOG("=======================================================");
        
        // Force Option A: "Tragic Sacrifice" even if they chose Option B
        TYRA_LOG(" [NARRATIVE] Choice overridden! Input %d replaced with CANON_DESTINY.", selectedOption);
        TYRA_LOG(" [XYVEN] 'I have no choice... I must strike down the vessel to fulfill the Seventh Vow.'");
        TYRA_LOG(" [SYS] Soul resonance critical. Zero possibilities remain.");
    } else {
        // Normal progression
        TYRA_LOG(" [NARRATIVE] Player choice evaluated successfully: %s", 
                 (selectedOption == 0) ? currentNode.choiceA : currentNode.choiceB);
        active = false; // Close dialogue after choice in normal chapters
    }
}

void DialogueEngine::render(StoryChapter currentChapter) {
    if (!active) return;

    // Use Tyra's logging system to reflect the active subtitles and rendering state
    static int frameCounter = 0;
    frameCounter++;

    if (frameCounter % 60 == 0) {
        if (glitchIndicator) {
            TYRA_LOG(" [GS RENDER] GLITCH ACTIVE - Rendering Lower-Third Dialogue Box in High-Contrast RED!");
        } else {
            TYRA_LOG(" [GS RENDER] Rendering Subtitles: [%s]: \"%s\"", currentNode.speaker, currentNode.line);
            if (currentNode.choiceA && currentNode.choiceB) {
                TYRA_LOG(" [GS RENDER] Rendering Choices: [A] %s | [B] %s", currentNode.choiceA, currentNode.choiceB);
            }
        }
    }

    // Call simulated 2D sprite shaders and fonts
    drawCinematicSubtitles(currentNode.speaker, currentNode.line);
    if (currentNode.choiceA && currentNode.choiceB) {
        drawChoiceBox(currentNode.choiceA, currentNode.choiceB);
    }
}

void DialogueEngine::drawCinematicSubtitles(const char* speaker, const char* text) {
    // In real Tyra, this maps to coordinates on a 640x448 screen (lower third)
    // Subtitle box dimensions: X: 40, Y: 320, W: 560, H: 100
    // Text drawing operations on standard Font2D layer
}

void DialogueEngine::drawChoiceBox(const char* choiceA, const char* choiceB) {
    // Draw selectable choice box overlayed on the upper right side of subtitles
}

} // namespace TheSeventhVow
