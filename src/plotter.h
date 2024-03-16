#pragma once
#define OLC_PGE_APPLICATION
#include "../includes/olcPixelGameEngine.h"

#include "function.h"
#include "ranges.h"
// Plot.Plot(range(1,10,1), 2x + 3)
class Plot : public olc::PixelGameEngine {
private:
  std::vector<std::pair<double, double>> coordinates;
  Function fn;
  Range rg;
public:
  Plot() = default;
  Plot(Range r, Function f ) { sAppName = "Plot C++"; fn = f; rg = r;}
  // inititalization goes here
  bool OnUserCreate() override {
    SetPoints(Range(1, 390, 1), fn);
    return true;
  }

  // this fn is called for every frame..
  bool OnUserUpdate(float fElpasedTime) override {
    Clear(olc::WHITE);
    DrawAxes();
    PlotPoints();
    return true;
  }
 private:
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
 public:
  void plot(){
   if(this->Construct(400, 400, 4, 4)) this->Start();
  }
};

