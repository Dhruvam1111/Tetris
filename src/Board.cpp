#include "Board.h"
#include <iostream>

// Constructor - initializes the board to empty
Board::Board()
{
    clear();
}

// Clears the entire board (sets all cells to empty)
void Board::clear()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            grid[y][x] = ' '; // Empty cell
        }
    }
}

// Draws the current game board along with the active falling piece
void Board::draw(const Tetromino &piece) const
{
    char tempGrid[HEIGHT][WIDTH];

    // Copy the current board into tempGrid
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            tempGrid[y][x] = grid[y][x];
        }
    }

    // Overlay the falling piece onto the tempGrid
    piece.draw(tempGrid);

    // Render the combined grid (board + piece)
    drawBoard(tempGrid);
}

// Moves a piece if possible, returning false if blocked
bool Board::movePiece(Tetromino &piece, int dx, int dy)
{
    piece.move(dx, dy);
    if (isCollision(piece))
    {
        piece.move(-dx, -dy); // Undo move if collision detected
        return false;
    }
    return true;
}

// Rotates the piece, reverting if it causes a collision
void Board::rotatePiece(Tetromino &piece)
{
    piece.rotate();
    if (isCollision(piece))
    {
        piece.rotateBack();
    }
}

// Places the falling piece permanently onto the grid
void Board::placePiece(const Tetromino &piece)
{
    piece.placeOnBoard(grid);
}

// Checks for and clears fully filled lines, returning number of cleared lines
int Board::clearFullLines()
{
    int linesCleared = 0;

    for (int y = 0; y < HEIGHT; ++y)
    {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x)
        {
            if (grid[y][x] == ' ')
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            // Shift all rows above down by one
            for (int row = y; row > 0; --row)
            {
                for (int col = 0; col < WIDTH; ++col)
                {
                    grid[row][col] = grid[row - 1][col];
                }
            }
            // Clear the top row
            for (int col = 0; col < WIDTH; ++col)
            {
                grid[0][col] = ' ';
            }
            linesCleared++;
        }
    }
    return linesCleared;
}

// Checks if a piece collides with the existing board (walls, floor, other blocks)
bool Board::isCollision(const Tetromino &piece) const
{
    return piece.collidesWith(grid);
}

// Draws the board with borders, empty cells, and colored pieces
void Board::drawBoard(const char grid[HEIGHT][WIDTH]) const
{
    std::cout << COLOR_FRAME << "+--------------------+" << RESET_COLOR << "\n";
    for (int y = 0; y < HEIGHT; ++y)
    {
        std::cout << COLOR_FRAME << "|" << RESET_COLOR;
        for (int x = 0; x < WIDTH; ++x)
        {
            char cell = grid[y][x];
            if (cell == ' ')
            {
                std::cout << COLOR_EMPTY << '.' << RESET_COLOR; // Gray dots for empty cells
            }
            else
            {
                const char *color = RESET_COLOR;
                switch (cell)
                {
                case 'I':
                    color = COLOR_I;
                    break;
                case 'O':
                    color = COLOR_O;
                    break;
                case 'T':
                    color = COLOR_T;
                    break;
                case 'S':
                    color = COLOR_S;
                    break;
                case 'Z':
                    color = COLOR_Z;
                    break;
                case 'J':
                    color = COLOR_J;
                    break;
                case 'L':
                    color = COLOR_L;
                    break;
                }
                std::cout << color << '#' << RESET_COLOR; // Colored hash for blocks
            }
        }
        std::cout << COLOR_FRAME << "|" << RESET_COLOR << "\n";
    }
    std::cout << COLOR_FRAME << "+--------------------+" << RESET_COLOR << "\n";
}
