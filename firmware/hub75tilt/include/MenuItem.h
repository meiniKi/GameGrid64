#ifndef MENUITEM_H_
#define MENUITEM_H_

#include <Arduino.h>
#include "System.h"


class MenuItem {
private:
    String title_;
    uint16_t title_color_;

    typedef struct {
        String name_;
        uint32_t value_;
        uint16_t color_;
    } option_t;

    option_t* options_;
    uint8_t sel_;
    uint8_t cnt_;
    uint8_t capacity_;

public:
    MenuItem(String title, uint16_t title_color, uint8_t nr_ways);
    void registerOption(String name, uint32_t value, uint16_t color);
    void next();
    uint32_t getSelectedValue() { return options_[sel_].value_; };
    String* getSelectedName()   { return &options_[sel_].name_; };
    uint16_t getSelectedColor() { return options_[sel_].color_; };
    String* getTitle()          { return &title_; };
    uint16_t getTitleColor()    { return title_color_; };
};


#endif