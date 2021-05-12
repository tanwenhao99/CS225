#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "intro.h"

#include <stdlib.h>
#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;
  image.readFromFile(inputFile);
  for (unsigned x = 0; x < image.width() / 2; x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel1 = image.getPixel(x, y);
      HSLAPixel & pixel2 = image.getPixel(image.width() - x - 1, image.height() - y - 1);
      HSLAPixel temp = pixel1;
      pixel1 = pixel2;
      pixel2 = temp;
    }
  }
  if (image.width() % 2 == 1) {
    for (unsigned y = 0; y < image.height() / 2; y++) {
      HSLAPixel & pixel1 = image.getPixel(image.width() / 2, y);
      HSLAPixel & pixel2 = image.getPixel(image.width() / 2, image.height() - y - 1);
      HSLAPixel temp = pixel1;
      pixel1 = pixel2;
      pixel2 = temp;
    }
  }
  image.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG image(width, height);
  // TODO: Part 3 (Germany Flag)
  srand (time(NULL));
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height / 3; y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.h = 0;
      pixel.s = 0;
      pixel.l = (double)(rand() % 31) / 100;
      pixel.a = (double)(rand() % 81 + 20) / 100;
    }
    for (unsigned y = height / 3; y < 2 * height / 3; y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = (double)(rand() % 51 + 25) / 100;
      pixel.a = 1;
    }
    for (unsigned y = 2 * height / 3; y < height; y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.h = 55;
      pixel.s = 1;
      pixel.l = 0.5;
      pixel.a = 1;
    }
  }
  return image;
}
