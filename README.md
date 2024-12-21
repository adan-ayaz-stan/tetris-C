
# Tetris Game

A classic Tetris game built in C++ using the Simple and Fast Multimedia Library (SFML).

## Preview of the Game
![image](https://github.com/user-attachments/assets/cbea0d46-4b48-4266-b3ab-0306da502f6d)

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Preview of the Game](#preview-of-the-game)
- [License](#license)

---

## About the Project

This project is a recreation of the iconic Tetris game, designed to be simple yet enjoyable. It utilizes SFML to handle graphics, audio, and input, offering a smooth and responsive gameplay experience. The purpose of this project is to demonstrate fundamental game development principles and provide an interactive way to practice programming with C++.

---

## Features

- Classic Tetris gameplay with falling blocks.
- Smooth animations and intuitive controls.
- Scoring system based on lines cleared.
- Increasing difficulty as the game progresses.
- Fully customizable settings for window size and controls.

---

## Installation

### Prerequisites

- A C++ compiler supporting C++11 or later.
- SFML library installed on your system. You can download it from [SFML's official website](https://www.sfml-dev.org/).

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/tetris-sfml.git
   cd tetris-sfml
   ```

2. Build the project:
   - If using CMake:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
   - Alternatively, compile directly with g++:
     ```bash
     g++ -o tetris main.cpp -lsfml-graphics -lsfml-window -lsfml-system
     ```

3. Run the executable:
   ```bash
   ./tetris
   ```

---

## Usage

### Controls

- **Left Arrow**: Move block left.
- **Right Arrow**: Move block right.
- **Down Arrow**: Drop block faster.
- **Up Arrow**: Rotate block.
- **Escape**: Quit the game.

---

## Preview of the Game

![image](https://github.com/user-attachments/assets/cbea0d46-4b48-4266-b3ab-0306da502f6d)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

