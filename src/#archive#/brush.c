#include <math.h>
#include "brush.h"

Brush CreateBrush(Color c, int size, float opacity) {
    Brush b;
    b.type = BRUSH_ROUND;
    b.color = c;
    b.size = size;
    b.opacity = opacity;
    b.smoothEnabled = false;
    return b;
}

static void DrawSmoothStroke(Vector2 *points, int count, Color c, int size) {
    for (int i = 1; i < count; i++) {
        Vector2 p1 = points[i - 1];
        Vector2 p2 = points[i];
        DrawLineEx(p1, p2, size, c);
    }
}

static void DrawRoundStroke(Vector2 *points, int count, Color c, int size) {
    for (int i = 0; i < count; i++) {
        DrawCircleV(points[i], size, c);
    }
}

void ApplyBrushStroke(Brush *brush, Vector2 *points, int count, RenderTexture2D target) {
    BeginTextureMode(target);
    Color renderColor = Fade(brush -> color, brush -> opacity);

    switch (brush -> type) {
        case BRUSH_ROUND:
            DrawRoundStroke(points, count, renderColor, brush -> size);
            break;

        case BRUSH_SMOOTH:
            DrawSmoothStroke(points, count, renderColor, brush -> size);
            break;

        case BRUSH_STAMP:
            DrawRoundStroke(points, count,renderColor, brush -> size * 2);
            break;        
    }

    EndTextureMode();

}