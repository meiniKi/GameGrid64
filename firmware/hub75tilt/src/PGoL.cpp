
#include "PGoL.h"

PGoL::PGoL(uint8_t density, uint32_t interval) :
    density_(density), t_(0), interval_(interval), color_((uint16_t)(-1))
{
    name = String("GoL");
}

void PGoL::init()
{
    gol_.randGrid(0, density_);
    t_ = millis();
}

void PGoL::game()
{
    if (sys_->getOkClicked())
        gol_.randGrid(millis(), density_);

    if (sys_->getSelClicked())
        color_ = random(0, 65535);


    if ((millis() - t_) > interval_)
    {
        gol_.next();
        t_ = millis();
    }
    gol_.render(sys_->getDmd(), color_);
}

void PGoL::deinit()
{

}

void PGoL::preview()
{
    sys_->getDmd()->drawString(20, 40, name.c_str(), name.length(), 0xFA1F, 0);
}
