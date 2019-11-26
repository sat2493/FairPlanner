#include <algorithm>
#include <iostream>
#include <vector>
#include "llrb_multimap.h"

int main() {
  LLRB_multimap<int, int> multimap;
  std::vector<std::vector<int>> keyVal{{2, 18}, {2, 17}, {2, 54}, {3, 93}};

  // Test with uninitialized tree
  std::cout << "Pre-insertion tests:" << std::endl;
  try {
    int key = 2;
    multimap.Get(key);
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
    multimap.Insert(key, value);
  }

  std::cout << "After insertions:" << std::endl;
  multimap.Print();

  // Test Get, Remove, and Insert functions
  std::cout << "Post-insertion tests:" << std::endl;
  std::cout << "Get(2) = " << multimap.Get(2) << "\n";
  std::cout << "Get(3) = " << multimap.Get(3) << "\n";
  try {
    int key = 100;
    multimap.Get(key);
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
    multimap.Remove(key, value);
  }
  std::cout << "After deletions:" << std::endl;
  multimap.Print();

  return 0;
}
