
#include "Ball.h"

Ball::Ball(uint8_t r, float x, float y, float sensitivity, float friction, float gravity, float reflect, float phy_r) :
    radius_(r), color_((uint16_t)(-1)), x_(x),  y_(y), theta_x_(0.0f), theta_y_(0.0f),
    ax_(0.0f), ay_(0.0f), vx_(0.0f), vy_(0.0f), gravity_(gravity), phy_r_(phy_r), wx_(0.0f), wy_(0.0f),
    sensitivity_(sensitivity), friction_(friction), reflect_(reflect)
{

}

void Ball::resetMovement()
{
  ax_ = 0.0f;
  ay_ = 0.0f;
  vx_ = 0.0f;
  vy_ = 0.0f;
  vx_ = 0.0f;
  vy_ = 0.0f;
  wy_ = 0.0f;
  wx_ = 0.0f;
}

void Ball::setPosition(float x_pos, float y_pos)
{
  x_ = x_pos;
  y_ = y_pos;
}

void Ball::setX(float pos)
{
  x_ = pos;
}

void Ball::setY(float pos)
{
  y_ = pos;
}

void Ball::bounceX(float x)
{
  if (vx_ == 0)
    return;
  x_ = (vx_ > 0.0f) ? (x - radius_ - 0.01f) : (x_ + radius_ + 0.01f);
  vx_ = -vx_ * reflect_;
  wx_ = -wx_ * reflect_;
}

void Ball::bounceY(float y)
{
  if (vy_ == 0)
    return;
  y_ = (vy_ > 0.0f) ? (y - radius_ - 0.01f) : (y_ + radius_ + 0.01f);
  vy_ = -vy_ * reflect_;
  wy_ = -wy_ * reflect_;
}

void Ball::setColor(uint8_t r, uint8_t g, uint8_t b)
{
  color_ = ((r&0xF8) << 8) | ((g&0xFC) << 3) | (b >> 3);
}

void Ball::update(float ax, float ay, float az, float dt)
{
  theta_x_ = atan(ax / sqrt(ay*ay + az*az)); // right (+)
  theta_y_ = atan(ay / sqrt(ax*ax + az*az)); // away (+)

  ax_ = sensitivity_ * gravity_ * sin(theta_x_);
  ay_ = sensitivity_ * gravity_ * sin(theta_y_);

  float alpha_x = (5.0 * sensitivity_ * gravity_ * sin(theta_x_)) / (2.0 * phy_r_);
  float alpha_y = (5.0 * sensitivity_ * gravity_ * sin(theta_y_)) / (2.0 * phy_r_);

  vx_ += ax_ * dt;
  vy_ += ay_ * dt;
    
  x_ += vx_ * dt;
  y_ += vy_ * dt;
  
  wx_ += alpha_x * dt;
  wy_ += alpha_y * dt;
    
  vx_ = wx_ * phy_r_ * (1.0f - friction_);
  vy_ = wy_ * phy_r_ * (1.0f - friction_);

  //if (vx_ < 0.00001f) vx_ = 0.0f;
  //if (vy_ < 0.00001f) vy_ = 0.0f;

 /*
  ax_ = (sensitivity_ * theta_y_ * gravity_) / mass_;
  ay_ = (sensitivity_ * theta_x_ * gravity_) / mass_;

  vx_ = vx_ + ax_ * dt;
  vy_ = vy_ + ay_ * dt;

  x_ = x_ + vx_ * dt;
  y_ = y_ + vy_ * dt;

  vx_ = (1.0f - friction_) * (mass_ * vx_ * dt);
  vy_ = (1.0f - friction_) * (mass_ * vy_ * dt);
  */
}

bool Ball::collidesX(float x, bool inc)
{
  if ( inc && (x_ + (float)(radius_) > x + Ball::epsilon) )
    return true;

  if ( !inc && (x_ - (float)(radius_) < x - Ball::epsilon) )
    return true;

  return false;
}

bool Ball::collidesY(float y, bool inc)
{
  if ( inc && (y_ + (float)(radius_) > (y + Ball::epsilon)) )
  {
    return true;
  }

  if ( !inc && ((y_ - (float)(radius_)) < (y - Ball::epsilon)) )
  {
    return true;
  }

  return false;
}


void Ball::render(Adafruit_GFX *gfx, uint8_t offx, uint8_t offy)
{
  if (gfx == nullptr)
    return;
  gfx->fillCircle(offx+x_, offy+y_, radius_, color_);
}