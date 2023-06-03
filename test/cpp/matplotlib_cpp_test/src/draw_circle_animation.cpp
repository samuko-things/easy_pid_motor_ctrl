#define _USE_MATH_DEFINES
#include "matplotlibcpp.h"
#include <cmath>

#include <chrono>


namespace plt = matplotlibcpp;

int main() {
  // auto t_start = std::chrono::high_resolution_clock::now();
  // auto t_end = std::chrono::high_resolution_clock::now();
  auto prev_time = std::chrono::system_clock::now();
  std::chrono::duration<double> duration;

  int n = 1000;
  std::vector<double> x, y, z;

  for (int i = 0; i < n; i++) {
    prev_time = std::chrono::system_clock::now();

    x.push_back(i * i);
    y.push_back(sin(2 * M_PI * i / 360.0));
    z.push_back(log(i));

    // Clear previous plot
    plt::clf();
    // Plot line from given x and y data. Color is selected automatically.
    plt::plot(x, y);
    // Plot a line whose name will show up as "log(x)" in the legend.
    plt::plot(x, z, {{"label", "log(x)"}});

    // Set x-axis to interval [0,1000000]
    plt::xlim(0, n * n);

    // Add graph title
    plt::title("Sample figure");
    // Enable legend.
    plt::legend();
    // Display plot continuously
    plt::pause(0.001);

    duration = (std::chrono::system_clock::now() - prev_time);
    std::cout << "Finished in " << duration.count() << " seconds [Wall Clock]" << std::endl;
  }
}
