#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>

// Tetromino class represents a Tetris piece (shape, position, rotation)
class Tetromino
{
public:
    // Different types of Tetromino pieces
    enum Type
    {
        I,
        O,
        T,
        S,
        Z,
        J,
        L
    };

    Tetromino(Type type); // Constructor - creates a piece of given type

    static Tetromino getRandomPiece(); // Static function to generate a random piece

    // Movement and rotation
    void move(int dx, int dy);      // Move horizontally or vertically
    void rotate();                  // Rotate 90 degrees clockwise
    void rotateBack();              // Undo rotation (90 degrees counter-clockwise)
    void setPosition(int x, int y); // Set initial position (usually at top-center)

    // Drawing and collision handling
    void draw(char grid[20][10]) const;               // Draw piece onto the given grid
    void placeOnBoard(char grid[20][10]) const;       // Permanently place the piece
    bool collidesWith(const char grid[20][10]) const; // Check if it overlaps with existing blocks

private:
    Type type;    // Type of the piece (I, O, T, etc.)
    int x, y;     // Current position on the board
    int rotation; // Current rotation (0, 1, 2, 3)

    // Shape definitions (each type has 4 rotations)
    static const std::vector<std::vector<std::vector<std::pair<int, int>>>> shapes;

    // Character used to represent each piece type on the board
    static const char pieceChars[7];
};

#endif
