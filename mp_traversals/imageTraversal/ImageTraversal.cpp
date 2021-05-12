#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, const PNG & png, const Point & start, double tolerance) 
    : traversal(traversal), png_(png), start_(start), tol(tolerance) {
  pixel = png_.getPixel(start.x, start.y);
  visited = std::vector< std::vector<bool> >(png.width(), std::vector<bool>(png.height(), false));
}

/**
 * Iterator increment operator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point pt = traversal->pop();
  visited[pt.x][pt.y] = true;
  if (pt.x+1 < png_.width() && calculateDelta(pixel, png_.getPixel(pt.x+1, pt.y)) <= tol) {
    if (!visited[pt.x+1][pt.y]) 
      traversal->add(Point(pt.x+1, pt.y));
  }
  if (pt.y+1 < png_.height() && calculateDelta(pixel, png_.getPixel(pt.x, pt.y+1)) <= tol) {
    if (!visited[pt.x][pt.y+1]) 
      traversal->add(Point(pt.x, pt.y+1));
  }
  if (pt.x-1 < png_.width() && calculateDelta(pixel, png_.getPixel(pt.x-1, pt.y)) <= tol) {
    if (!visited[pt.x-1][pt.y]) 
      traversal->add(Point(pt.x-1, pt.y));
  }
  if (pt.y-1 < png_.height() && calculateDelta(pixel, png_.getPixel(pt.x, pt.y-1)) <= tol) {
    if (!visited[pt.x][pt.y-1]) 
      traversal->add(Point(pt.x, pt.y-1));
  }
  while (!traversal->empty() && visited[traversal->peek().x][traversal->peek().y]) 
    traversal->pop();
  if (traversal->empty())
    traversal = NULL;
  return *this;
}

/**
 * Iterator accessor operator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return traversal->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return traversal != other.traversal;
}

