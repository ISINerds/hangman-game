#pragma once
#include "./state.h"

void drawWelcomePage(GameState* state,int screen_width,int screen_height);
void updateWelcomePage(GameState* state,int screen_width,int screen_height);

void drawWelcomePage(GameState* state,int screen_width,int screen_height){
    // DrawRectangle(screen_width/4, screen_height/4, screen_width/2, screen_height/2, MAROON);
    DrawText("Welcome page", screen_width/4, screen_height/4, 20, WHITE);
}

void updateWelcomePage(GameState* state,int screen_width,int screen_height){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        state->current_page=SETTINGS_PAGE;
    }
}