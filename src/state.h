#pragma once


#include "raylib.h"
#include "./includes/utils/file_parsing.h"
#include "./includes/data-structures/binary_tree.h"
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 450
# define MAX_ATTEMPT 6
typedef enum{
    WELCOME_PAGE,
    SETTINGS_PAGE,
    GAME_PAGE,
}Page;


typedef enum {
    KEY_CORRECT,
    KEY_WRONG,
    KEY_NOT_CLICKED
} KeyState;

typedef struct {
    char character;
    KeyState state;
} Key;

typedef struct {
    Key* keys;
    int size;
} Keyboard;

typedef struct{
    Page current_page;
    Difficulty game_difficulty;
    BinaryTree* root;
    WordList word_list;
    Keyboard keyboard;
    char* word_to_guess;
    char* curr_word_state;
    int attempt;
}GameState;
Texture2D hangman_images[7];
Texture2D blood_image;

void changePage(GameState* state,Page page){
    state->current_page=page;
}

void changeGameDifficulty(GameState* state, Difficulty difficulty){
    state->game_difficulty=difficulty;
}

Keyboard initKeyBoard(){
    Keyboard keyboard;
    keyboard.size=26;
    keyboard.keys = (Key*)malloc(keyboard.size*sizeof(Key));
    if(keyboard.keys == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<keyboard.size;i++){
        keyboard.keys[i].character='A'+i;
        keyboard.keys[i].state=KEY_NOT_CLICKED;
    }
    return keyboard;
}
