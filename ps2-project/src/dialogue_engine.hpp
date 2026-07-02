/**
 * @file dialogue_engine.hpp
 * @brief Cinematic dialogue engine with 'Illusion of Choice' override logic for the PS2
 */

#ifndef SEVENTH_VOW_DIALOGUE_ENGINE_HPP
#define SEVENTH_VOW_DIALOGUE_ENGINE_HPP

#include <tyra>
#include "chapter_manager.hpp"

namespace TheSeventhVow {

struct DialogueNode {
    const char* speaker;
    const char* line;
    const char* choiceA;
    const char* choiceB;
};

class DialogueEngine {
public:
    DialogueEngine(Tyra::Engine* engine);
    ~DialogueEngine();

    /**
     * @brief Initialize dialogue arrays and state
     */
    void init();

    /**
     * @brief Render subtitle box and current options on the lower third of the screen
     */
    void render(StoryChapter currentChapter);

    /**
     * @brief Set active line node based on story events
     */
    void setActiveNode(const DialogueNode& node);

    /**
     * @brief Intercept player choices, overriding during Chapter 5
     * @param selectedOption 0 for Option A, 1 for Option B
     * @param currentChapter The current chapter context from ChapterManager
     */
    void processPlayerChoice(int selectedOption, StoryChapter currentChapter);

    // Getters and status
    bool isDialogueActive() const { return active; }
    void startDialogue() { active = true; }
    void closeDialogue() { active = false; }
    bool isGlitchIndicatorActive() const { return glitchIndicator; }
    void update(float deltaTime);

private:
    Tyra::Engine* engine;
    DialogueNode currentNode;
    bool active;
    bool glitchIndicator;
    float glitchTimer;

    // Simulated font and sprite rendering helper
    void drawCinematicSubtitles(const char* speaker, const char* text);
    void drawChoiceBox(const char* choiceA, const char* choiceB);
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_DIALOGUE_ENGINE_HPP
