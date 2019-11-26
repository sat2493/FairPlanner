#include <algorithm>
#include <iostream>
#include <vector>
#include "llrb_map.h"

int main() {
  LLRB_map<int, int> map;
  std::vector<std::vector<int>> keyVal{{2, 18}, {42, 43}, {51, 54}, {74, 93}};

  // Test with uninitialized tree
  std::cout << "Pre-insertion tests:" << std::endl;
  try {
    int key = 2;
    map.Get(key);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  // Insert a bunch of keys
  for (std::vector<std::vector<int>>::iterator it1 = keyVal.begin();
       it1 != keyVal.end();
       it1++) {
    int key, value;
    for (std::vector<int>::iterator it2 = it1->begin();
         it2 != it1->end();
         it2++) {
      if (it2 == it1->begin()) key = *it2;
      else  value = *it2;
    }
    map.Insert(key, value);
  }

  std::cout << "After insertions:" << std::endl;
  map.Print();

  // Test Get, Remove, and Insert functions
  std::cout << "Post-insertion tests:" << std::endl;
  std::cout << "Get(2) = " << map.Get(2) << "\n";
  std::cout << "Get(42) = " << map.Get(42) << "\n";
  try {
    int key = 100;
    map.Get(key);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }
  try {
    int key = 200;
    int value = 300;
    map.Remove(key, value);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }
  try {
    int key = 2;
    int value = 18;
    map.Insert(key, value);
  } catch (std::exception &e) {
    std::cout << "Expected exception: " << e.what() << std::endl;
  }

  // Delete all the keys in another order
  std::random_shuffle(keyVal.begin(), keyVal.end());
  for (std::vector<std::vector<int>>::iterator it1 = keyVal.begin();
       it1 != keyVal.end();
       it1++) {
    int key, value;
    for (std::vector<int>::iterator it2 = it1->begin();
         it2 != it1->end();
         it2++) {
      if (it2 == it1->begin()) key = *it2;
      else  value = *it2;
    }
    map.Remove(key, value);
  }
  std::cout << "After deletions:" << std::endl;
  map.Print();

  return 0;
}
