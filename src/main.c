#include<stdio.h>
#include "./includes/utils/file_parsing.h"
#include "./includes/data-structures/binary_tree.h"
#include "./includes/data-structures/trie.h"
#include "raylib.h"
int main(void){
    WordList words = parseFile("./assets/words.txt");
    BinaryTree* root = NULL;
    root = addWords(words,root);
    generateImageFromBinaryTree(root,"./build/tree.svg","./assets/tree.gv");
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Initialize window
    
    InitWindow(screenWidth, screenHeight, "Simple Raylib Example");

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        // (This example doesn't need updates)

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE); // Clear background color

        // Draw a rectangle
        DrawRectangle(screenWidth/4, screenHeight/4, screenWidth/2, screenHeight/2, MAROON);

        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}