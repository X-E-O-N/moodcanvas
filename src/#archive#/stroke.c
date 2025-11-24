#include "stroke.h"
#include <stdlib.h>
#include <string.h>

void InitStrokeStack(StrokeStack *stack) {
    stack->capacity = 1000;
    stack->count = 0;
    stack->items = malloc(sizeof(Stroke) * stack->capacity);
}

void PushStroke(StrokeStack *stack, Stroke s) {
    if (stack->count < stack->capacity) {
        stack->items[stack->count++] = s;
    }
}

Stroke PopStroke(StrokeStack *stack) {
    Stroke empty = {0};
    if (stack->count == 0) return empty;
    return stack->items[--stack->count];
}

void FreeStroke(Stroke *s) {
    if (s->points) free(s->points);
}