#include "../plotter.h"

int main() {
  Function f("5x");
  Range r(1,400,1);
  Plot myPlot(r,f);
  myPlot.plot();
  return 0;
}

