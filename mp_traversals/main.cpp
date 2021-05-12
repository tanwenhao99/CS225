
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png; 
  png.readFromFile("among-us.png");

  FloodFilledImage image(png);
  BFS boundary(png, Point(0, 0), 0.05);
  BFS outside(png, Point(64, 64), 0.05);
  RainbowColorPicker rainbow(0.05);
  DFS body(png, Point(200, 350), 0.05);
  DFS bag(png, Point(350, 350), 0.05);
  DFS glasses(png, Point(180, 250), 0.05);
  HSLAPixel blue(270, 1, 0.5);
  HSLAPixel red(0, 1, 0.5);
  HSLAPixel white(180, 1, 0.5);
  GradientColorPicker gradient(white, blue, Point(64, 64), 500);
  SolidColorPicker Red(red);
  SolidColorPicker White(white);
  image.addFloodFill(boundary, rainbow);
  image.addFloodFill(body, Red);
  image.addFloodFill(bag, Red);
  image.addFloodFill(glasses, White);
  image.addFloodFill(outside, gradient);

  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
