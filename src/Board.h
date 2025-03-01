#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"
#include <iostream>

// Board class represents the 10x20 game grid
class Board
{
public:
    static const int WIDTH = 10;  // Board width (fixed)
    static const int HEIGHT = 20; // Board height (fixed)

    Board(); // Constructor - initializes an empty board

    void clear();                                     // Clears the board (resetting to empty)
    void draw(const Tetromino &currentPiece) const;   // Draws the board with current falling piece
    bool movePiece(Tetromino &piece, int dx, int dy); // Attempts to move a piece, returns false if blocked
    void rotatePiece(Tetromino &piece);               // Attempts to rotate the piece
    void placePiece(const Tetromino &piece);          // Locks piece into the board when it lands
    int clearFullLines();                             // Clears fully filled lines and returns how many were cleared
    bool isCollision(const Tetromino &piece) const;   // Checks if piece collides with placed blocks

private:
    char grid[HEIGHT][WIDTH]; // The internal 10x20 grid to store placed pieces

    void drawBoard(const char grid[HEIGHT][WIDTH]) const; // Internal helper to render grid with borders/colors

#ifdef _WIN32
    static constexpr const char *RESET_COLOR = ""; // No color in Windows if ANSI not supported
    static constexpr const char *COLOR_I = "";
    static constexpr const char *COLOR_O = "";
    static constexpr const char *COLOR_T = "";
    static constexpr const char *COLOR_S = "";
    static constexpr const char *COLOR_Z = "";
    static constexpr const char *COLOR_J = "";
    static constexpr const char *COLOR_L = "";
    static constexpr const char *COLOR_FRAME = "";
    static constexpr const char *COLOR_EMPTY = "";
#else
    // ANSI color codes for Linux/macOS
    static constexpr const char *RESET_COLOR = "\033[0m";
    static constexpr const char *COLOR_I = "\033[36m";
    static constexpr const char *COLOR_O = "\033[33m";
    static constexpr const char *COLOR_T = "\033[35m";
    static constexpr const char *COLOR_S = "\033[32m";
    static constexpr const char *COLOR_Z = "\033[31m";
    static constexpr const char *COLOR_J = "\033[34m";
    static constexpr const char *COLOR_L = "\033[91m";
    static constexpr const char *COLOR_FRAME = "\033[37m"; // White frame
    static constexpr const char *COLOR_EMPTY = "\033[90m"; // Gray empty cells
#endif
};

#endif
