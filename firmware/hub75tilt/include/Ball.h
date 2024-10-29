#ifndef BALL_H_
#define BALL_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>


class Ball {
private:
    uint8_t radius_;
    float x_, y_;
    float theta_x_, theta_y_;
    float ax_, ay_;
    float vx_, vy_;
    float wx_, wy_;
    float gravity_;
    float phy_r_;
    float sensitivity_;
    float reflect_;
    float friction_;
    uint16_t color_;
    static constexpr float epsilon = 0.01f;

public:
    Ball(uint8_t r, float x, float y, float sensitivity, float friction, float gravity, float reflect, float phy_r);

    void setPosition(float x_pos, float y_pos);
    void resetMovement();
    void setX(float pos);
    void setY(float pos);
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    void update(float ax, float ay, float az, float dt);
    void bounceY(float y);
    void bounceX(float x);
    bool collidesX(float x, bool inc);
    bool collidesY(float y, bool inc);

    void getPosition(float &x_pos, float &y_pos) const {
        x_pos = x_;
        y_pos = y_;
    }

    uint8_t getRadius() const { return radius_; };

    void render(Adafruit_GFX *gfx, uint8_t offx, uint8_t offy);
};

#endif