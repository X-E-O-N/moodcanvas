#ifndef CANVAS_H
#define CANVAS_H

#include "raylib.h"

typedef struct {
    RenderTexture2D texture;
    int width;
    int height;
} Canvas;

Canvas CreateCanvas(int width, int height);
void BeginCanvasDraw(Canvas *c);
void EndCanvasDraw(void);
void DrawCanvas(Canvas *c);

#endif
