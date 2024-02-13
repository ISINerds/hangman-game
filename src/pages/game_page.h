#pragma once
#include "./state.h"
#include "../includes/data-structures/binary_tree.h"
#include "string.h"
#include<ctype.h>
void drawGamePage(GameState* state,int screen_width,int screen_height);
void updateGamePage(GameState* state,int screen_width,int screen_height);
bool replay_button_clicked = false;
bool game_over = false;
bool win = true;
bool isMouseOverBackButton;
static bool winSoundPlayed = false; 
static bool loseSoundPlayed = false; 

// contains the current state of the word

bool compareString(char* s1,char* s2){
    int i=0,j=0;
    while(s1[i]!='\0'&&s2[j]!='\0'){
        if(tolower(s1[i])!=tolower(s2[j]))return false;
        i++;
        j++;
    }
    return true;
}

void drawTop(GameState* state,Rectangle top_rect){
    //circles
    float circle_radius = 10.0f;
    float circles_total_width = 6 * (circle_radius * 2 + 5); // Total width of all circles and gaps

    int w = GetRenderWidth();
    int h = GetRenderHeight();
    DrawTexturePro(back_button,
                (Rectangle){ 0, 0, (float)back_button.width, (float)back_button.height },
                (Rectangle){30,0,60,60},
                (Vector2){ 0, 0},
                0.0f,
                WHITE);

    Vector2 mousePosition = GetMousePosition();

    isMouseOverBackButton = CheckCollisionPointRec(mousePosition, (Rectangle){30,0,60,60});

    float scaleFactor = 0.5f + 0.5f * sinf(GetTime() * (state->attempt+4)); // Adjust the speed of pulsation with the multiplier
    Rectangle heartRect = {
        top_rect.x + top_rect.width / 1.2,
        top_rect.y + h/25,
        (float)heart_texture.width * scaleFactor,
        (float)heart_texture.height * scaleFactor
    };

    if ((6 - state->attempt) % 7 == 1 && !game_over) {
        if (!IsSoundPlaying(heart_beating)) {
            PlaySound(heart_beating);
        }
    } else if (game_over || (6 - state->attempt) % 7 == 0)  {
        StopSound(heart_beating);
    }
    
    DrawTexturePro(heart_texture, (Rectangle){ 0, 0, (float)heart_texture.width, (float)heart_texture.height },
                   heartRect, (Vector2){ heartRect.width / 2, heartRect.height / 2 }, 0.0f, WHITE);
    char attempts[2];
    sprintf(attempts, "%d",(6 - state->attempt)%7);



    //DrawText(attempts, hangman_rect.x + hangman_rect.width / 1.3 + screen_width/10 , hangman_rect.y - screen_height/5, 25, WHITE);
    DrawText(attempts, heartRect.x + w/35 , heartRect.y - h/55, h/22, PURPLE);

    //state->curr_word_state = "_______";
    // DrawRectangleRoundedLines(top_rect,0.2,1,1,ColorFromHSV(120,1,1));
    if(state->curr_word_state != NULL){
        int font_size= 50;
        int letter_spacing=w/48;
        int word_width = MeasureText(state->curr_word_state, font_size);
        // int wordX = top_rect.x + circles_total_width + (top_rect.width-circles_total_width - word_width) / 2;
        int wordX= w/2.5;
        int wordY = (top_rect.height) / 2;


        for (int i = 0; i < strlen(state->word_to_guess); i++){
            DrawText(TextFormat("%c", toupper(state->curr_word_state[i])), wordX + i * (letter_spacing + 20), wordY, h/20, WHITE);
        }
    }
    // printf("comp  = %d , wtg = %s ,wcs= %s\n",compareString(state->curr_word_state,state->word_to_guess),state->word_to_guess,state->curr_word_state);
}

