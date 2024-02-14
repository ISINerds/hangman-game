# hangman-game

# Hangman Game

This project is a Hangman game developed in C using the Raylib library. The game offers three modes: single-player, two-player, and graph mode. Additionally, it provides the functionality to play using either the mouse or keyboard.

## Game Principle

Hangman is a word guessing game where the player tries to guess a word by suggesting letters within a certain number of attempts. For each incorrect guess, a part of a hangman is drawn.

## Modes

- Single-Player Mode: The system selects a random word based on a chosen difficulty level, and the player tries to guess the word before reaching the maximum allowed attempts.
- Two-Player Mode: Player 1 suggests a word for Player 2 to guess.
- Graph Mode: Visualizes the game's word dictionary as a binary tree on a map. It allows the user to add or remove words and view the resulting graph.

## Folder Structure

- src/: Contains the main source code of the application.
- assets/: Includes images and sounds used in the game.
- tests/: Contains several tests to verify the application's logic.
- external/: Generated folder for libraries and dependencies.
- build/: Generated folder for build outputs.
 
## Dependencies

This project relies on Raylib and raygui libraries for graphics and input handling. The Makefile is provided to automate various commands such as installing dependencies, compiling the project, running the application, or running tests.

## Installation and Usage


-Install Dependencies:

    

    make install_raylib && make install_raygui && make install_criterion
    
-Compile the Project:
    
    
    
    make build
    
-Run the Application:
    
    
    
    make run
    
-Run Tests:
    
    
    make run_test

-Clean the test:

    make clean_test
