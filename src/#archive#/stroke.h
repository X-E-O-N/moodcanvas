#ifndef STROKE_H
#define STROKE_H

#include "brush.h"

typedef struct {
    Vector2 *points;
    Brush brush;
    int pointCount;
    int layerIndex;
} Stroke;

typedef struct {
    Stroke *items;
    int count;
    int capacity;
} StrokeStack;

void InitStrokeStack(StrokeStack *stack);
void PushStroke(StrokeStack *stack, Stroke s);
Stroke PopStroke(StrokeStack *stack);
void FreeStroke(Stroke *s);

#endif