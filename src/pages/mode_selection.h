#pragma once
#include "./state.h"

void drawModeSelectionPage(GameState* state);
void updateModeSelectionPage(GameState* state,int w,int h);

bool isMouseOver1Player;
bool isMouseOver2Players;
bool isMouseOverGraph;
bool wasHovering = false;

void drawModeSelectionPage(GameState* state) {

    int w = GetRenderWidth();
    int h = GetRenderHeight();

    Vector2 mousePosition = GetMousePosition();

    Rectangle modeSelectRect ={w/7, h/5, 0.7*w, h*0.2};

    float centerX = modeSelectRect.x + modeSelectRect.width / 2;
    float centerY = modeSelectRect.y + modeSelectRect.height / 2;
    DrawRectangleRounded(modeSelectRect, roundness, 0, Darkblue);
    DrawRectangleRoundedLines(modeSelectRect, roundness+0.1, 0, 5, lightBlue);

    DrawText("Choose your mode", centerX - (MeasureText("Choose your mode", textSize) / 2), centerY - (textSize / 2), textSize, WHITE);
    for(int i=0; i<6 ; i++) DrawCircle(w/5 + i*(w*0.008 + w*0.012) , h/4.4, w*0.008, circleColors[i]);

    Rectangle oneplayerRect = { w/5, h/5.5 + h*0.2 + h/10, w/10, h/4 };
    DrawText("1 Player", (float)(oneplayerRect.x + oneplayerRect.width / 2 - w/15), (float)(oneplayerRect.y + oneplayerRect.height*0.8 ), h/20, YELLOW);
    
    Rectangle twoplayersRect = { w/5 + 2*w/10 + w/12 , h/5.5 + h*0.2 + h/10, w/8, h/4 };
    DrawText("2 Players", (float)(twoplayersRect.x + twoplayersRect.width / 2 - w/10), (float)(twoplayersRect.y + twoplayersRect.height*0.8 ), h/20, YELLOW);

    Rectangle graphRect = { w/5 + 2*w/5 + w/8 , h/5.5 + h*0.2 + h/10, w/8, h/4 };
    DrawText("Graph", (float)(graphRect.x + graphRect.width / 2 - w/17), (float)(graphRect.y + graphRect.height*0.8 ), h/20, YELLOW);

    DrawTexturePro(oneplayer_texture,
            (Rectangle){ 0, 0, (float)oneplayer_texture.width, (float)oneplayer_texture.height },
            oneplayerRect,
            (Vector2){ oneplayerRect.width / 5, oneplayerRect.height / 5 },
            0.0f,
            WHITE);
    DrawTexturePro(twoplayers_texture,
                (Rectangle){ 0, 0, (float)twoplayers_texture.width, (float)twoplayers_texture.height },
                twoplayersRect,
                (Vector2){ twoplayersRect.width / 5, twoplayersRect.height / 5 },
                0.0f,
                WHITE);
    DrawTexturePro(graph_texture,
                (Rectangle){ 0, 0, (float)graph_texture.width, (float)graph_texture.height },
                graphRect,
                (Vector2){ graphRect.width / 5, graphRect.height / 5 },
                0.0f,
                WHITE);     
    //DrawTextureRec(oneplayer_texture, oneplayerRect, (Vector2){ oneplayerRect.x, oneplayerRect.y }, WHITE);
    if (CheckCollisionPointRec(mousePosition,oneplayerRect) || CheckCollisionPointRec(mousePosition,twoplayersRect) || CheckCollisionPointRec(mousePosition,graphRect)) {
        if (!wasHovering) {
            PlaySound(click_sound);
        }
        wasHovering = true;
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        if (wasHovering) {
            StopSound(click_sound);
        }
        wasHovering = false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void updateModeSelectionPage(GameState* state,int w, int h) {
    Rectangle oneplayerRect = { w/5, h/5.5 + h*0.2 + h/10, w/10, h/4 };
    Rectangle twoplayersRect = { w/5 + 2*w/10 + w/12 , h/5.5 + h*0.2 + h/10, w/8, h/4 };
    Rectangle graphRect = { w/5 + 2*w/5 + w/8 , h/5.5 + h*0.2 + h/10, w/8, h/4 };

    if (CheckCollisionPointRec(GetMousePosition(),oneplayerRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        state->current_page = SETTINGS_PAGE;
        state->mode = ONE_PLAYER;
    }
    else if(CheckCollisionPointRec(GetMousePosition(),twoplayersRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        state->current_page=ENTER_WORD_PAGE;
        state->mode = TWO_PLAYERS;
    }
    else if (CheckCollisionPointRec(GetMousePosition(),graphRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        state->current_page=GRAPH_PAGE;
        state->mode = GRAPH;
    }
}