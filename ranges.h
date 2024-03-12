#pragma once
#include <vector>
// represents a range of a number
// I am absolutely aware of c++ 20 Ranges..
class Range {
private:
  std::vector<int> vals;

public:
  Range() = default;
  Range(int start, int end, int increment) {
    for (int i = start; i < end; i = i + increment) {
      vals.emplace_back(i);
    }
  }
  // kinda stupid..
  const std::vector<int> &getRangeVals() { return vals; }
};

