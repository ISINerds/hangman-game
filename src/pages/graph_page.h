#pragma once
#include "./state.h"
#include "../includes/data-structures/binary_tree.h"

void drawGraphPage(GameState* state,int screen_width,int screen_height);
void updateGraphPage(GameState* state,int screen_width,int screen_height);
Texture2D gp_graph_texture;
bool one_time=true;
Camera2D camera = {
    .target = { 0.0f, 0.0f },
    .offset = { 0.0f, 0.0f },
    .rotation = 0.0f,
    .zoom = 1.0f
};
Vector2 mouse_position = { 0 };
Vector2 previous_mouse_position = { 0 };
bool is_dragging = false;
bool gp_is_mouse_over_back_button=false;
bool gp_show_popup=false;
bool gp_empty_message=false;
bool gp_word_dont_exist = false;
bool gp_show_popup_wdx = false;
float map(float value, float fromMin, float fromMax, float toMin, float toMax) {
    // Calculate the percentage of 'value' within the range (fromMin, fromMax)
    float percentage = (value - fromMin) / (fromMax - fromMin);

    // Map the percentage onto the range (toMin, toMax)
    return (percentage * (toMax - toMin)) + toMin;
}
bool gpAllAlpha(const char *text_input) {
    for (int i = 0; text_input[i] != '\0'; i++) {
        if (!isalpha(text_input[i]))return false;
    }
    return true;
}

