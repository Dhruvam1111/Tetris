#include "Game.h"
#include <iostream>
#include <algorithm>
#include <ctime>

// Platform-specific screen clearing and sleep functions
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

// Constructor - initialize game state and prepare first piece
Game::Game() : score(0), level(1), linesCleared(0), highScore(0),
               gameOver(false), paused(false), exitGame(false),
               currentPiece(Tetromino::getRandomPiece()) {}

// Main function - runs the entire game lifecycle
void Game::run()
{
    srand(time(nullptr)); // Seed random generator
    while (!exitGame)
    {
        initialize();         // Set up game state for new game
        gameLoop();           // Main gameplay loop
        showGameOverScreen(); // Show final score
        if (!promptRestart())
            break; // Ask if player wants to restart
    }
}

// Reset all gameplay variables for a fresh game
void Game::initialize()
{
    board.clear();
    spawnPiece(); // Start with first piece
    score = 0;
    level = 1;
    linesCleared = 0;
    gameOver = false;
    paused = false;
}

// Main gameplay loop - runs until game over
void Game::gameLoop()
{
    int frameCounter = 0;
    const int baseGravityInterval = 6; // Controls natural fall speed (lower = faster)

    while (!gameOver)
    {
        processInput(); // Read and handle all player input

        if (paused)
        { // Handle paused state (skip updates/render)
            showPauseScreen();
            waitForUnpause();
            continue;
        }

        // Apply gravity at regular intervals (depends on level)
        if (frameCounter % std::max(1, (baseGravityInterval - level)) == 0)
        {
            if (!board.movePiece(currentPiece, 0, 1))
            {                         // Try moving down
                handlePieceLanding(); // Piece lands if blocked
                spawnPiece();         // New piece starts falling
                if (board.isCollision(currentPiece))
                { // Collision immediately = game over
                    gameOver = true;
                }
            }
        }

        render();     // Redraw game state
        SLEEP_MS(20); // Control game speed (50 FPS target)
        frameCounter++;
    }
}

// Process all player input (movement, rotation, pause, etc.)
void Game::processInput()
{
    inputHandler.update(); // Poll all keys

    if (inputHandler.quitPressed())
    { // Quit game if 'q' pressed
        gameOver = true;
        exitGame = true;
    }

    if (inputHandler.pausePressed())
    { // Pause or resume if 'p' pressed
        paused = !paused;
    }

    if (paused)
        return; // Skip all movement processing when paused

    // Handle movement and rotation based on pressed or held keys
    if (inputHandler.leftPressed() || inputHandler.leftHeld())
    {
        board.movePiece(currentPiece, -1, 0); // Move left
    }

    if (inputHandler.rightPressed() || inputHandler.rightHeld())
    {
        board.movePiece(currentPiece, 1, 0); // Move right
    }

    if (inputHandler.downPressed() || inputHandler.downHeld())
    {
        board.movePiece(currentPiece, 0, 1); // Soft drop
    }

    if (inputHandler.rotatePressed())
    {
        board.rotatePiece(currentPiece); // Rotate piece
    }

    if (inputHandler.hardDropPressed())
    { // Hard drop (instantly falls to bottom)
        while (board.movePiece(currentPiece, 0, 1))
            ;
        handlePieceLanding();
        spawnPiece();
    }
}

// Clears screen and displays current score, level, and board
void Game::render()
{
    system(CLEAR_SCREEN);
    std::cout << "Score: " << score << " | Level: " << level << " | High Score: " << highScore << "\n";
    board.draw(currentPiece); // Draw current board and falling piece
}

// Spawns a new random piece at starting position (top-center)
void Game::spawnPiece()
{
    currentPiece = Tetromino::getRandomPiece();
    currentPiece.setPosition(4, 0);
}

// Handles logic when a piece lands (scoring, clearing lines, leveling up)
void Game::handlePieceLanding()
{
    board.placePiece(currentPiece);         // Lock piece into grid
    int lines = board.clearFullLines();     // Clear any full rows
    linesCleared += lines;                  // Track cleared lines
    score += lines * 100;                   // Score 100 points per line
    increaseLevel();                        // Check for level-up
    highScore = std::max(highScore, score); // Track high score
}

// Increases level after every 3 cleared lines
void Game::increaseLevel()
{
    if (linesCleared >= level * 3)
    {
        level++;
        std::cout << "Level Up! Now at Level " << level << "\n";
        SLEEP_MS(500); // Brief pause to show message
    }
}

// Displays pause message
void Game::showPauseScreen() const
{
    std::cout << "\n** Paused - Press P to Resume **\n";
}

// Loops until player presses 'p' again to unpause
void Game::waitForUnpause()
{
    while (true)
    {
        inputHandler.update();
        if (inputHandler.pausePressed())
        {
            paused = false;
            break;
        }
        SLEEP_MS(50); // Short delay to avoid busy loop
    }
}

// Displays game over message with final score and high score
void Game::showGameOverScreen() const
{
    std::cout << "\nGame Over! Final Score: " << score << "\n";
    std::cout << "High Score: " << highScore << "\n";
}

// Asks player if they want to restart or quit
bool Game::promptRestart()
{
    std::cout << "Press R to Restart or Q to Quit: ";
    char choice;
    std::cin >> choice;
    if (choice == 'Q' || choice == 'q')
        exitGame = true;
    return choice == 'R' || choice == 'r';
}
