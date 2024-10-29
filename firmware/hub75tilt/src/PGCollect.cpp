
#include "PGCollect.h"
//#include <math.h>

PGCollect::PGCollect() :
  ball_(nullptr),
  ax_(0.0f), ay_(0.0f), az_(0.0f), px_(0.0f), py_(0.0f), dt_(0.0f),
  start_of_game_(0), nr_obj_(4), remaining_(4), size_(2), end_of_game_(0)
{
  name = String("Collect");
}

void PGCollect::handleObjects_()
{
  float bx, by;
  float br;
  float clx, cly;
  float dx, dy;
  float d2;
  
  ball_->getPosition(bx, by);
  br = ball_->getRadius();

  bool all_hit = true;

  for (uint8_t i = 0; i < nr_obj_; ++i)
  {
    if (objects_[i].hit_ == false)
    {
      clx = max((float)(objects_[i].x_), min(bx, (float)(objects_[i].x_) + (float)(size_)));
      cly = max((float)(objects_[i].y_), min(by, (float)(objects_[i].y_) + (float)(size_)));

      dx = bx - clx;
      dy = by - cly;

      d2 = (dx*dx) + (dy*dy);

      if (d2 <= (br*br))
      {
        objects_[i].hit_ = true;
        if (remaining_ > 0)
          remaining_ -= 1;
        if (remaining_ == 0)
          end_of_game_ = millis();
      }
    }

    if (objects_[i].hit_ == false)
      all_hit = false;
  }

  if (all_hit == true)
  {
    Serial.println("Creating objects...\n");
    for (uint8_t i = 0; i < random(1, nr_obj_); i++)
    {
      bool overlap;
      do
      {
        overlap = false;
        objects_[i].x_ = (int8_t)(random(-30, 31 - size_));
        objects_[i].y_ = (int8_t)(random(-30, 31 - size_));

        for (uint8_t j = 0; j < i; j++)
        {
          if ((abs(objects_[i].x_ - objects_[j].x_) <= size_) && (abs(objects_[i].y_ - objects_[j].y_) <= size_))
          {
            overlap = true;
            break;
          }
        }
      } while (overlap);

      objects_[i].hit_ = false;
    }
  }
}

void PGCollect::renderObjects_()
{
  for (uint8_t i = 0; i < nr_obj_; ++i)
  {
    if (objects_[i].hit_ == false)
    {
      sys_->getDmd()->fillRect(objects_[i].x_ + 31, objects_[i].y_ + 31, size_, size_, (uint16_t)(0xc638));
    }
  }
}

void PGCollect::renderStats_()
{
  String s;
  sys_->setFontSmall();

  s = String((millis()-start_of_game_)/100.0);
  sys_->getDmd()->drawString(60-6*s.length(), 2, s.c_str(), s.length(), (uint16_t)(0x07e0), 0);

  s = String(remaining_);
  sys_->getDmd()->drawString(2, 2, s.c_str(), s.length(), (uint16_t)(0xf800), 0);
}


void PGCollect::init()
{
  t_ = millis();

  menu_ = new Menu(sys_, 4, String("Collect"), (uint16_t)(0xc638));

  uint16_t title_color = (uint16_t)(0xc638);
  uint16_t value_color = (uint16_t)(0xc4de);

  MenuItem* mball = new MenuItem(String("Ball"), title_color, 3);
  mball->registerOption(String("B1"), 15, value_color);
  mball->registerOption(String("B2"), 30, value_color);
  mball->registerOption(String("B3"), 80, value_color);

  MenuItem* mseed = new MenuItem(String("Seed"), title_color, 3);
  mseed->registerOption(String("S1"), 1, value_color);
  mseed->registerOption(String("S2"), 2, value_color);
  mseed->registerOption(String("S3"), 3, value_color);

  MenuItem* mlength = new MenuItem(String("Length"), title_color, 5);
  mlength->registerOption(String("50"), 50, value_color);
  mlength->registerOption(String("100"), 100, value_color);
  mlength->registerOption(String("150"), 150, value_color);
  mlength->registerOption(String("200"), 200, value_color);
  mlength->registerOption(String("1000"), 1000, value_color);

  MenuItem* msize = new MenuItem(String("Size"), title_color, 3);
  msize->registerOption(String("5"), 5, value_color);
  msize->registerOption(String("2"), 2, value_color);
  msize->registerOption(String("1"), 1, value_color);

  menu_->registerOption(mball);
  menu_->registerOption(mseed);
  menu_->registerOption(mlength);
  menu_->registerOption(msize);
}

void PGCollect::renderBorder_()
{
  sys_->getDmd()->drawRect(0, 0, 64, 64, (uint16_t)(0xc638));
}

void PGCollect::game_init()
{
  if (objects_ != nullptr)
    delete objects_;

  objects_ = new object_t[nr_obj_];
  for (uint8_t i = 0; i < nr_obj_; i++)
    objects_[i].hit_ = true;

  float gravity = (float)(menu_->getItem(0)->getSelectedValue());
  uint32_t seed = menu_->getItem(1)->getSelectedValue();
  remaining_ = (uint32_t)(menu_->getItem(2)->getSelectedValue());
  size_ = (uint8_t)(menu_->getItem(3)->getSelectedValue());

  srand(seed);
  if (ball_ != nullptr)
      delete ball_;
  ball_ = new Ball(2, 0.0f, 0.0f, gravity, 0.1f, 9.81f, 0.25f, 0.005f);
  ball_->setColor(255, 20, 20);
}

void PGCollect::game()
{
  if (end_of_game_)
  {
    String s;
    sys_->setFontMed();
    s = String((end_of_game_-start_of_game_)/100.0);
    sys_->getDmd()->drawString(26, 20, s.c_str(), s.length(), (uint16_t)(0xf800), 0);
    return;
  }

  if (sys_->getOkClicked())
    ball_->setPosition(0.0f, 0.0f);

  dt_ = (millis() - t_) / 1000.0f;
  t_  = millis();

  sys_->getLis()->read();
  ax_ = sys_->getLis()->y_g; // left (-), right (+)
  ay_ = -sys_->getLis()->x_g; // to body (+), away (-)
  az_ = -sys_->getLis()->z_g;

  ball_->update(ax_, ay_, az_, dt_);
  ball_->getPosition(px_, py_);

  if (ball_->collidesX(31.0f, true))
    ball_->bounceX(31.0f);
  if (ball_->collidesX(-30.0f, false))
    ball_->bounceX(-30.0f);

  if (ball_->collidesY(31.0f, true))
    ball_->bounceY(31.0f);
  if (ball_->collidesY(-30.0f, false))
    ball_->bounceY(-30.0f);

  renderBorder_();
  renderStats_();
  handleObjects_();
  renderObjects_();
  ball_->render(sys_->getDmd(), 31, 31);
}

void PGCollect::deinit()
{

}

void PGCollect::preview()
{
  sys_->getDmd()->drawString(13, 40, name.c_str(), name.length(), 0xFA1F, 0);
}
