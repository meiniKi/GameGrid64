#include "MenuItem.h"

MenuItem::MenuItem(String title, uint16_t title_color, uint8_t nr_ways) : title_(title), title_color_(title_color),
    sel_(0), cnt_(0), capacity_(nr_ways)
{
    options_ = new option_t[nr_ways];
}

void MenuItem::registerOption(String name, uint32_t value, uint16_t color)
{
    if (cnt_ == capacity_)
        return;
    
    options_[cnt_].name_  = name;
    options_[cnt_].value_ = value;
    options_[cnt_].color_ = color;
    cnt_++;
}


void MenuItem::next()
{
    if (cnt_ <= 1)
        return;
    sel_ = (sel_ + 1) % cnt_;
}
