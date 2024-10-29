#include "Menu.h"

Menu::Menu(System* sys, uint8_t nr_options, String title, uint16_t color) : 
    sel_(0), done_(0), sys_(sys), title_(title), title_color_(color),
    cnt_(0), capacity_(nr_options)
{
    items_ = new MenuItem*[nr_options];
} 

void Menu::registerOption(MenuItem* item)
{
    if (cnt_ == capacity_)
        return;
    items_[cnt_++] = item;

}

uint8_t Menu::handle()
{
    if (sys_->getSelClicked())
    {
        items_[sel_]->next();
    }
    if (sys_->getOkClicked())
    {
        if (sel_ < (cnt_-1))
            sel_++;
        else
            done_ = true;
    }
    return done_;
}

void Menu::render()
{
    sys_->setFontMed();
    sys_->getDmd()->drawString(15, 3, title_.c_str(), title_.length(), title_color_, 0);
    sys_->setFontSmall();
    for (uint8_t i=0; i<cnt_; i++)
    {
        String* s;

        if (i == sel_)
            sys_->getDmd()->drawString(2, 18+10*i, ">", 1, 2016, 0);
        
        s = items_[i]->getTitle();
        sys_->getDmd()->drawString(15, 18+10*i, s->c_str(), s->length(), items_[i]->getTitleColor(), 0);
        //uint8_t offset = s->length() * 6 + 2;
        s = items_[i]->getSelectedName();
        sys_->getDmd()->drawString(48, 18+10*i, s->c_str(), s->length(), items_[i]->getSelectedColor(), 0);
    }
    // Button labels
    sys_->getDmd()->drawString(32-21, 57, "+/-", 3, 0b11111100000, 0);
    sys_->getDmd()->drawString(32+10, 57, "x", 1, 0b11111100000, 0);
}
