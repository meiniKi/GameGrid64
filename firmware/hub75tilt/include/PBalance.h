#ifndef PBALANCE_H_
#define PBALANCE_H_

#include <Arduino.h>
#include "Ball.h"
#include "Playable.h"
#include "System.h"

class PBalance : public Playable {
private:
    Ball ball_;
    uint32_t t_;
    float ax_, ay_, az_;
    float px_, py_;
    float dt_;

    void renderBorder();

public:
    PBalance();
    virtual void init() override;
    virtual void game() override;
    virtual void deinit() override;
    virtual void preview() override;
};


#endif