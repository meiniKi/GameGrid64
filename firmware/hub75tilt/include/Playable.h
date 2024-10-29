#ifndef PLAYABLE_H_
#define PLAYABLE_H_

#include <Arduino.h>
#include "System.h"
#include "Menu.h"

class Playable {
protected:
    System* sys_;
    Menu* menu_;

    typedef enum {
        MENU,
        GAME_INIT,
        PLAY
    } play_state_t;

    play_state_t state_;

public:
    String name = String("None");
    virtual void setup(System* sys);
    virtual void loop();
    virtual void init() { };
    virtual void game_init() { };
    virtual void game() = 0;
    virtual void preview() = 0;
    virtual void deinit() { };
    virtual ~Playable() = default;
};

#endif

