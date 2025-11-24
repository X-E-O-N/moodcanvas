#include "layer.h"
#include <string.h>

Layer CreateLayer(int w, int h, const char *name) {
    Layer l;
    l.tex = LoadRenderTexture(w, h);
    l.visible = true;
    strcpy(l.name, name);

    BeginTextureMode(l.tex);
    ClearBackground(BLANK);
    EndTextureMode();

    return l;
}

void DrawLayer(Layer *layer, int x, int y) {
    if (!layer->visible) return;
    DrawTextureRec(
        layer->tex.texture,
        (Rectangle){0, 0, (float)layer->tex.texture.width, -(float)layer->tex.texture.height},
        (Vector2){x, y},
        WHITE
    );
}