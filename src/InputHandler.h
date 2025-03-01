#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#ifdef _WIN32
#include <windows.h> // Windows-specific header for input handling
#else
#include <termios.h> // For controlling terminal I/O modes
#include <unistd.h>  // For read(), usleep()
#include <fcntl.h>   // For file control options
#endif

// Class for handling user input
class InputHandler
{
public:
    // Enumeration for different key actions
    enum Key
    {
        LEFT,      // Move left
        RIGHT,     // Move right
        DOWN,      // Move down
        ROTATE,    // Rotate piece
        HARD_DROP, // Instantly drop piece
        PAUSE,     // Pause the game
        QUIT,      // Quit the game
        TOTAL_KEYS // Total number of keys
    };

    InputHandler(); // Constructor

    void update(); // Updates the state of keys

    // Functions to check if a key was just pressed
    bool leftPressed() const;
    bool rightPressed() const;
    bool downPressed() const;
    bool rotatePressed() const;
    bool hardDropPressed() const;
    bool pausePressed() const;
    bool quitPressed() const;

    // Functions to check if a key is being held down
    bool leftHeld() const;
    bool rightHeld() const;
    bool downHeld() const;

private:
    bool keys[TOTAL_KEYS];     // Current state of keys
    bool prevKeys[TOTAL_KEYS]; // Previous state of keys

#ifndef _WIN32
    int kbhit(); // Check if a key has been hit
    int getch(); // Get character from input
#endif
};

#endif
