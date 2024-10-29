
#include "AppManager.h"


AppManager::AppManager(System* sys) :
    sel_state_(State_t::SEL_STARTUP), pid_(0), pcnt_(0), sys_(sys)
{
    for (uint8_t i = 0; i < 30; i++)
    {
        welcome_pixels_[i].x_ = 4+i;
        welcome_pixels_[i].y_ = 3;
        welcome_pixels_[i].dir_ = 0;
    }

};

void AppManager::registerPlayable(Playable* p)
{
    if (p == nullptr)
        return;
    p->setup(sys_);
    playable_[pcnt_++] = p;
}

void AppManager::loop()
{
    switch(sel_state_)
    {
        case SEL_STARTUP:
            renderWelcomeAnimation();
            sys_->setFontMed();
            sys_->getDmd()->drawString(17, 10, "Menu", 4, 0xc638, 0);
            sys_->setFontSmall();
            sys_->getDmd()->drawString(32-21, 57, "+/-", 3, 0b11111100000, 0);
            sys_->getDmd()->drawString(32+10, 57, "x", 1, 0b11111100000, 0);
            if (playable_[pid_])
                playable_[pid_]->preview();

            if (sys_->getSelClicked())
            {
                Serial.print("Sel pressed ->");
                pid_ = (pcnt_ == 1) ? 0 : (pid_ + 1) % pcnt_;
                Serial.print(pid_);
                Serial.print("\n");
            }
            if (sys_->getOkClicked())
                sel_state_ = SEL_INIT;

            //pid_ = 1;
            //sel_state_ = SEL_INIT; 
            break;

        case SEL_INIT:
            if (playable_[pid_])
                playable_[pid_]->init();
            playable_[pid_]->deinit();
            sel_state_ = SEL_PLAYING;
            break;

        case SEL_PLAYING:
            if (sys_->getSelLong())
            {
                sel_state_ = SEL_STARTUP;
                break;
            }
            if (playable_[pid_])
                playable_[pid_]->loop();
            break;

        default:
            break;
    }

}

void AppManager::moveWelcomePx_(uint8_t steps)
{
    const uint8_t boarder = 3;
    while (steps--)
    {
        for (uint8_t i = 0; i < 30; i++)
        {
            if ((welcome_pixels_[i].y_ ==    boarder && welcome_pixels_[i].x_ == 64-boarder) ||
                (welcome_pixels_[i].y_ == 64-boarder && welcome_pixels_[i].x_ == 64-boarder) ||
                (welcome_pixels_[i].y_ == 64-boarder && welcome_pixels_[i].x_ ==    boarder) ||
                (welcome_pixels_[i].y_ ==    boarder && welcome_pixels_[i].x_ ==    boarder))
                welcome_pixels_[i].dir_ = (welcome_pixels_[i].dir_ + 1) % 4;

            if (welcome_pixels_[i].dir_ == 0)
                welcome_pixels_[i].x_ += 1;
            else if (welcome_pixels_[i].dir_ == 1)
                welcome_pixels_[i].y_ += 1;
            else if (welcome_pixels_[i].dir_ == 2)
                welcome_pixels_[i].x_ -= 1;
            else if (welcome_pixels_[i].dir_ == 3)
                welcome_pixels_[i].y_ -= 1;
        }
    }
}


void AppManager::renderWelcomeAnimation()
{
    for (uint8_t i = 0; i < 30; i++)
    {
        sys_->getDmd()->drawPixel(
            welcome_pixels_[i].x_,
            welcome_pixels_[i].y_,
            (uint16_t)(0xf800));
    }
    moveWelcomePx_(3);

}