#pragma once
#include <vector>
// represents a range of a number
// I am absolutely aware of c++ 20 Ranges..
class Range {
private:
  int m_start;
  int m_end;
  int m_increment;
public:
  Range() = default;
  Range(int start, int end, int increment) {
    m_start = start;
    m_end = end;
    m_increment = increment;
  }

  std::vector<int> GetValues(){
    std::vector<int> temps;
    for(int i = m_start; i < m_end ; i = i + m_increment){
	temps.emplace_back(i);    
    }
    return temps;
  }
};

