/**
 * @file main.cpp
 * @brief Entry point for 'The Seventh Vow', a 3D Action RPG for PlayStation 2
 * @details Implemented using the open-source Tyra Engine.
 * 
 * © 2026 The Seventh Vow Development Team. All rights reserved.
 */

#include <tyra>
#include "game.hpp"

int main(int argc, char* argv[]) {
    // Enable debug logging for Tyra Engine
    // Tyra includes a built-in logger that prints to standard PS2 stdout (ps2client/ps2link)
    TYRA_LOG("Starting 'The Seventh Vow' on PlayStation 2...");

    // Configure engine startup options
    Tyra::EngineOptions options;
    options.vmode = Tyra::Vmode::NTSC;  // High-performance 60Hz NTSC mode
    options.width = 640;               // Standard PS2 horizontal resolution
    options.height = 448;              // NTSC interlaced vertical resolution
    options.audio_frequency = 44100;   // CD-quality sound output (44.1 kHz)
    
    // Instantiate Tyra Engine with custom configurations
    Tyra::Engine engine;
    
    // Create game instance, passing a pointer to the initialized engine
    TheSeventhVow::Game game(&engine);

    // Initialize and run the main game loop
    // engine.run() internally calls game.init() once, then loops game.loop() every frame
    engine.run(&game);

    return 0;
}
