#pragma once
#include "./state.h"

void drawGamePage(GameState* state,int screen_width,int screen_height);
void updateGamePage(GameState* state,int screen_width,int screen_height);
// contains the current state of the word
void drawTop(GameState* state,Rectangle top_rect){
    Color green = (Color){0,178,13, 255};
    Color purple = (Color){154,52,161,255};
    Color yellow = (Color){255,216,0,255};
    Color pink = (Color){232,0,145,255};
    Color blue = (Color){0,156,225,255};
    Color orange = (Color){255,141,0,255};
    //circles
    float circle_radius = 10.0f;
    float circles_total_width = 6 * (circle_radius * 2 + 5); // Total width of all circles and gaps

    Color circleColors[] = { green, yellow, orange, pink, blue, purple };

    for (int i = 0; i < 6; ++i) {
        float circleX = circles_total_width / 2 + i * (circle_radius * 2 + 5);
        DrawCircle(circleX, (top_rect.height) / 2 +10, circle_radius, circleColors[i]);
    }

    state->curr_word_state = "information";
    // DrawRectangleRoundedLines(top_rect,0.2,1,1,ColorFromHSV(120,1,1));
    if(state->curr_word_state != NULL){
        int font_size= 50;
        int letter_spacing=7;
        int word_width = MeasureText(state->curr_word_state, font_size);
        int wordX = top_rect.x + circles_total_width + (top_rect.width-circles_total_width - word_width) / 2;
        int wordY = (top_rect.height) / 2;

        for (int i = 0; i < strlen(state->curr_word_state); i++){
            DrawText(TextFormat("%c", toupper(state->curr_word_state[i])), wordX + i * (letter_spacing + 20), wordY, 20, WHITE);
        }
    }
    

}
void drawKeyboard(GameState* state,Rectangle keyboard_rect){
    DrawRectangleRoundedLines(keyboard_rect,0.2,1,1,ColorFromHSV(120,1,1));
}
void drawHangMan(GameState* state,Rectangle hangman_rect){
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
    drawHangMan(state,hangman_rect);

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