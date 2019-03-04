#include "star.h"

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;
uint8_t stars_numbers=5;
extern uint8_t color_instensity;
Star::Star()
{
  number=0;
  value=0;
  up=true;
  speed=0;
}
void Star::init()
{
  int i;
  number=random(stars_numbers, stars_numbers*2);
  for(i=0;i<number;i++)
  {
    dot[i]=random(0, strip_lengh);
  }
  value=0;
  up=true;
  speed=random(10, 20);
}
void Star::update()
{
  if(up)
  {
    if(value+speed<255)
      value+=speed;
    else
      value=255;
  }
  else
  {
    if(value-speed>0)
      value-=speed;
    else
      value=0;
  }
  if(value==0)
    init();
  if(value==255)
    up=false;

  int temp_val=value*color_instensity/50;
  if(temp_val>255)
    temp_val=255;
  if(temp_val<0)
    temp_val=0;

  RgbColor tempcolor(temp_val,temp_val,temp_val);
  for(int i=0;i<number;i++)
    strip.SetPixelColor(dot[i], tempcolor);
};
