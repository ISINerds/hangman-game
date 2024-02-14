#pragma once
#include "./state.h"

void drawWelcomePage(GameState* state,int screen_width,int screen_height);
void updateWelcomePage(GameState* state,int screen_width,int screen_height);


Color black = (Color){ 0,0,0, 255 };
Color gray = (Color){ 81,105,162, 255 };
Color dark_blue = (Color){ 26,31,68, 0 };
Color green = (Color){0,178,13, 255};
Color purple = (Color){154,52,161,255};
Color yellow = (Color){255,216,0,255};
Color pink = (Color){232,0,145,255};
Color blue = (Color){0,156,225,255};
Color orange = (Color){255,141,0,255};


void drawWelcomePage(GameState* state,int screen_width,int screen_height){
    float roundness = 1.0f;
    float width = 500.0f;
    float height = 120.0f;
    float segments = 0.0f;
    float line_thick = 3.0f;

    int w = GetRenderWidth();
    int h = GetRenderHeight();
    // Calculate the position of the rectangle to be in the middle of the window
    // Rectangle rec = {(float)(screen_width - width) / 2, (float)(screen_height - height) / 2, width, height};
    Rectangle rec = {w/7, h/4, 0.7*w, 0.3*h};

    Color circle_colors[] = { green, yellow, orange, pink, blue, purple };


    DrawLine(560, 0, 560, screen_height, Fade(black, 0.6f));
    DrawRectangle(560, 0, screen_width - 500, screen_height, Fade(black, 0.3f));

    DrawRectangleRounded(rec, roundness, (int)segments, Fade(dark_blue, 0.2f));
    DrawRectangleRoundedLines(rec, roundness, (int)segments, line_thick, Fade(gray, 0.4f));

    
    const char* text = "HANGMAN GAME";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 30, 1);

    //float textX = rec.x + (rec.width - text_size.x) / 2;
    float textX = rec.x + w/5;
    // float textY = rec.y + (rec.height - text_size.y) / 2;
    float textY = rec.y + h/8;

    DrawText(text, textX, textY, h/14, WHITE);

    //circles
    float circle_radius = h/50;
    //float centerX = rec.x + rec.width / 2;
    float centerX = textX + w/5.5;
    //float centerY = rec.y + rec.height / 2;
    float centerY = rec.y + h/15;

    float total_width = 6 * (circle_radius * 2 + 5); // Total width of all circles and gaps

    float circlesY = textY - 30.0f; 

    for (int i = 0; i < 6; ++i) {
        // float circleX = centerX - total_width / 2 + i * (circle_radius * 2 + 5);
        // DrawCircle(circleX, circlesY, circle_radius, circle_colors[i]);
        float circleX = centerX - total_width / 2 + i * (circle_radius * 2 + 5);
        DrawCircle(circleX, centerY, circle_radius, circle_colors[i]);
    }

    // Rectangle button_rec = { centerX - 100 / 2, rec.y + rec.height + 10, 100, 50 };
    Rectangle button_rec = { rec.x + w/3.2, rec.y + h/3 + 10, 100, 50 };

    // Check if the mouse button is pressed within the button boundaries
    if (CheckCollisionPointRec(GetMousePosition(), button_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    DrawRectangleRec(button_rec, dark_blue);
    DrawText("START !", button_rec.x, button_rec.y + 7, h/18, yellow);
}

void updateWelcomePage(GameState* state,int screen_width,int screen_height){
    Rectangle rec = {screen_width/7, screen_height/4, 0.7*screen_width, 0.3*screen_height};
    Rectangle button_rec = { rec.x + screen_width/3.2, rec.y + screen_height/3 + 10, 100, 50 };
    if(CheckCollisionPointRec(GetMousePosition(), button_rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        state->current_page=MODE_SELECTION;
    }
}