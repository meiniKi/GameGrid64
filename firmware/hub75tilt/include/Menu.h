#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>
#include "System.h"
#include "MenuItem.h"

class Menu {
private:
    uint8_t sel_;
    uint8_t done_;
    System* sys_;
    String  title_;
    uint16_t title_color_;
    
    MenuItem** items_;
    uint8_t cnt_;
    uint8_t capacity_;

public:
    Menu(System* sys, uint8_t nr_items, String title, uint16_t color);
    uint8_t handle();
    void registerOption(MenuItem* item);
    void render();
    uint8_t getNrItems() { return cnt_; };
    MenuItem* getItem(uint8_t i) { return items_[i]; };

};


#endif