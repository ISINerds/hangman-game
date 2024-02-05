#pragma once
#include "./state.h"
#include "./includes/data-structures/binary_tree.h"
#include "string.h"
void drawGamePage(GameState* state,int screen_width,int screen_height);
void updateGamePage(GameState* state,int screen_width,int screen_height);
// contains the current state of the word
void drawTop(GameState* state,Rectangle top_rect){
    DrawRectangleRoundedLines(top_rect,0.2,1,1,ColorFromHSV(120,1,1));
}
// DrawRectangleRoundedLines(keyboard_rect,0.2,1,1,ColorFromHSV(120,1,1));
void drawKeyboard(GameState* state, Rectangle keyboard_rect) {
    int width = keyboard_rect.width;
    int height = keyboard_rect.height;
    int padding = width * 0.05;
    int num_letters = 5;
    int num_lines = 5;
    int lett_width = (width - 2 * padding - (num_letters - 1) * padding) / num_letters;
    int lett_height = (height - (num_lines - 1) * padding) / num_lines;
    lett_height*=0.8;
    int kk=0;
    for (int line = 0; line < num_lines; line++) {
        for (int column = 0; column < num_letters + (line == num_lines - 1); column++) {
            Rectangle letterRect = {
                .x = keyboard_rect.x + column * lett_width + column * padding + ((lett_width + padding) / 2)*(line != num_lines - 1),
                .y = keyboard_rect.y + line * lett_height + line * padding,
                .width = lett_width,
                .height = lett_height
            };
            // printf("%c\n",);
            if (CheckCollisionPointRec(GetMousePosition(), letterRect)&&(state->keyboard).keys[kk].state == KEY_NOT_CLICKED) {
                DrawRectangleRounded(
                    (Rectangle){
                    .x=letterRect.x - 2,
                    .y=letterRect.y - 2,
                    .width=letterRect.width + 4,
                    .height=letterRect.height + 4,
                },0.8,1,(Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});
                DrawRectangleRoundedLines(letterRect, 0.8, 1, 3, (Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});
            } else {
                if((state->keyboard).keys[kk].state == KEY_NOT_CLICKED){
                    DrawRectangleRounded(
                        (Rectangle){
                        .x=letterRect.x - 2,
                        .y=letterRect.y - 2,
                        .width=letterRect.width + 4,
                        .height=letterRect.height + 4,
                    },0.8,1,(Color){.r=0x1A,.g=0x1F,.b=0x44,.a=255});
                    DrawRectangleRoundedLines(letterRect, 0.8, 1, 3, (Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});
                }else if ((state->keyboard).keys[kk].state == KEY_WRONG){
                    DrawRectangleRounded(
                        (Rectangle){
                        .x=letterRect.x - 2,
                        .y=letterRect.y - 2,
                        .width=letterRect.width + 4,
                        .height=letterRect.height + 4,
                    },0.8,1,(Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});
                    DrawRectangleRoundedLines(letterRect, 0.8, 1, 3, (Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});
                }else if ((state->keyboard).keys[kk].state == KEY_CORRECT){
                    DrawRectangleRounded(
                        (Rectangle){
                        .x=letterRect.x - 2,
                        .y=letterRect.y - 2,
                        .width=letterRect.width + 4,
                        .height=letterRect.height + 4,
                    },0.8,1,(Color){.r=0x00,.g=0xb2,.b=0x0d,.a=255});
                    DrawRectangleRoundedLines(letterRect, 0.8, 1, 3, (Color){.r=0x51,.g=0x69,.b=0xA2,.a=255});

                }
            }
            int fontSize = (lett_width < lett_height) ? lett_width / 2 : lett_height / 2;
            int textX = letterRect.x + (letterRect.width - MeasureText("A", fontSize)) / 2;
            int textY = letterRect.y + (letterRect.height - fontSize) / 2;
            DrawText(TextFormat("%c",(state->keyboard).keys[kk].character), textX, textY, fontSize, RAYWHITE);
            kk++;
        }
    }
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
    Rectangle keyboard_rect = {
        .x = (screen_width*0.05),
        .y = (screen_height*0.04) + screen_height*0.125 + (screen_height*0.04),
        .width = screen_width*0.4,
        .height = screen_height*0.7,
    };

    int width = keyboard_rect.width;
    int height = keyboard_rect.height;
    int padding = width * 0.05;
    int num_letters = 5;
    int num_lines = 5;
    int lett_width = (width - 2 * padding - (num_letters - 1) * padding) / num_letters;
    int lett_height = (height - (num_lines - 1) * padding) / num_lines;
    lett_height*=0.8;
    int kk=0;
    for (int line = 0; line < num_lines; line++) {
        for (int column = 0; column < num_letters + (line == num_lines - 1); column++) {
            Rectangle letterRect = {
                .x = keyboard_rect.x + column * lett_width + column * padding + ((lett_width + padding) / 2)*(line != num_lines - 1),
                .y = keyboard_rect.y + line * lett_height + line * padding,
                .width = lett_width,
                .height = lett_height
            };
            if(CheckCollisionPointRec(GetMousePosition(),letterRect)&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&&(state->keyboard).keys[kk].state==KEY_NOT_CLICKED){
                int n = strlen(state->word_to_guess);
                int* arr_pos = (int*)malloc(sizeof(int)*n);
                for(int i=0;i<n;i++){
                    arr_pos[i]=0;
                }
                getletterIndex(arr_pos,0,(char)((state->keyboard).keys[kk].character+('a'-'A')),state->word_to_guess,state->root);
                int ok=0;
                for(int i=0;i<n;i++){
                    if(arr_pos[i]){
                        (state->curr_word_state)[i]=(state->keyboard).keys[kk].character;
                        ok=1;
                    }
                }
                printf("state = %s\n",state->curr_word_state);
                (state->keyboard).keys[kk].state=ok?KEY_CORRECT:KEY_WRONG;
                if(ok){
                    state->attempt++;
                }
                free(arr_pos);
            }
            kk++;
        }
    }

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