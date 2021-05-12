#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

int main() {
  List<int> list1;
  List<int> list2;

  list1.insertBack(2);
  list1.insertBack(10);
  list1.insertBack(-3);
  list1.insertBack(4111);
  list1.sort();

  for (auto it = list1.begin(); it != list1.end(); it++) {
    cout << (*it) << endl;
  }
  return 0;
}