char new_word[256] = ""; // Text input buffer
void drawGraphPage(GameState* state, int screen_width, int screen_height) {
    Rectangle scissorRect = {
        screen_width * 0.12f,
        screen_height * 0.13f,
        screen_width * 0.8f,
        screen_height * 0.8f
    };
    
    Rectangle input_box = { screen_width / 5, screen_height / 30, screen_width / 5, 30 };

    GuiTextBox(input_box, new_word, 255, true);

    if(GuiButton((Rectangle){ screen_width / 5 + screen_width / 5 + screen_width*0.03, screen_height / 30, 100, 30 }, "Add Word")){
        if(new_word[0]!='\0'&&gpAllAlpha(new_word)){
            state->root=addWordToBinaryTree(new_word,state->root);
            one_time=true;
        }else{
            gp_show_popup=true;
            if(new_word[0]=='\0'){
                gp_empty_message=true;
            }else{
                gp_empty_message=false;
            }
        }
    }
    if(GuiButton((Rectangle){ screen_width / 5 + screen_width / 5 + 2*screen_width*0.03 + 100, screen_height / 30 , 150, 30 }, "Remove Word")){
        if(new_word[0]!='\0'&&gpAllAlpha(new_word)){
            if(search_word(state->root,new_word)){
                state->root=removeWord(state->root,state->root,new_word);
                one_time=true;
            }else{
                gp_show_popup_wdx=true;
            }
        }else{
            gp_show_popup=true;
            if(new_word[0]=='\0'){
                gp_empty_message=true;
            }else{
                gp_empty_message=false;
            }
        }

    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_ZERO)) {
        camera.zoom=1.0f;
        camera.target = (Vector2){ 0.0f, 0.0f };
    }
    float circle_radius = screen_height/50.0;
    Color circle_colors_pg[6] = { (Color){0,178,13, 255}, (Color){255,216,0,255}, (Color){255,141,0,255}, (Color){232,0,145,255}, (Color){0,156,225,255}, (Color){154,52,161,255} };
    for (int i = 0; i < 6; ++i) {        
        DrawCircle(screen_width-(6-i)*2.5*circle_radius,2*circle_radius , circle_radius, circle_colors_pg[i]);
    }

    if(is_dragging){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    DrawTexturePro(back_button,
            (Rectangle){ 0, 0, (float)back_button.width, (float)back_button.height },
            (Rectangle){30,0,30,30},
            (Vector2){ 0, 0},
            0.0f,
            WHITE);


    gp_is_mouse_over_back_button = CheckCollisionPointRec(GetMousePosition(), (Rectangle){30,0,30,30});

    previous_mouse_position = mouse_position;
    mouse_position = GetMousePosition();

    // Update camera position based on arrow key inputs
    if (IsKeyDown(KEY_LEFT)) {
        camera.target.x -= 10.0f;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        camera.target.x += 10.0f;
    }
    if (IsKeyDown(KEY_UP)) {
        camera.target.y -= 10.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        camera.target.y += 10.0f;
    }

    // Start dragging
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&&CheckCollisionPointRec(GetMousePosition(),scissorRect)) {
        is_dragging = true;
    }

    // Continue dragging
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && is_dragging) {
        camera.target.x -= (mouse_position.x - previous_mouse_position.x)*map(1-(camera.zoom-0.25),0.25,1,1,5);
        camera.target.y -= (mouse_position.y - previous_mouse_position.y)*map(1-(camera.zoom-0.25),0.25,1,1,5);
    }
    // End dragging
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        is_dragging = false;
    }

    if(camera.target.x<=0){
        camera.target.x=0;
    }
    if(camera.target.y<=0){
        camera.target.y=0;
    }

    if(camera.target.x+scissorRect.width>=gp_graph_texture.width){
        camera.target.x=gp_graph_texture.width-scissorRect.width;
    }
    if(camera.target.y+scissorRect.height>=gp_graph_texture.height){
        camera.target.y=gp_graph_texture.height-scissorRect.height;
    }

    BeginMode2D(camera);

    BeginScissorMode((int)scissorRect.x, (int)scissorRect.y, (int)scissorRect.width, (int)scissorRect.height);

    DrawTexture(gp_graph_texture, scissorRect.x, scissorRect.y, WHITE);

    EndScissorMode();

    EndMode2D();

    if(gp_show_popup){
        int res = GuiMessageBox((Rectangle){ (screen_width-(gp_empty_message?screen_width*0.4:screen_width*0.65))/2, screen_height/2 - screen_height*0.3, gp_empty_message?screen_width*0.4:screen_width*0.65, screen_height*0.4 }, GuiIconText(ICON_INFO, "Info"),gp_empty_message?"The word cannot be empty.":"The word should only contain alphabetic characters.","ok");
        if(res==1||res==0)gp_show_popup=false;
    }
    if(gp_show_popup_wdx){
        int res = GuiMessageBox((Rectangle){ (screen_width-screen_width*0.4)/2, screen_height/2 - screen_height*0.3, screen_width*0.4, screen_height*0.4 }, GuiIconText(ICON_INFO, "Info"),"Word does not exist","ok");
        if(res==1||res==0)gp_show_popup_wdx=false;
    }

}

void updateGraphPage(GameState* state,int screen_width,int screen_height){
    if(one_time){
        DrawText("Loading, please wait...", screen_width / 2 - MeasureText("Loading, please wait...", 20) / 2, screen_height / 2 - 10, 20, WHITE);
        EndDrawing();
        generateImageFromBinaryTree(state->root,"./build/tree","./assets/tree.gv");        
        gp_graph_texture = LoadTexture("./build/tree.png");
        
        // camera.target = (Vector2){ 0.0f, 0.0f };

        // camera.offset = (Vector2){ 0.0f,0.0f };
        // camera.rotation = 0.0f;
        // camera.zoom = 1.0f;
        one_time=false;
    }
    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
    if(camera.zoom>1.0){
        camera.zoom=1.0;
    }
    if(camera.zoom<0.25){
        camera.zoom=0.25;
    }
    if(gp_is_mouse_over_back_button&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        gp_show_popup=false;
        one_time=true;
        is_dragging = false;
        gp_empty_message=false;
        gp_word_dont_exist = false;
        gp_show_popup_wdx = false;
        strcpy(new_word,"");
        state->current_page=MODE_SELECTION;
    }
}