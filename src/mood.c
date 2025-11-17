#include "mood.h"

MoodProfile GetMoodProfile(Mood mood) {
    switch(mood) {
        case MOOD_CALM:
            return (MoodProfile) {
                .backgroundColor = (Color){180, 220, 255, 255},
                .uiColor = (Color){150, 200, 255, 255},
                .brushColor = (Color){30, 100, 200, 255},
                .brushSize = 6,
                .brushOpacity = 0.6f
            };
        case MOOD_HAPPY:
            return (MoodProfile) {
                .backgroundColor = (Color){255, 255, 180, 255},
                .uiColor = (Color){255, 220, 50, 255},
                .brushColor = (Color){255, 140, 0, 255},
                .brushSize = 8,
                .brushOpacity = 0.9f
            };
        case MOOD_ANGRY:
            return (MoodProfile) {
                .backgroundColor = (Color){200, 30, 30, 255},
                .uiColor = (Color){150, 0, 0, 255},
                .brushColor = (Color){255, 255, 255, 255},
                .brushSize = 14,
                .brushOpacity = 1.0f
            };
        case MOOD_SAD:
            return (MoodProfile) {
                .backgroundColor = (Color){120, 140, 180, 255},
                .uiColor = (Color){90, 110, 150, 255},
                .brushColor = (Color){200, 200, 255, 255},
                .brushSize = 5,
                .brushOpacity = 0.5f
            };
        default:
            return (MoodProfile){0};
    }
}