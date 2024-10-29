#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "DMD_RGB.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3DH.h>

#include "st_fonts/UkrRusArial14.h"
#include "st_fonts/SystemFont5x7.h"

class System {

    //Number of panels in x and y axis
    #define DISPLAYS_ACROSS 1
    #define DISPLAYS_DOWN   1

    #define BTN0            22
    #define BTN1            21

    #define LIS3DH_CIPO     16
    #define LIS3DH_CS       17
    #define LIS3DH_CLK      18
    #define LIS3DH_COPI     19
    #define LIS3DH_INT1     20

    #define DMD_PIN_nOE   15
    #define DMD_PIN_SCLK  12

    #define ENABLE_DUAL_BUFFER true

private:
    // mux pins - A, B, C... mux pins must be consecutive in ascending order
    static constexpr uint8_t mux_list_[] = {6, 7, 8, 9, 10}; // PIN_A ... PIN_E

    // All this pins also must be consecutive in ascending order
    static constexpr uint8_t custom_rgbpins_[] = {11, 0, 1, 2, 3, 4, 5}; // CLK, R0, G0, B0, R1, G1, B1

    DMD_RGB <RGB64x64plainS32, COLOR_4BITS> dmd_;
    DMD_Standard_Font font_arial_14_;
    DMD_Standard_Font font_5x7_;

    // Gyro
    Adafruit_LIS3DH lis_;

    typedef struct {
        uint8_t  state_prev_;
        uint8_t  state_;
        uint32_t changed_;
    } btn_t;

    btn_t btn_ok_;
    btn_t btn_sel_;

    void eval_buttons_();
public:
    System();
    void init();
    
    inline DMD_RGB <RGB64x64plainS32, COLOR_4BITS>* getDmd() { return &dmd_; };
    inline Adafruit_LIS3DH* getLis() { return &lis_; };
    
    inline uint8_t getOkClicked()   { return !btn_ok_.state_ && btn_ok_.state_prev_; };
    inline uint8_t getSelClicked()  { return !btn_sel_.state_ && btn_sel_.state_prev_; };
    inline uint8_t getOkLong()      { return btn_ok_.state_ && ((millis() - btn_ok_.changed_) > 1000); };
    inline uint8_t getSelLong()     { return btn_sel_.state_ && ((millis() - btn_sel_.changed_) > 1000); };
    inline uint8_t getOkPress()     { return btn_ok_.state_; };
    inline uint8_t getSelPress()    { return btn_sel_.state_; };

    void setFontMed();
    void setFontSmall();


    void loopBegin();
    void loopEnd();
};


#endif