void drawWinLoseMessage(GameState* state, Rectangle keyboard_rect){
    float roundness = 0.5f;
    float width = keyboard_rect.width-0.5;
    float height = keyboard_rect.height-0.5;
    float segments = 0.0f;
    float line_thick = 3.0f;

    int w = GetRenderWidth();
    int h = GetRenderHeight();
    // Calculate the position of the rectangle to be in the middle of the window
    Rectangle rec = {keyboard_rect.x+(float)(keyboard_rect.width - width) / 2, keyboard_rect.y+(float)(keyboard_rect.height - height) / 2, width, height};

    Color circle_colors[] = { green, yellow, orange, pink, blue, purple };


    DrawLine(560, 0, 560, keyboard_rect.height, Fade(black, 0.6f));
    DrawRectangle(560, 0, keyboard_rect.width - 500, keyboard_rect.height, Fade(black, 0.3f));

    DrawRectangleRounded(rec, roundness, (int)segments, Fade(dark_blue, 0.2f));
    DrawRectangleRoundedLines(rec, roundness, (int)segments, line_thick, Fade(gray, 0.4f));
    
    const char* text =win?(state->mode==ONE_PLAYER?"YOU WON":"PLAYER2 WON"):(state->mode==ONE_PLAYER?"YOU LOST":"PLAYER2 LOST");
    Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 30, 1);
    float textX = rec.x + w/9;
    float textY = rec.y + h/7;
    DrawText(text, textX, textY, h/14, pink);
    
    const char* text1 = "THE WORD WAS";
    Vector2 text_size1 = MeasureTextEx(GetFontDefault(), text1, 5, 1);
    float text1X = rec.x + w/14;
    float text2Y = rec.y + h/3.5;
    DrawText(text1, text1X, text2Y, h/14, WHITE);

    const char* word = state->word_to_guess;
    Vector2 word_size = MeasureTextEx(GetFontDefault(), word, 5, 1);
    float wordX = (strlen(word)<=3) ? rec.x + w/(1.9*strlen(word)) : (strlen(word)<=5) ? rec.x + w/(1.55*strlen(word)): rec.x + w/(strlen(word));
    float wordY = rec.y + h/2.5;
    DrawText(word, wordX, wordY, h/14, WHITE);

    //circles
    float circle_radius = h/50;
    float centerX = textX + w/8.5;
    float centerY = rec.y + h/15;

    float total_width = 6 * (circle_radius * 2 + 5); // Total width of all circles and gaps

    float circlesY = textY - 30.0f; 

    for (int i = 0; i < 6; ++i) {
        float circleX = centerX - total_width / 2 + i * (circle_radius * 2 + 5);
        DrawCircle(circleX, centerY, circle_radius, circle_colors[i]);
    }

    Rectangle button_rec = { rec.x + w/6.8, rec.y + h/2.2 + 20, 100, 50 };

    DrawRectangleRec(button_rec, dark_blue);
    DrawText("REPLAY !", button_rec.x, button_rec.y + 7, h/18, yellow);

     if (CheckCollisionPointRec(GetMousePosition(), button_rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        replay_button_clicked = true;
    } else {
        replay_button_clicked = false;
    }
    if(game_over && win && !winSoundPlayed){
        if(IsSoundPlaying(heart_beating)) StopSound(heart_beating);
        if(!IsSoundPlaying(win_sound)) {
            PlaySound(win_sound);
            winSoundPlayed=true;
        }
    }
    if (!win && !loseSoundPlayed && game_over) {
        if(IsSoundPlaying(heart_beating)) StopSound(heart_beating);
        if(!IsSoundPlaying(wah_sound)) {
            PlaySound(wah_sound);
            loseSoundPlayed=true;
        }        
    }

}

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
    // }
}
void drawHangMan(GameState* state, Rectangle hangman_rect, int screen_width, int screen_height) {
    if (state->attempt >= 0 && state->attempt <= 6) {
        if (state->attempt == 6) {
            DrawTexture(blood_image, hangman_rect.x + screen_width / 8, hangman_rect.y + screen_height / 6, WHITE);
        }
        DrawTexturePro(hangman_images[state->attempt],
            (Rectangle){ 0, 0, (float)hangman_images[state->attempt].width, (float)hangman_images[state->attempt].height },
            hangman_rect,
            (Vector2){ hangman_rect.width / 20, hangman_rect.height / 20 }, // Adjust the division factor here
            0.0f,
            WHITE);
    } else {
        // printf("Invalid attempt value: %d\n", state->attempt);
        // printf("Not Implemented \n");
        // exit(1);
    }
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
    // TODO MAHA
    Rectangle keyboard_rect = {
        .x = (screen_width*0.05) + screen_width*0.4 + (screen_width*0.05),
        .y = (screen_height*0.04) + screen_height*0.125 + (screen_height*0.04),
        .width = screen_width*0.4,
        .height = screen_height*0.7,
    };
    if(!game_over){
        drawKeyboard(state,keyboard_rect) ;
    } else {
        drawWinLoseMessage(state, keyboard_rect);
    }
    Rectangle hangman_rect = {
        .x = (screen_width*0.05),
        .y = (screen_height*0.04) + screen_height*0.125 + (screen_height*0.04),
        .width = screen_width*0.4,
        .height = screen_height*0.7,
    };
    drawHangMan(state,hangman_rect,screen_width,screen_height);

}
void updateTop(GameState* state,int screen_width,int screen_height){
    if(compareString(state->curr_word_state,state->word_to_guess)==1||state->attempt==MAX_ATTEMPT){
        game_over=true;
        if(compareString(state->curr_word_state,state->word_to_guess)==0){
            win=false;
        }
    }
    if (isMouseOverBackButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        state->attempt = 0 ;
        state->keyboard = initKeyBoard();
        game_over=false;
        replay_button_clicked=false;
        state->current_page=MODE_SELECTION;
    }
}

