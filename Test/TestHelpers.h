#ifndef TESTHELPERS_H_INCLUDED
#define TESTHELPERS_H_INCLUDED

#include <algorithm>
#include <vector>

// Helper functions.

// Checks whether a vector contains an element.
template <typename T>
bool contains(const std::vector<T>& vec, const T& elem) {
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}

// Checks if two vectors contain the same elements.
template <typename T>
bool same_elements(const std::vector<T>& vec1, const std::vector<T>& vec2) {
  if (vec1.size() != vec2.size()) {return false;}
  for (const T& elem : vec1) {
    if (!contains(vec2, elem)) {return false;}
  }
  return true;
}

#endif // TESTHELPERS_H_INCLUDED
