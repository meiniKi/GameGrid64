#ifndef PGOL_H_
#define PGOL_H_

#include <Arduino.h>
#include "Playable.h"
#include "GoL.h"

class PGoL : public Playable {
private:
    GoL<64,64> gol_;
    uint8_t density_;
    uint32_t t_;
    uint32_t interval_;
    uint16_t color_;

public:
    PGoL(uint8_t density, uint32_t interval);
    virtual void init() override;
    virtual void game() override;
    virtual void deinit() override;
    virtual void preview() override;
};


#endif