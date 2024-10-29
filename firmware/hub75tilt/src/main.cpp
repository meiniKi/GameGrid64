#include <Arduino.h>
#include "System.h"
#include "AppManager.h"
#include "PGoL.h"
#include "PBalance.h"
#include "PGCollect.h"


System sys = System();

AppManager appm = AppManager(&sys);
//
PGoL pgol       = PGoL(50, 100);
PBalance pbal   = PBalance();
PGCollect pgcol = PGCollect();


void setup(void)
{
  Serial.begin(9600);

  sys.init();

  appm.registerPlayable(&pgol);
  appm.registerPlayable(&pbal);
  appm.registerPlayable(&pgcol);
}

void loop(void)
{
  uint32_t interval = 20;  
  uint32_t prev_step = 0;
  uint32_t printed = 0;

  while(1)
  {
    /*
    if (printed != prev_step)
    {
      printed = prev_step;
      Serial.println(millis()-prev_step);
    }
    */

    if ((millis() - prev_step) > interval)
    {
      prev_step = millis();
      sys.loopBegin();
      appm.loop();
      sys.loopEnd();
    }
  }

}
