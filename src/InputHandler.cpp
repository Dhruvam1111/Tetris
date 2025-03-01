#include "InputHandler.h"
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#endif

// Constructor - initialize all keys as unpressed
InputHandler::InputHandler()
{
    for (int i = 0; i < TOTAL_KEYS; ++i)
    {
        keys[i] = false;
        prevKeys[i] = false;
    }
}

// Update input state - reads keys and tracks both press and hold
void InputHandler::update()
{
    // Reset all keys for this frame
    for (int i = 0; i < TOTAL_KEYS; ++i)
    {
        prevKeys[i] = keys[i];
        keys[i] = false; // Will be set to true only if detected this frame
    }

#ifdef _WIN32
    while (_kbhit()) // Check if a key is pressed
    {
        int ch = _getch(); // Get the key code

        // If it's a special key (arrow keys), _getch() returns 0 or 224 first
        if (ch == 0 || ch == 224)
        {
            ch = _getch(); // Get the actual key code
            switch (ch)
            {
            case 75:
                keys[LEFT] = true;
                break; // Left Arrow
            case 77:
                keys[RIGHT] = true;
                break; // Right Arrow
            case 80:
                keys[DOWN] = true;
                break; // Down Arrow
            case 72:
                keys[ROTATE] = true;
                break; // Up Arrow
            }
        }
        else
        {
            switch (ch)
            {
            case ' ':
                keys[HARD_DROP] = true;
                break; // Space key for hard drop
            case 'p':
            case 'P':
                keys[PAUSE] = true;
                break; // Pause game
            case 'q':
            case 'Q':
                keys[QUIT] = true;
                break; // Quit game
            }
        }
    }
#else
    while (kbhit())
    {
        int ch = getch(); // Get the key input

        if (ch == 27) // Escape sequence (for arrow keys)
        {
            if (getch() == 91) // '[' part of escape sequence
            {
                switch (getch())
                {
                case 'A':
                    keys[ROTATE] = true;
                    break; // Up Arrow
                case 'B':
                    keys[DOWN] = true;
                    break; // Down Arrow
                case 'C':
                    keys[RIGHT] = true;
                    break; // Right Arrow
                case 'D':
                    keys[LEFT] = true;
                    break; // Left Arrow
                }
            }
        }
        else
        {
            switch (ch)
            {
            case ' ':
                keys[HARD_DROP] = true;
                break;
            case 'p':
            case 'P':
                keys[PAUSE] = true;
                break;
            case 'q':
            case 'Q':
                keys[QUIT] = true;
                break;
            }
        }
    }
#endif
}

// Key press functions - return true only on the initial press
bool InputHandler::leftPressed() const { return keys[LEFT] && !prevKeys[LEFT]; }
bool InputHandler::rightPressed() const { return keys[RIGHT] && !prevKeys[RIGHT]; }
bool InputHandler::downPressed() const { return keys[DOWN] && !prevKeys[DOWN]; }
bool InputHandler::rotatePressed() const { return keys[ROTATE] && !prevKeys[ROTATE]; }
bool InputHandler::hardDropPressed() const { return keys[HARD_DROP] && !prevKeys[HARD_DROP]; }
bool InputHandler::pausePressed() const { return keys[PAUSE] && !prevKeys[PAUSE]; }
bool InputHandler::quitPressed() const { return keys[QUIT] && !prevKeys[QUIT]; }

// Key hold functions - return true as long as the key is being held down
bool InputHandler::leftHeld() const { return keys[LEFT]; }
bool InputHandler::rightHeld() const { return keys[RIGHT]; }
bool InputHandler::downHeld() const { return keys[DOWN]; }

#ifndef _WIN32
// Non-blocking keyboard check for Linux/macOS
int InputHandler::kbhit()
{
    struct timeval tv = {0, 0};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(1, &readfds, NULL, NULL, &tv);
}

// Single character input for Linux/macOS
int InputHandler::getch()
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif
