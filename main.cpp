
#include <string>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <cctype>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
// todo: design a proper structure..
// single variable function

class Function {
private:
  std::function<double(int)> m_function;
  char m_variable;

  std::vector<std::string> m_params;

public:
  // no mechanism to confirm a single variable
  Function(char *str) { assign_lamdda(str); }

  void assign_lamdda(char *str) {
    char *current = str;
    char *next = str;

    while (*current != '\0') {
      if (isspace(*current)) {
        next++;
        current++;
      } else if (isdigit(*current)) {
        int num = int(*current) - 48;
        while (isdigit(*(++next))) {
          num = num * 10 + (*next - 48);
          current++;
        }
        current = next;
        m_params.emplace_back(std::to_string(num));
      } else if (isalpha(*current)) {
        // for future to check if its a single var or not
        m_variable = *current;
        // std::string temp(m_variable);
        m_params.emplace_back("x");
        current++;
        next++;
      } else if ((*current) == '+') {
        m_params.emplace_back("+");
        current++;
        next++;
      } else if ((*current) == '-') {
        m_params.emplace_back("-");
        current++;
        next++;
      } else if ((*current) == '*') {
        m_params.emplace_back("*");
        current++;
        next++;
      } else if ((*current) == '/') {
        m_params.emplace_back("/");
        current++;
        next++;
      }
    }
    m_function = [&](int x) -> double {
      double result = 0;
      char current_op = '*';
      bool no_op_read = true;
      for (const auto &elt : m_params) {
        if (isdigit(elt[0])) {
          if (no_op_read)
            result = std::stoi(elt);
          else {
            result = perform_operation(result, std::stoi(elt), current_op);
          }
        } else if (elt == "+") {
          current_op = '+';
          no_op_read = false;
        } else if (elt == "-") {
          no_op_read = false;
          current_op = '-';
        } else if (elt == "/") {
          no_op_read = false;
          current_op = '/';
        } else if (elt == "*") {
          no_op_read = false;
          current_op = '*';
        } else if (isalpha(elt[0])) {
          if (no_op_read)
            result = 1;
          result = perform_operation(result, x, current_op);
        }
      }
      return result;
    };
  }

  double Evaluate(int input) { return m_function(input); }

  void debug() {
    for (const auto &elt : m_params)
      std::cout << elt << '\n';
  }
  double perform_operation(const double &a, const double &b, const char op) {
    if (op == '+')
      return a + b;
    if (op == '-')
      return a - b;
    if (op == '*')
      return a * b;
    if (op == '/')
      return a / b;
  }
};

// can we just use C++20's range? - Yes, We'll
class Range {
private:
  std::vector<int> vals;

public:
  Range(int start, int end, int increment) {
    for (int i = start; i < end; i = i + increment) {
      vals.emplace_back(i);
    }
  }
  // kinda stupid..
  const std::vector<int> &getRangeVals() { return vals; }
};

// Plot.Plot(range(1,10,1), 2x + 3)
class Plot : public olc::PixelGameEngine {
private:
  std::vector<std::pair<double, double>> coordinates;

public:
  Plot() { sAppName = "Plot C++"; }
  // inititalization goes here
  bool OnUserCreate() override {
    SetPoints(Range(1, 390, 1), Function("5x"));
    return true;
  }

  // this fn is called for every frame..
  bool OnUserUpdate(float fElpasedTime) override {
    Clear(olc::WHITE);
    DrawAxes();
    PlotPoints();
    return true;
  }

  void DrawAxes() {
    // vertical axis (Y axis)
    DrawLine(0, 0, 0, 398, olc::BLUE);
    // horizontal axis (X axis)
    DrawLine(0, 398, 400, 398, olc::BLUE);
  }

  void SetPoints(Range r, Function f) {
    // kinda not what I like
    for (int elt : r.getRangeVals()) {
      coordinates.emplace_back(std::make_pair(elt, f.Evaluate(elt)));
    }
  }

  void PlotPoints() {
    for (auto points : coordinates) {
      Draw(points.first, 398 - points.second, olc::RED);
    }
  }
};
int main() {

  Plot myPlot;
  if (myPlot.Construct(400, 400, 4, 4)) {
    myPlot.Start();
  }
  return 0;
}
