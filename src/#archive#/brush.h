#ifndef BRUSH_H
#define BRUSH_H

#include <stdbool.h>
#include "raylib.h"

typedef enum {
    BRUSH_ROUND = 0,
    BRUSH_SMOOTH,
    BRUSH_STAMP
} BrushType;

typedef struct {
    BrushType type;
    Color color;
    int size;
    float opacity;
    bool smoothEnabled;
} Brush;

Brush CreateBrush(Color c, int size, float opacity);
void ApplyBrushStroke(Brush *brush, Vector2 *points, int pointCount, RenderTexture2D target);

#endif

