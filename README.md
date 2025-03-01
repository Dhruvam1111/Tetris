# Tetris Game in C++

## 📌 Overview
This is a **console-based Tetris game** developed in **C++**, featuring classic Tetris mechanics like falling tetrominoes, line clearing, scoring, and game-over conditions. The project follows **object-oriented programming (OOP) principles** and includes **real-time input handling** to provide a smooth gameplay experience.

## 📖 Table of Contents
1. [Features](#features)
2. [Installation & Running the Game](#installation--running-the-game)
3. [Usage](#usage)
4. [Controls](#controls)
5. [Data Structures Analysis](#data-structures-analysis)
6. [Future Improvements](#future-improvements)
7. [Contributing](#contributing)
8. [Project Structure](#project-structure)
9. [License](#license)

## 🎯 Features
✅ **All Seven Tetrominoes** (I, O, T, S, Z, J, L)  
✅ **10x20 Game Grid** with real-time rendering  
✅ **Smooth Piece Movements** (left, right, rotate, and drop)  
✅ **Gravity Mechanism** (falling speed increases over time after each level)  
✅ **Collision Detection** (prevents overlapping or out-of-bounds movement)  
✅ **Line Clearing System** (removes full rows and shifts the grid)  
✅ **Scoring System** (points awarded for cleared lines)  
✅ **Level Up System** (game level increases after every 3 cleared lines)  
✅ **Pause & Quit Functionality**  

## 🔧 Installation & Running the Game
### 📂 Clone the Repository
```sh
git clone https://github.com/your-repo/Tetris-CPP.git
cd Tetris-CPP
```

### 🛠️ Build & Run (Using g++)
Ensure you have **g++ (C++17 or later)** installed.
```sh
g++ src/*.cpp -o Tetris -std=c++17
./Tetris
```

### 🖥️ Running in VS Code (Using `tasks.json` & `launch.json`)
1. Open the project folder in **Visual Studio Code**.
2. Press **Ctrl + Shift + B** to build the project.
3. Press **F5** to run the game in debug mode.

## 🎮 Usage
- Start the game by running the compiled executable.
- Move and rotate tetrominoes to fill rows and clear them.
- The game increases in difficulty as you clear lines.
- The game ends when the blocks reach the top.

## 🎮 Controls
| Key           | Action           |
|--------------|----------------|
| Left Arrow (←) | Move left       |
| Right Arrow (→) | Move right      |
| Up Arrow (↑) | Rotate piece    |
| Down Arrow (↓) | Soft drop      |
| Spacebar      | Hard drop      |
| P / p           | Pause/Resume   |
| Q / q           | Quit game      |
| R / r           | Restart game |

## 📊 Data Structures Analysis
- **Game Board:** Implemented as a **2D array (char grid[20][10])**, allowing efficient row clearing and rendering.
- **Tetrominoes:** Implemented as a **vector of coordinate pairs**, enabling flexible movement and rotation.
- **Collision Detection:** Uses **piece position checks** against the board grid to determine if a move is valid.
- **User Input Handling:** Uses platform-specific input handling (`conio.h` for Windows, `termios.h` for Linux/macOS).

## 🚀 Future Improvements
- Implement **graphical UI** using SDL or OpenGL.
- Add **multiplayer support**.
- Introduce **power-ups** or **special modes**.
- Implement **custom key bindings**.

## 🤝 Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch (`feature-branch`).
3. Make your changes and commit them.
4. Push to your fork and submit a pull request.

## 📂 Project Structure
```
├── src/                 # Source code files
│   ├── Game.cpp         # Core game loop and logic
│   ├── Board.cpp        # Handles the 10x20 grid logic
│   ├── Tetromino.cpp    # Manages tetromino shapes & movements
│   ├── InputHandler.cpp # Handles keyboard input
│   ├── main.cpp         # Entry point of the game
│
├── include/             # Header files
│   ├── Game.h
│   ├── Board.h
│   ├── Tetromino.h
│   ├── InputHandler.h
│
├── launch.json          # VS Code Debug Configuration
├── tasks.json           # VS Code Build Tasks
├── Tetris.exe           # Executable (Windows only)
├── README.md            # Project Documentation
```

## 🏷️ License
This project is open-source under the **MIT License**. Feel free to modify and enhance it! 🚀

