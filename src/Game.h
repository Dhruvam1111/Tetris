#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Tetromino.h"
#include "InputHandler.h"
#include <iostream>
#include <chrono>

// The Game class controls the entire game flow
class Game
{
public:
    Game();     // Constructor
    void run(); // Main function to start and manage the game

private:
    Board board;               // The game board
    Tetromino currentPiece;    // The currently falling piece
    InputHandler inputHandler; // Handles player input

    int score;        // Player's score
    int level;        // Current game level
    int linesCleared; // Total lines cleared so far
    int highScore;    // Highest score achieved in current session

    bool gameOver; // Flag for game-over state
    bool paused;   // Flag for pause state
    bool exitGame; // Flag to exit the game entirely

    // Core game functions
    void initialize();         // Initialize/reset game state
    void gameLoop();           // Main game loop
    void processInput();       // Handle player input
    void render();             // Draw the game to the screen
    void spawnPiece();         // Spawn a new tetromino
    void handlePieceLanding(); // Handle logic when piece lands
    void increaseLevel();      // Level progression logic

    // Utility display functions
    void showPauseScreen() const;    // Display pause message
    void waitForUnpause();           // Wait until player unpauses
    void showGameOverScreen() const; // Display game-over message
    bool promptRestart();            // Ask player if they want to restart
};

#endif
