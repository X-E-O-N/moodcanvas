#include "raylib.h"

#ifndef MOOD_H
#define MOOD_H

typedef enum {
    MOOD_CALM = 0,
    MOOD_HAPPY,
    MOOD_ANGRY,
    MOOD_SAD,
    MOOD_COUNT
} Mood;

typedef struct {
    Color backgroundColor;
    Color uiColor;
    Color brushColor;
    int brushSize;
    float brushOpacity;
} MoodProfile;

MoodProfile GetMoodProfile(Mood mood);

#endif
