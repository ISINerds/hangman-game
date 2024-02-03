#pragma once
#include "./state.h"

void drawSettingsPage(GameState* state,int screen_width,int screen_height);
void updateSettingsPage(GameState* state,int screen_width,int screen_height);


void drawSettingsPage(GameState* state,int screen_width,int screen_height){
    // DrawRectangle(screen_width/4, screen_height/4, screen_width/2, screen_height/2, RED); 
    DrawText("Setting page", screen_width/4, screen_height/4, 20, WHITE);
}

void updateSettingsPage(GameState* state,int screen_width,int screen_height){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        state->current_page=GAME_PAGE;
    }
}