#pragma once

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../../external/raygui/raygui.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../includes/utils/file_parsing.h"
#include "../includes/data-structures/binary_tree.h"
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 450
# define MAX_ATTEMPT 6
typedef enum{
    WELCOME_PAGE,
    SETTINGS_PAGE,
    ENTER_WORD_PAGE,
    GAME_PAGE,
}Page;

typedef enum {
    US,
    FR,
} KeyboardLayout;

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
    KeyboardLayout keyboard_layout;
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
Sound success_sound,fail_sound;
char text_input[256] = { 0 };
void changePage(GameState* state,Page page){
    state->current_page=page;
}

void changeGameDifficulty(GameState* state, Difficulty difficulty){
    state->game_difficulty=difficulty;
}



KeyboardLayout getKeyboardLayout(void){
    FILE *pipe = popen("setxkbmap -query | grep layout", "r");
    if (!pipe) {
        perror("popen");
        return US;
    }
    KeyboardLayout Keyboard_layout=US;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        char *layout = strstr(buffer, "layout:");
        if (layout != NULL) {
            layout += strlen("layout:");
            while (*layout == ' ' || *layout == '\t') {
                layout++;
            }

            char *newline = strchr(layout, '\n');
            if (newline != NULL) {
                *newline = '\0';
            }

            if (strcmp(layout, "us") == 0) {
                printf("[HANGMAN-INFO] Keyboard Layout: US (English)\n");
                Keyboard_layout = US;
            } else if (strcmp(layout, "fr") == 0) {
                printf("[HANGMAN-INFO] Keyboard Layout: FR (French)\n");
                Keyboard_layout = FR;
            } else {
                printf("[HANGMAN-INFO] Unknown Keyboard Layout: %s\n", layout);
                Keyboard_layout = US;
            }
        }
    }
    pclose(pipe);
    return Keyboard_layout;
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
    keyboard.keyboard_layout=getKeyboardLayout();
    return keyboard;
}
