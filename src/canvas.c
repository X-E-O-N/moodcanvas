#include "canvas.h"

Canvas CreateCanvas(int width, int height) {
    Canvas c;
    c.texture = LoadRenderTexture(width, height);
    c.width = width;
    c.height = height;

    BeginTextureMode(c.texture);
    ClearBackground((Color){180, 220, 255, 255});
    EndTextureMode();

    return c;
}

void BeginCanvasDraw(Canvas *c) {
    BeginTextureMode(c->texture);
    //BeginBlendMode(BLEND_ALPHA);
}

void EndCanvasDraw(void) {
    //EndBlendMode();
    EndTextureMode();
}

void DrawCanvas(Canvas *c) {
    DrawTextureRec(
        c->texture.texture,
        (Rectangle){0, 0, c->width, -c->height},
        (Vector2){0, 0},
        WHITE
    );
}
