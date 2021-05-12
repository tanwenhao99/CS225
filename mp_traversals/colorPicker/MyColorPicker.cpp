#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel color1, HSLAPixel color2, HSLAPixel color3, Point center)
  : color1(color1), color2(color2), color3(color3), center(center) { }

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned sum = 0;
  if (x > center.x)
    sum += x - center.x;
  else
    sum += center.x - x;
  if (y > center.y)
    sum += y - center.y;
  else
    sum += center.y - y;
  if (sum % 3 == 0)
    return color1;
  else if (sum % 3 == 1)
    return color2;
  else
    return color3;
}
