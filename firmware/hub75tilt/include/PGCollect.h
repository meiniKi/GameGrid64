#ifndef PGCOLLECT_H_
#define PGCOLLECT_H_

#include <Arduino.h>
#include "Ball.h"
#include "Playable.h"
#include "Menu.h"

class PGCollect : public Playable {
private:
  Ball* ball_;
  uint32_t t_;
  float ax_, ay_, az_;
  float px_, py_;
  float dt_;

  uint8_t nr_obj_;
  uint32_t remaining_;
  uint32_t start_of_game_;
  uint32_t end_of_game_;
  uint8_t size_;

  typedef struct {
    int8_t x_;
    int8_t y_;
    uint8_t hit_;
  } object_t;

  object_t* objects_;

  // Ball type, seed, nr obj

  void handleObjects_();
  void renderObjects_();
  void renderBorder_();
  void renderStats_();

public:
  PGCollect();
  virtual void init() override;
  virtual void game() override;
  virtual void game_init() override;
  virtual void deinit() override;
  virtual void preview() override;
};


#endif