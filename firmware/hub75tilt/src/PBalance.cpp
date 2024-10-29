
#include "PBalance.h"

PBalance::PBalance() :
    ball_(Ball(2, 0.0f, 0.0f, 15.0f, 0.1f, 9.81f, 0.5f, 0.005f)),
    ax_(0.0f), ay_(0.0f), az_(0.0f), px_(0.0f), py_(0.0f), dt_(0.0f)
{
    name = String("Balance");
}

void PBalance::init()
{
    t_ = millis();
    ball_.setColor(255, 20, 20);
}

void PBalance::renderBorder()
{
    sys_->getDmd()->drawRect(0, 0, 64, 64, 0xc638);
}

void PBalance::game()
{
    if (sys_->getOkClicked())
        ball_.setPosition(0.0f, 0.0f);

    dt_ = (millis() - t_) / 1000.0f;
    t_  = millis();

    sys_->getLis()->read();
    ax_ = sys_->getLis()->y_g; // left (-), right (+)
    ay_ = -sys_->getLis()->x_g; // to body (+), away (-)
    az_ = -sys_->getLis()->z_g;

    ball_.update(ax_, ay_, az_, dt_);
    ball_.getPosition(px_, py_);

    if (ball_.collidesX(31.0f, true))
        ball_.bounceX(31.0f);
    if (ball_.collidesX(-30.0f, false))
        ball_.bounceX(-30.0f);

    if (ball_.collidesY(31.0f, true))
        ball_.bounceY(31.0f);
    if (ball_.collidesY(-30.0f, false))
        ball_.bounceY(-30.0f);

    ball_.render(sys_->getDmd(), 31, 31);
    renderBorder();

}

void PBalance::deinit()
{

}

void PBalance::preview()
{
    sys_->getDmd()->drawString(11, 40, name.c_str(), name.length(), 0xFA1F, 0);
}
