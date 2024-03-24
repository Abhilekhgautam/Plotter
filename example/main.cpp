#include "../src/plotter.h"

int main() {
  // define a new function.
  Function f("5x");
  // define the range
  Range r(1,400,1);
  // create a plot object with range and the function
  Plot myPlot(r,f);
  // call the plot function to plot
   myPlot.plot();
  return 0;
}

