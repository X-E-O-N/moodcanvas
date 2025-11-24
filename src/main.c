#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "canvas.h"
#include "mood.h"
#include "ui.h"

#define UI_HEIGHT 90

// initialize/declare global variables

char statusText[64];
int statusTimer = 0;
Canvas canvas;
// Color currentBG;
// Color targetBG;
// float moodTransition = 1.0f;
Color selectedColor;
int brushSize;
float brushOpacity;
bool eraserMode = false;
Vector2 lp = {0, 0};
UIState uiState;


int main(void){

    // initialize window and canvas

    const int screenWidth = 1024;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "raylib test");
    SetTargetFPS(60);

    canvas = CreateCanvas(screenWidth, screenHeight);

    // set brush and canvas properties from default mood, sync to ui

    Mood currentMood = MOOD_CALM;
    Mood clickedMood = currentMood;
    MoodProfile moodProfile = GetMoodProfile(currentMood);

    selectedColor = moodProfile.brushColor;
    uiState.brushSize = moodProfile.brushSize;
    uiState.brushOpacity = moodProfile.brushOpacity;
    uiState.eraser = false;
    uiState.sizeLevel = 1;
    uiState.opacityLevel = 1;
    brushSize = uiState.brushSize;
    brushOpacity = uiState.brushOpacity;
    eraserMode = uiState.eraser;

    mkdir("exports", 0777);

    // runtime

    while (!WindowShouldClose()){

        // click a mood button to change to the corresponding mood

        if (clickedMood != currentMood) {
            currentMood = clickedMood;
            MoodProfile newProfile = GetMoodProfile(currentMood);


            // change brush properties according to selected mood

            selectedColor = newProfile.brushColor;
            uiState.brushSize = newProfile.brushSize;
            uiState.brushOpacity = newProfile.brushOpacity;
            uiState.eraser = false;
            uiState.requestClear = false;

            if (uiState.brushSize <= 5) uiState.sizeLevel = 0;
            else if (uiState.brushSize <= 12) uiState.sizeLevel = 1;
            else uiState.sizeLevel = 2;

            if (uiState.brushOpacity <= 0.3f) uiState.opacityLevel = 0;
            else if (uiState.brushOpacity <= 0.8f) uiState.opacityLevel = 1;
            else uiState.opacityLevel = 2;


            moodProfile = newProfile;

            // background transition on mood change

            // currentBG = moodProfile.backgroundColor;
            // targetBG = newProfile.backgroundColor;
            // moodTransition = 0.0f;

            // if (moodTransition < 1.0f) {
            //     moodTransition += 0.04f;

            //     Color blended = {
            //         (unsigned char)Lerp(currentBG.r, targetBG.r, moodTransition),
            //         (unsigned char)Lerp(currentBG.g, targetBG.g, moodTransition),
            //         (unsigned char)Lerp(currentBG.b, targetBG.b, moodTransition),
            //         255
            //     };
            // }

            // draw canvas bg

            BeginCanvasDraw(&canvas);
            ClearBackground(moodProfile.backgroundColor);
            EndCanvasDraw();
        }

        // clear canvas

        if (uiState.requestClear) {
            BeginCanvasDraw(&canvas);
            ClearBackground(moodProfile.backgroundColor);
            EndCanvasDraw();

            uiState.requestClear = false;
        }

        // drawing logic
        
        Vector2 mp = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mp.y > UI_HEIGHT) {
            lp = mp;
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mp.y > UI_HEIGHT) { 
            BeginCanvasDraw(&canvas);
            Color drawCol = eraserMode ? moodProfile.backgroundColor : Fade(selectedColor, brushOpacity);
            DrawLineEx(lp, mp, brushSize * 2.2f, drawCol);
            DrawCircleV(mp, brushSize, drawCol);

            EndCanvasDraw();
            lp = mp;
        } 

        // save as png

        if (IsKeyPressed(KEY_S)) {
            Image img = LoadImageFromTexture(canvas.texture.texture);
            ImageFlipVertical(&img);
            ExportImage(img, "untitled.png");
            UnloadImage(img);

            strcpy(statusText, "Saved as untitled.png");
            statusTimer = 120;
        }

        // draw canvas and ui elements

        BeginDrawing();
        ClearBackground(moodProfile.backgroundColor);

        DrawCanvas(&canvas);
        DrawMoodButtons(currentMood, &clickedMood, &selectedColor, &uiState);

        // set brush properties according to selected settings

        brushSize = uiState.brushSize;
        brushOpacity = uiState.brushOpacity;
        eraserMode = uiState.eraser;

        // draw circle on cursor/current stroke area

        if (mp.y > 80) {
            if (!eraserMode) {
                DrawCircleLines(mp.x, mp.y, brushSize, selectedColor);
            } else {
                DrawCircleLines(mp.x, mp.y, brushSize, RED);
            }
        }

        // display status timer

        if (statusTimer > 0) {
            DrawText(statusText, 20, screenHeight - 40, 20, BLACK);
            statusTimer--;
        }

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
