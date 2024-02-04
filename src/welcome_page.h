#pragma once
#include "./state.h"

void drawWelcomePage(GameState* state,int screen_width,int screen_height);
void updateWelcomePage(GameState* state,int screen_width,int screen_height);

bool start_button_clicked = false;

void drawWelcomePage(GameState* state,int screen_width,int screen_height){
    float roundness = 1.0f;
    float width = 500.0f;
    float height = 120.0f;
    float segments = 0.0f;
    float line_thick = 3.0f;


    // Calculate the position of the rectangle to be in the middle of the window
    Rectangle rec = {(float)(screen_width - width) / 2, (float)(screen_height - height) / 2, width, height};

    Color black = (Color){ 0,0,0, 255 };
    Color gray = (Color){ 81,105,162, 255 };
    Color dark_blue = (Color){ 26,31,68, 0 };
    Color green = (Color){0,178,13, 255};
    Color purple = (Color){154,52,161,255};
    Color yellow = (Color){255,216,0,255};
    Color pink = (Color){232,0,145,255};
    Color blue = (Color){0,156,225,255};
    Color orange = (Color){255,141,0,255};

    DrawLine(560, 0, 560, screen_height, Fade(black, 0.6f));
    DrawRectangle(560, 0, screen_width - 500, screen_height, Fade(black, 0.3f));

    DrawRectangleRounded(rec, roundness, (int)segments, Fade(dark_blue, 0.2f));
    DrawRectangleRoundedLines(rec, roundness, (int)segments, line_thick, Fade(gray, 0.4f));

    
    const char* text = "HANGMAN GAME";
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 30, 1);

    float textX = rec.x + (rec.width - text_size.x) / 2;
    float textY = rec.y + (rec.height - text_size.y) / 2;

    DrawText(text, textX, textY, 30, WHITE);

    //circles
    float circle_radius = 10.0f;
    float centerX = rec.x + rec.width / 2;
    float centerY = rec.y + rec.height / 2;
    float total_width = 6 * (circle_radius * 2 + 5); // Total width of all circles and gaps

    float circlesY = textY - 30.0f; 
    Color circle_colors[] = { green, yellow, orange, pink, blue, purple };

    for (int i = 0; i < 6; ++i) {
        float circleX = centerX - total_width / 2 + i * (circle_radius * 2 + 5);
        DrawCircle(circleX, circlesY, circle_radius, circle_colors[i]);
    }

    Rectangle button_rec = { centerX - 100 / 2, rec.y + rec.height + 10, 100, 50 };
    // Check if the mouse button is pressed within the button boundaries
    if (CheckCollisionPointRec(GetMousePosition(), button_rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        start_button_clicked = true;
    } else {
        start_button_clicked = false;
    }

    DrawRectangleRec(button_rec, dark_blue);
    DrawText("START", button_rec.x + 10, button_rec.y + 7, 20, yellow);
}

void updateWelcomePage(GameState* state,int screen_width,int screen_height){
    if(start_button_clicked) state->current_page=SETTINGS_PAGE;

}