#include<stdio.h>
#include "../includes/utils/file_parsing.h"
#include "../includes/data-structures/binary_tree.h"
#include "../includes/data-structures/trie.h"
// TODO : refactor the includes
#include "./state.h"
#include "./welcome_page.h"
#include "./settings_page.h"
#include "./game_page.h"
#include "./enter_word_page.h"

void drawBackgroundImage(Texture2D background_image,int screen_width,int screen_height){
        float scaleX = (float)screen_width / background_image.width;
        float scaleY = (float)screen_height / background_image.height;
        DrawTexturePro(background_image, (Rectangle){ 0, 0, background_image.width, background_image.height },
                       (Rectangle){ 0, 0, screen_width, screen_height }, (Vector2){ 0, 0 }, 0, WHITE);

}

void setTextBoxStyles(){
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0xFFFFFFFF);
    GuiSetStyle(TEXTBOX, BASE_COLOR_DISABLED, 0xFFFFFFFF);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_NORMAL, 0x000000FF);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_FOCUSED, 0x000000FF);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_PRESSED, 0x000000FF);
    GuiSetStyle(TEXTBOX, BORDER_COLOR_DISABLED, 0x000000FF);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, 0x000000FF);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_DISABLED, 0x000000FF);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, 0x000000FF);
    GuiSetStyle(TEXTBOX, TEXT_COLOR_PRESSED, 0x000000FF);
    // GuiSetStyle(TEXTBOX, BASE_COLOR_DISABLED, 0x000000FF);
    // GuiSetStyle(TEXTBOX, BASE_COLOR_FOCUSED, 0x000000FF);
    // GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, 0x000000FF);
    // GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, 0x000000FF);
}

void setPopUpStyles(){
    
}
int main(void){
    WordList words = parseFile("./assets/words.txt");
    BinaryTree* root = NULL;
    root = addWords(words,root);
    generateImageFromBinaryTree(root,"./build/tree","./assets/tree.gv");
    GameState state = {
        .current_page=ENTER_WORD_PAGE,
        .keyboard = initKeyBoard(),
        .root=root,
        .attempt=0,
        .word_list=words,
    };
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hangman");
    InitAudioDevice();
    setTextBoxStyles();
    success_sound = LoadSound("./assets/sound/success.mp3");
    fail_sound = LoadSound("./assets/sound/fail.mp3");
    for(int i=0;i<7;i++){
        char filePath[50];
        snprintf(filePath, sizeof(filePath), "./assets/images/Hangman/hangman%d.png",i);
        hangman_images[i]=LoadTexture(filePath);
    }
    blood_image=LoadTexture("./assets/images/Hangman/blood.png");
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
            case ENTER_WORD_PAGE:
                updateEnterWordPage(&state,w,h);
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
            case ENTER_WORD_PAGE:
                drawEnterWordPage(&state,w,h);
                break;
            default:
                break;
        }
        int fps = GetFPS();
        // Render FPS text in bottom-left corner
        DrawFPS(10, h-30);
        EndDrawing();
    }
    UnloadTexture(background_image); // Unload texture
    for(int i=0;i<7;i++){
        UnloadTexture(hangman_images[i]);
    }
    UnloadTexture(blood_image);

    CloseWindow();
    return 0;
}