int customIsKeyDown(KeyboardLayout layout){
    int keyPressed = GetKeyPressed();
    if((keyPressed==0 || keyPressed>90 || keyPressed<65)&&keyPressed!=KEY_SEMICOLON){
        return -1;
    }
    // printf("keypressed : %d\n",keyPressed);
    if(layout == US){
        return keyPressed-KEY_A;
    }else{
        switch (keyPressed){
        case KEY_Q:
            return 0; //A
        case KEY_A:
            return 16; //Q
        case KEY_Z:
            return 22; //W
        case KEY_W:
            return 25; //Z
        case KEY_SEMICOLON:
            return 12; //M
        default:
            return keyPressed-KEY_A;
        }
    }

}
void updateKeyboard(GameState* state,int screen_width,int screen_height){
    Rectangle keyboard_rect = {
        .x = (screen_width*0.05) + screen_width*0.4 + (screen_width*0.05),
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
                (state->keyboard).keys[kk].state=ok?KEY_CORRECT:KEY_WRONG;
                if(!ok){
                    state->attempt++;
                    PlaySound(fail_sound);
                }else{
                    PlaySound(success_sound);
                }
                free(arr_pos);
            }
            kk++;
        }
    }
    int index=0;
    if((index = customIsKeyDown(state->keyboard.keyboard_layout))!=-1&&(state->keyboard).keys[index].state==KEY_NOT_CLICKED){
        int n = strlen(state->word_to_guess);
        int* arr_pos = (int*)malloc(sizeof(int)*n);
        for(int j=0;j<n;j++){
            arr_pos[j]=0;
        }
        getletterIndex(arr_pos,0,(char)((state->keyboard).keys[index].character+('a'-'A')),state->word_to_guess,state->root);
        int ok=0;
        for(int j=0;j<n;j++){
            if(arr_pos[j]==1){
                (state->curr_word_state)[j]=(state->keyboard).keys[index].character;
                ok=1;
            }
        }
        free(arr_pos);
        (state->keyboard).keys[index].state=ok?KEY_CORRECT:KEY_WRONG;
        if(!ok){
            state->attempt++;
            PlaySound(fail_sound);
        }else{
            PlaySound(success_sound);
        }
    }
    


}
void updateHangMan(GameState* state,int screen_width,int screen_height){

}

void updateWinLoseMessage(GameState* state,int screen_width,int screen_height){
    if(replay_button_clicked){
            winSoundPlayed= false; loseSoundPlayed=false;
            state->attempt = 0 ;
            state->keyboard = initKeyBoard();
            game_over=false;
            replay_button_clicked=false;
            if(state->mode==TWO_PLAYERS){
                state->current_page=ENTER_WORD_PAGE;
                return;
            }
            char* chosen_word = getRandomWord(state->game_difficulty, state->word_list);
            printf("game diff = %d\n",state->game_difficulty);
            state->word_to_guess=chosen_word;
            int len = strlen(chosen_word);
            state->curr_word_state=(char*)malloc((len + 1)*sizeof(char));
            char* underscores = (char*)malloc((len + 1) * sizeof(char));
            for(int i=0;i<len;i++)underscores[i]='_';
            strcpy(state->curr_word_state,underscores);
            printf("%s\n",state->word_to_guess);
    }
}


void updateGamePage(GameState* state,int screen_width,int screen_height){
    updateTop(state,screen_width,screen_height);
    if(!game_over){
        updateKeyboard(state,screen_width,screen_height);
        updateHangMan(state,screen_width,screen_height);
    }else {
        updateWinLoseMessage(state, screen_width,screen_height);
    }
    // char *msg1, *msg2;
    // msg1 = (char*)malloc(sizeof(char)*100);
    // msg2 = (char*)malloc(sizeof(char)*100);
    // getEndGameMessages(state, 6, msg1, msg2);
    
    // if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //     state->current_page=WELCOME_PAGE;
    // }
}