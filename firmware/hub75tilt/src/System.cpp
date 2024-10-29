
#include "System.h"

System::System() : dmd_((uint8_t*)(System::mux_list_), DMD_PIN_nOE, DMD_PIN_SCLK, (uint8_t*)(System::custom_rgbpins_), DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER),
  lis_(LIS3DH_CS, LIS3DH_COPI, LIS3DH_CIPO, LIS3DH_CLK), btn_ok_(), btn_sel_(), font_arial_14_(Arial_14), font_5x7_(SystemFont5x7)
{
 
}

void System::init()
{
  dmd_.init();
  dmd_.disableFastTextShift(true);
  dmd_.setRotation(1);
  dmd_.selectFont(&font_arial_14_);
  dmd_.setBrightness(50);

  pinMode(BTN0, INPUT_PULLUP);
  pinMode(BTN1, INPUT_PULLUP);

  lis_.begin();
  lis_.setRange(LIS3DH_RANGE_2_G);
  lis_.setDataRate(LIS3DH_DATARATE_400_HZ);
}

void System::eval_buttons_()
{
  btn_sel_.state_prev_ = btn_sel_.state_;
  if (millis() - btn_sel_.changed_ > 10)
  {
    btn_sel_.state_ = !digitalRead(BTN1);
    if (btn_sel_.state_ != btn_sel_.state_prev_)
      btn_sel_.changed_ = millis();
  }

  btn_ok_.state_prev_ = btn_ok_.state_;
  if (millis() - btn_ok_.changed_ > 10)
  {
    btn_ok_.state_ = !digitalRead(BTN0);
    if (btn_ok_.state_ != btn_ok_.state_prev_)
      btn_ok_.changed_ = millis();
  }
}


void System::loopBegin()
{
  eval_buttons_();
  dmd_.clearScreen(true);
}

void System::loopEnd()
{
  dmd_.swapBuffers(true);
}

void System::setFontMed()
{
  dmd_.selectFont(&font_arial_14_);
}

void System::setFontSmall()
{
  dmd_.selectFont(&font_5x7_);
}
