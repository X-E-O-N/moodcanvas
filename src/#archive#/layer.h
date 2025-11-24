#ifndef LAYER_H
#define LAYER_H

#include "raylib.h"

typedef struct {
    RenderTexture2D tex;
    bool visible;
    char name[32];
} Layer;

Layer CreateLayer(int w, int h, const char *name);
void DrawLayer(Layer *layer, int x, int y);

#endif
