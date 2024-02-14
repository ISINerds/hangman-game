# hangman-game

Hangman Game

This project is a Hangman game developed in C using the Raylib library. The game offers three modes: single-player, two-player, and graph mode. Additionally, it provides the functionality to play using either the mouse or keyboard.

Game Principle

Hangman is a word guessing game where the player tries to guess a word by suggesting letters within a certain number of attempts. For each incorrect guess, a part of a hangman is drawn.

Modes

    Single-Player Mode: The system selects a random word based on a chosen difficulty level, and the player tries to guess the word before reaching the maximum allowed attempts.
    Two-Player Mode: Player 1 suggests a word for Player 2 to guess.
    Graph Mode: Visualizes the game's word dictionary as a binary tree on a map. It allows the user to add or remove words and view the resulting graph.

Folder Structure

    src/: Contains the main source code of the application.
    assets/: Includes images and sounds used in the game.
    tests/: Contains several tests to verify the application's logic.
    external/: Generated folder for libraries and dependencies.
    build/: Contains the build outputs.

Dependencies

This project relies on Raylib and raygui libraries for graphics and input handling. The Makefile is provided to automate various commands such as installing dependencies, compiling the project, running the application, or running tests.

Installation and Usage

    Clone the repository:

    bash

git clone https://github.com/yourusername/hangman-game.git

Navigate to the project directory:

bash

cd hangman-game

Use the Makefile to automate tasks:

    Install Dependencies:

    bash

make install

Compile the Project:

bash

make build

Run the Application:

bash

make run

Run Tests:

bash

make test


# Coding Style Guide

## File Naming

- Use lowercase letters for file names.
- Separate words with underscores.

    Example: `main.c`, `file_parser.c`

## Function and Variable Naming

- Use camelCase for function names.
- Separate variable names with underscores.
- Be descriptive and use meaningful names.

    Example:
    ```c
    char** word_arrays;
    int calculateScore();
    char *readTextFile();
    ```

## Struct Naming

- Use camelCase for struct names.
- Consider adding a typedef for cleaner usage.

    Example:
    ```c
    typedef struct {
        int size;
        char **lines;
    } TextData;
    ```

## Macro Naming

- Use uppercase letters for macro names.
- Separate words with underscores.

    Example:
    ```c
    #define MAX_WORD_LENGTH 20
    ```

## Constants

- Use uppercase letters for constants.
- Separate words with underscores.

    Example:
    ```c
    const int MAX_ATTEMPTS = 5;
    ```

## Enums

- Use a mixed case for enum names.
- Enumerators are typically uppercase.

    Example:
    ```c
    typedef enum {
        SUCCESS,
        FAILURE,
    } Status;
    ```

## Comments

- Use comments to explain complex code or provide context.
- Follow a consistent commenting style, such as using `//` for single-line comments and `/* */` for multi-line comments.

    Example:
    ```c
    // This function calculates the average score.
    float calculateAverageScore(int scores[], int numScores);
    ```

Remember to update this guide as your coding standards evolve, and encourage your team to adhere to these conventions for a more consistent and maintainable codebase.
