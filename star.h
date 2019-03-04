#ifndef star_h
#define star_h

#define strip_lengh 301

#include <Arduino.h>
#include <NeoPixelBus.h>



class Star
{
  public:
    Star();
    void update();
    void init();
  private:
    int dot[40];
    int number;
    int value;
    bool up;
    int speed;
};
    
#endif
