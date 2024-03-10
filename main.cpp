#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <cctype>
#include <utility>

// todo: design a proper structure..
// single variable function
class Function {
private:
  std::string function;

public:
  // no mechanism to confirm a single variable
  Function(std::string str) { function = str; }
  double Evaluate(int input) {
    int temp = 1;
    // assume multiplication by default.
    char current_operator = '*';
    double result = 1;
    for (char elt : function) {
      if (isspace(elt)) {
      } else if (isdigit(elt)) {
        result = perform_operation(int(elt) - 48, result, current_operator);
      } else if (elt == '+') {
        current_operator = '+';
      } else if (elt == '-') {
        current_operator = '-';
      } else if (elt == '/') {
        current_operator = '/';
      } else if (elt == '*') {
        current_operator = '*';
      } else if (isalpha(elt)) {
        result =
            perform_operation(perform_operation(temp, input, current_operator),
                              result, current_operator);
      }
    }
    return result;
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
  bool OnUserCreate() override { return true; }
  // this fn is called for every frame..
  bool OnUserUpdate(float fElpasedTime) override {
    Clear(olc::WHITE);
    DrawAxes();
    if (coordinates.size() == 0)
      SetPoints(Range(1, 390, 1), Function("2x + 30"));
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
