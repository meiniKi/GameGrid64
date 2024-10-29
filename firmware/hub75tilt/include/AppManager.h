#ifndef APPMANAGER_H_
#define APPMANAGER_H_

#include <Arduino.h>
#include "System.h"
#include "Playable.h"

class AppManager {
private:
    typedef enum {
        SEL_STARTUP,
        SEL_INIT,
        SEL_PLAYING
    } State_t;

    typedef struct 
    {
        uint8_t x_;
        uint8_t y_;
        uint8_t dir_;
    } Point_t;

    State_t sel_state_;
    uint8_t pid_;
    uint8_t pcnt_;
    Playable* playable_[10];

    System* sys_;

    Point_t welcome_pixels_[30];

    void moveWelcomePx_(uint8_t steps);
    void clicked_(void* oneButton) { Serial.println("OK from Appm\n"); };

public:
    AppManager(System* sys);
    void registerPlayable(Playable* p);
    void loop();
    void renderWelcomeAnimation();
};

#endif