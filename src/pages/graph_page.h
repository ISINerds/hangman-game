#pragma once
#include "./state.h"
#include "../includes/data-structures/binary_tree.h"

void drawGraphPage(GameState* state,int screen_width,int screen_height);
void updateGraphPage(GameState* state,int screen_width,int screen_height);
Texture2D gp_graph_texture;
bool one_time=true;
Camera2D camera = { 0 };
Vector2 mouse_position = { 0 };
Vector2 previous_mouse_position = { 0 };
bool is_dragging = false;
bool gp_is_mouse_over_back_button=false;
void drawGraphPage(GameState* state, int screen_width, int screen_height) {

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
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        is_dragging = true;
    }

    // Continue dragging
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && is_dragging) {
        camera.target.x -= (mouse_position.x - previous_mouse_position.x);
        camera.target.y -= (mouse_position.y - previous_mouse_position.y);
    }
    // End dragging
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        is_dragging = false;
    }


    Rectangle scissorRect = {
        screen_width * 0.1f,
        screen_height * 0.1f,
        screen_width * 0.8f,
        screen_height * 0.8f
    };

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
}

void updateGraphPage(GameState* state,int screen_width,int screen_height){
    if(one_time){
        DrawText("Loading, please wait...", screen_width / 2 - MeasureText("Loading, please wait...", 20) / 2, screen_height / 2 - 10, 20, WHITE);
        EndDrawing();
        generateImageFromBinaryTree(state->root,"./build/tree","./assets/tree.gv");        
        gp_graph_texture = LoadTexture("./build/tree.png");
        // camera.target = (Vector2){ gp_graph_texture.width / 2.0f, gp_graph_texture.height / 2.0f };
        camera.target = (Vector2){ 0.0f, 0.0f };
        // camera.offset = (Vector2){ screen_width / 2.0f, screen_height / 2.0f };
        camera.offset = (Vector2){ 0.0f,0.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        one_time=false;
    }
    camera.zoom += ((float)GetMouseWheelMove() * 0.05f);
    if(gp_is_mouse_over_back_button&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        state->current_page=MODE_SELECTION;
    }
}
// Image graph_image;
// Texture2D gp_graph_texture;
// bool one_time=true;
// void drawGraphPage(GameState* state,int screen_width,int screen_height){
//     DrawTexture(gp_graph_texture, 0, 0, WHITE);
// }

// void updateGraphPage(GameState* state,int screen_width,int screen_height){
//     if(one_time){
//         generateImageFromBinaryTree(state->root,"./build/tree","./assets/tree.gv");
//         graph_image=LoadImageSvg("./build/tree.svg", screen_width, screen_height);
//         gp_graph_texture=LoadTextureFromImage(graph_image);
//         one_time=false;
//     }

// }