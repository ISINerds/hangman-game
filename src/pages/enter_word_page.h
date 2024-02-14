#pragma once
#include "./state.h"
#include "../includes/utils/file_parsing.h"
#include "../includes/data-structures/binary_tree.h"
void drawEnterWordPage(GameState* state,int screen_width,int screen_height);
void updateEnterWordPage(GameState* state,int screen_width,int screen_height);
bool show_popup=false;
bool empty_message=false;
bool ewp_is_mouse_over_back_button=false;
bool ewAllAlpha(const char *text_input) {
    for (int i = 0; text_input[i] != '\0'; i++) {
        if (!isalpha(text_input[i]))return false;
    }
    return true;
}

void drawEnterWordPage(GameState* state,int screen_width,int screen_height){
    int w = GetRenderWidth();
    int h = GetRenderHeight();

    
    DrawTexturePro(back_button,
                (Rectangle){ 0, 0, (float)back_button.width, (float)back_button.height },
                (Rectangle){30,0,60,60},
                (Vector2){ 0, 0},
                0.0f,
                WHITE);
    Vector2 mousePosition = GetMousePosition();

    ewp_is_mouse_over_back_button = CheckCollisionPointRec(mousePosition, (Rectangle){30,0,60,60});
    const int textSize= screen_height/13;
    float roundness = 0.5f;
    Color Darkblue = (Color){26, 31, 68, 255}; 
    Color lightBlue = (Color){81, 105, 162, 255}; 

    Color circleColors[] = {
        (Color){0, 178, 13, 255},    // #00b20d
        (Color){255, 216, 0, 255},   // #ffd800
        (Color){232, 0, 145, 255},   // #e80091
        (Color){0, 156, 225, 255},   // #009ce1
        (Color){255, 141, 0, 255},   // #ff8d00
        (Color){154, 52, 161, 255}   // #9a34a1
    };
    


    Rectangle choiceRec ={screen_width/7, screen_height/4, 0.7*screen_width, screen_height*0.2};
    
    DrawRectangleRounded(choiceRec, roundness, 0, Darkblue);
    DrawText("PLAYER 1", choiceRec.x + choiceRec.width / 2 - (MeasureText("PLAYER 1", textSize) / 2), choiceRec.y + choiceRec.height / 6, textSize, (Color){255, 216, 0, 255});
    DrawText("Enter your word", choiceRec.x + choiceRec.width / 2 - (MeasureText("Enter your word", textSize*0.5) / 2), choiceRec.y + choiceRec.height/1.8, textSize*0.5, WHITE);

    for(int i=0; i<6 ; i++) {
        DrawCircle(screen_width/5 + i*(screen_width*0.008 + screen_width*0.012) , screen_height/3.5, screen_width*0.008, circleColors[i]);
    }
    DrawRectangleRoundedLines(choiceRec, roundness+0.1, 0, 5, lightBlue);
    Rectangle input_box={
        (screen_width-0.3*screen_width)/2,
        1.3*screen_height/4+screen_height*0.2,
        screen_width*0.3,
        screen_height*0.07
    };
    GuiTextBox(input_box, text_input, 255, true);
    Rectangle go_button={
        (screen_width-0.3*screen_width)/2 +screen_width*0.3/2 - MeasureText("GO",textSize)/2,
        1.3*screen_height/4+screen_height*0.2 + 1.5*(screen_height*0.07),
        MeasureText("GO",textSize),
        textSize
    };
    if(CheckCollisionPointRec(GetMousePosition(), go_button)){
        DrawText("GO",go_button.x, go_button.y, textSize, (Color){255, 216, 0, 255});
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }else{
        DrawText("GO",go_button.x, go_button.y, textSize, (Color){255, 216, 0, 255});
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    if(show_popup){
        int res = GuiMessageBox((Rectangle){ (screen_width-(empty_message?screen_width*0.4:screen_width*0.65))/2, screen_height/2 - screen_height*0.3, empty_message?screen_width*0.4:screen_width*0.65, screen_height*0.4 }, GuiIconText(ICON_INFO, "Info"),empty_message?"The word cannot be empty.":"The word should only contain alphabetic characters.","ok");
        if(res==1||res==0)show_popup=false;
    }
}
void updateEnterWordPage(GameState* state,int screen_width,int screen_height){
    const int textSize= screen_height/15;
    Rectangle go_button={
        (screen_width-0.3*screen_width)/2 +screen_width*0.3/2 - MeasureText("GO",textSize)/2,
        1.3*screen_height/4+screen_height*0.2 + 1.5*(screen_height*0.07),
        MeasureText("GO",textSize),
        textSize
    };

    if(CheckCollisionPointRec(GetMousePosition(), go_button)&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(text_input[0]!='\0'&&ewAllAlpha(text_input)){
            for (int i = 0; text_input[i]; i++) {
                text_input[i] = tolower(text_input[i]);
            }
            char* chosen_word = text_input;
            int len = strlen(chosen_word);
            state->word_to_guess=(char*)malloc((len + 1) * sizeof(char));
            strcpy(state->word_to_guess,text_input);
            state->curr_word_state=(char*)malloc((len + 1) * sizeof(char));
            char* underscores = (char*)malloc((len + 1) * sizeof(char));
            for(int i=0;i<len;i++)underscores[i]='_';
            strcpy(state->curr_word_state,underscores);
            state->root=addWordToBinaryTree(state->word_to_guess,state->root);
            state->current_page=GAME_PAGE;
            state->attempt=0;
            strcpy(text_input,"");
        }else{
            show_popup=true;
            if(text_input[0]=='\0'){
                empty_message=true;
            }else{
                empty_message=false;
            }
        }
    }
    if(ewp_is_mouse_over_back_button&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        state->current_page=MODE_SELECTION;
    }

}