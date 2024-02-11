#pragma once
#include "./state.h"
#include "../includes/utils/file_parsing.h"
void drawSettingsPage(GameState* state,int screen_width,int screen_height);
void updateSettingsPage(GameState* state,int screen_width,int screen_height);

bool isMouseOverEasyButton;
bool isMouseOverMediumButton;
bool isMouseOverHardButton;

Color circleColors[] = {
    (Color){0, 178, 13, 255},    // #00b20d
    (Color){255, 216, 0, 255},   // #ffd800
    (Color){232, 0, 145, 255},   // #e80091
    (Color){0, 156, 225, 255},   // #009ce1
    (Color){255, 141, 0, 255},   // #ff8d00
    (Color){154, 52, 161, 255}   // #9a34a1
};

const int textSize= 30;
float roundness = 0.5f;
Color Darkblue = (Color){26, 31, 68, 255}; 
Color lightBlue = (Color){81, 105, 162, 255}; 
const int levelbuttonWidth = 200;
const int levelbuttonHeight = 50;

void drawSettingsPage(GameState* state,int screenWidth,int screenHeight){        
        int w = GetRenderWidth();
        int h = GetRenderHeight();

        Rectangle choiceRec ={w/7, h/4, 0.7*w, h*0.2};
        Rectangle easyRect = {w/7, h/4 + choiceRec.height + 0.1*h, w*0.2, (float)levelbuttonHeight};
        Rectangle mediumRect = {easyRect.x + easyRect.width +0.05*w, h/4 + choiceRec.height + 0.1*h , w*0.2, (float)levelbuttonHeight};
        Rectangle hardRect = {mediumRect.x + mediumRect.width +0.05*w , h/4 + choiceRec.height + 0.1*h , w*0.2, (float)levelbuttonHeight};


        float centerX = choiceRec.x + choiceRec.width / 2;
        float centerY = choiceRec.y + choiceRec.height / 2;

    
        DrawRectangleRounded(choiceRec, roundness, 0, Darkblue);
        DrawText("Choose your level !", centerX - (MeasureText("Choose your level !", textSize) / 2), centerY - (textSize / 2), textSize, WHITE);

        for(int i=0; i<6 ; i++) {
            DrawCircle(w/5 + i*(w*0.008 + w*0.012) , h/3.5, w*0.008, circleColors[i]);

        }

        Vector2 mousePosition = GetMousePosition();

        isMouseOverEasyButton = CheckCollisionPointRec(mousePosition, easyRect);
        isMouseOverMediumButton = CheckCollisionPointRec(mousePosition, mediumRect);
        isMouseOverHardButton = CheckCollisionPointRec(mousePosition, hardRect);


        DrawRectangleRounded(easyRect, roundness, 0, isMouseOverEasyButton ? lightBlue : Darkblue);
        DrawText("Easy", (int)(easyRect.x + easyRect.width / 2 - MeasureText("Easy", 20) / 2), (int)(easyRect.y + easyRect.height / 2 - 10), 20, WHITE);
        DrawRectangleRoundedLines(easyRect, roundness+0.1, 0, 5, lightBlue);


        DrawRectangleRounded(mediumRect, roundness, 0, isMouseOverMediumButton ? lightBlue : Darkblue);
        DrawText("Medium", (int)(mediumRect.x + mediumRect.width / 2 - MeasureText("Medium", 20) / 2), (int)(mediumRect.y + mediumRect.height / 2 - 10), 20, WHITE);
        DrawRectangleRoundedLines(mediumRect, roundness+0.1, 0, 5, lightBlue);

        DrawRectangleRounded(hardRect, roundness, 0, isMouseOverHardButton ? lightBlue : Darkblue);
        DrawText("Hard", (int)(hardRect.x + mediumRect.width / 2 - MeasureText("Hard", 20) / 2), (int)(hardRect.y + hardRect.height / 2 - 10), 20, WHITE);
        DrawRectangleRoundedLines(hardRect, roundness+0.1, 0, 5, lightBlue);       
        
        DrawRectangleRoundedLines(choiceRec, roundness+0.1, 0, 5, lightBlue);
}

void updateSettingsPage(GameState* state,int screen_width,int screen_height){
    
    state->attempt=0;
    WordList words= state->word_list;
    if (isMouseOverEasyButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        char* chosen_word = getRandomWord(EASY, words);
        state->word_to_guess=chosen_word;
        int len = strlen(chosen_word);
        state->curr_word_state=malloc((len + 1)*sizeof(char));
        char* underscores = (char*)malloc((len + 1) * sizeof(char));
        for(int i=0;i<len;i++)underscores[i]='_';
        strcpy(state->curr_word_state,underscores);
        printf("The chosen word is : %s \n", chosen_word);
        state->current_page=GAME_PAGE;
    }
    if (isMouseOverMediumButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        char* chosen_word = getRandomWord(MEDIUM, words);
        state->word_to_guess=chosen_word;
        int len = strlen(chosen_word);
        state->curr_word_state=malloc((len + 1)*sizeof(char));
        char* underscores = (char*)malloc((len + 1) * sizeof(char));
        for(int i=0;i<len;i++)underscores[i]='_';
        strcpy(state->curr_word_state,underscores);
        printf("The chosen word is : %s \n", chosen_word);
        state->current_page=GAME_PAGE;
    }
    if (isMouseOverHardButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        char* chosen_word = getRandomWord(HARD, words);
        state->word_to_guess=chosen_word;
        int len = strlen(chosen_word);
        state->curr_word_state=malloc((len + 1)*sizeof(char));
        char* underscores = (char*)malloc((len + 1) * sizeof(char));
        for(int i=0;i<len;i++)underscores[i]='_';
        strcpy(state->curr_word_state,underscores);
        printf("The chosen word is : %s \n", chosen_word);
        state->current_page=GAME_PAGE;
    }

}