#include "Tetromino.h"
#include <cstdlib>

// Shape definitions for each piece and all 4 rotations
const std::vector<std::vector<std::vector<std::pair<int, int>>>> Tetromino::shapes = {
    {// I-piece (line)
     {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
     {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
     {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
     {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
    {// O-piece (square)
     {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
     {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
     {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
     {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
    {// T-piece
     {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
     {{1, 0}, {0, 1}, {1, 1}, {1, 2}}},
    {// S-piece
     {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 1}, {2, 1}, {0, 2}, {1, 2}},
     {{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
    {// Z-piece
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     {{2, 0}, {1, 1}, {2, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
     {{1, 0}, {0, 1}, {1, 1}, {0, 2}}},
    {// J-piece
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {0, 2}, {1, 2}}},
    {// L-piece
     {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
     {{0, 0}, {1, 0}, {1, 1}, {1, 2}}}};

// Characters used to represent each piece type (linked to color in Board.cpp)
const char Tetromino::pieceChars[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

// Constructor - assigns type and starts at (4,0) near the top center
Tetromino::Tetromino(Type type) : type(type), x(4), y(0), rotation(0) {}

// Generates a random tetromino
Tetromino Tetromino::getRandomPiece()
{
    return Tetromino(static_cast<Type>(std::rand() % 7));
}

// Move the piece horizontally or vertically
void Tetromino::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

// Rotate 90 degrees clockwise
void Tetromino::rotate()
{
    rotation = (rotation + 1) % 4;
}

// Rotate back (90 degrees counter-clockwise)
void Tetromino::rotateBack()
{
    rotation = (rotation + 3) % 4;
}

// Set piece position directly (used when spawning)
void Tetromino::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

// Draw piece into a temporary grid (for rendering the board)
void Tetromino::draw(char grid[20][10]) const
{
    char pieceChar = pieceChars[type];
    for (const auto &cell : shapes[type][rotation])
    {
        int drawX = x + cell.first;
        int drawY = y + cell.second;
        if (drawX >= 0 && drawX < 10 && drawY >= 0 && drawY < 20)
        {
            grid[drawY][drawX] = pieceChar;
        }
    }
}

// Place piece into permanent grid (after landing)
void Tetromino::placeOnBoard(char grid[20][10]) const
{
    draw(grid);
}

// Check if piece collides with walls, floor, or existing blocks
bool Tetromino::collidesWith(const char grid[20][10]) const
{
    for (const auto &cell : shapes[type][rotation])
    {
        int checkX = x + cell.first;
        int checkY = y + cell.second;
        if (checkX < 0 || checkX >= 10 || checkY >= 20 || (checkY >= 0 && grid[checkY][checkX] != ' '))
        {
            return true;
        }
    }
    return false;
}
