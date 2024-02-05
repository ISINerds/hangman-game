#include<stdio.h>
#include "./includes/utils/file_parsing.h"
#include "./includes/data-structures/binary_tree.h"
#include "./includes/data-structures/trie.h"
// TODO : refactor the includes
#include "./state.h"
#include "./welcome_page.h"
#include "./settings_page.h"
#include "./game_page.h"


void drawBackgroundImage(Texture2D background_image,int screen_width,int screen_height){
        float scaleX = (float)screen_width / background_image.width;
        float scaleY = (float)screen_height / background_image.height;
        DrawTexturePro(background_image, (Rectangle){ 0, 0, background_image.width, background_image.height },
                       (Rectangle){ 0, 0, screen_width, screen_height }, (Vector2){ 0, 0 }, 0, WHITE);

}


int main(void){
    // WordList words = parseFile("./assets/words.txt");
    WordScore* words_array = (WordScore*)malloc(sizeof(WordScore)*5);
    words_array[0].word = "school";
    words_array[0].difficulty = EASY;
    
    words_array[1].word = "apple";
    words_array[1].difficulty = EASY;
    
    words_array[2].word = "tree";
    words_array[2].difficulty = EASY;
    
    words_array[3].word = "education";
    words_array[3].difficulty = EASY;
    
    words_array[4].word = "evaluation";
    words_array[4].difficulty = EASY;
    WordList words = {
        .words_array = words_array,
        .words_array_size = 5
    };
    BinaryTree* root = NULL;
    root = addWords(words,root);
    generateImageFromBinaryTree(root,"./build/tree","./assets/tree.gv");


    GameState state = {
        .current_page=GAME_PAGE,
        .keyboard = initKeyBoard(),
        .root=root,
        .attempt=0,
        .curr_word_state=malloc(strlen("__________") + 1),//"__________",
        .word_to_guess="evaluation",
        .word_list=words
    };
    strcpy(state.curr_word_state, "__________");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple Raylib Example");
    Texture2D background_image = LoadTexture("./assets/images/background.png");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        int w = GetRenderWidth();
        int h = GetRenderHeight();
        drawBackgroundImage(background_image,w,h);

        switch (state.current_page) {
            case WELCOME_PAGE:
                updateWelcomePage(&state,w,h);
                break;
            case SETTINGS_PAGE:
                updateSettingsPage(&state,w,h);
                break;
            case GAME_PAGE:
                updateGamePage(&state,w,h);
                break;
            default:
                break;
        }

        switch (state.current_page) {
            case WELCOME_PAGE:
                drawWelcomePage(&state,w,h);
                break;
            case SETTINGS_PAGE:
                drawSettingsPage(&state,w,h);
                break;
            case GAME_PAGE:
                drawGamePage(&state,w,h);
                break;
            default:
                break;
        }

        EndDrawing();
    }
    UnloadTexture(background_image); // Unload texture
    CloseWindow();
    return 0;
}