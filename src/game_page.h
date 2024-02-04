#pragma once
#include "./state.h"

void drawGamePage(GameState* state,int screen_width,int screen_height);
void updateGamePage(GameState* state,int screen_width,int screen_height);
// contains the current state of the word
void drawTop(GameState* state,Rectangle top_rect){
    DrawRectangleRoundedLines(top_rect,0.2,1,1,ColorFromHSV(120,1,1));
}
void drawKeyboard(GameState* state,Rectangle keyboard_rect){
    DrawRectangleRoundedLines(keyboard_rect,0.2,1,1,ColorFromHSV(120,1,1));
}
void drawHangMan(GameState* state,Rectangle hangman_rect, int screen_width, int screen_height){
    if (state->attempt >= 0 && state->attempt <= 6) {
            char filePath[50];
            snprintf(filePath, sizeof(filePath), "././assets/images/Hangman/hangman%d.png", state->attempt);

            Image image = LoadImage(filePath);
            Texture2D texture = LoadTextureFromImage(image);

            if(state->attempt == 6 ) {
                Image blood_image = LoadImage("././assets/images/Hangman/blood.png");
                Texture2D blood_texture = LoadTextureFromImage(blood_image);
                DrawTexture(blood_texture, hangman_rect.x + screen_width/8 , hangman_rect.y + screen_height/6, WHITE);
            }

            DrawTexturePro(texture, (Rectangle){ 0, 0, (float)texture.width, (float)texture.height } , hangman_rect, (Vector2){hangman_rect.width / 12, hangman_rect.height / 12 } , 0.0f , WHITE);

        } else printf("Invalid attempt value: %d\n", state->attempt);
    DrawRectangleRoundedLines(hangman_rect,0.2,1,1,ColorFromHSV(120,1,1));
}
void drawGamePage(GameState* state,int screen_width,int screen_height){
    // DrawRectangle(screen_width/4, screen_height/4, screen_width/2, screen_height/2, GREEN);
    // DrawText("Game page", screen_width/4, screen_height/4, 20, WHITE);
    Rectangle top_rect = {
        .x = (screen_width*0.05),
        .y = (screen_height*0.04),
        .width = screen_width-2*(screen_width*0.05),
        .height = screen_height*0.125,
    };
    drawTop(state,top_rect);
    Rectangle keyboard_rect = {
        .x = (screen_width*0.05),
        .y = (screen_height*0.04) + screen_height*0.125 + (screen_height*0.04),
        .width = screen_width*0.4,
        .height = screen_height*0.7,
    };
    drawKeyboard(state,keyboard_rect);
    Rectangle hangman_rect = {
        .x = (screen_width*0.05) + screen_width*0.4 + (screen_width*0.05),
        .y = (screen_height*0.04) + screen_height*0.125 + (screen_height*0.04),
        .width = screen_width*0.4,
        .height = screen_height*0.7,
    };
    drawHangMan(state,hangman_rect,screen_width,screen_height);

}
void updateTop(GameState* state,int screen_width,int screen_height){

}
void updateKeyboard(GameState* state,int screen_width,int screen_height){

}
void updateHangMan(GameState* state,int screen_width,int screen_height){

}
void updateGamePage(GameState* state,int screen_width,int screen_height){
    updateTop(state,screen_width,screen_height);
    updateKeyboard(state,screen_width,screen_height);
    updateHangMan(state,screen_width,screen_height);
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     state->current_page=WELCOME_PAGE;
    // }
}