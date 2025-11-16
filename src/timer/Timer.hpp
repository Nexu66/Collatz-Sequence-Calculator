#pragma once
#include <chrono>
#include <string>
namespace timer {
using namespace std::chrono;
class Timer {
 public:
  double time;
  time_point<steady_clock> start;
  void StartTimer() { this->start = steady_clock::now(); }
  double StopTimer() {
    auto stop = steady_clock::now();
    auto result_time =
        duration_cast<duration<double, std::milli>>(stop - start);
    this->time = result_time.count();
    return this->time;
  }
};
}  // namespace timer
