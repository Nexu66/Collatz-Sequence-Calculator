#pragma once
#include <QDebug>
#include <QList>
#include <QThread>
#include <atomic>
#include <limits>
#include <ranges>
#include <thread>
#include <vector>

#include "Timer.hpp"

namespace Core {
namespace impl {
enum Signals { STOP = -1, VALUE_OVERFLOWED = -2 };
class CollatzProcessorImpl {
 public:
  CollatzProcessorImpl();
  ~CollatzProcessorImpl();
  bool is_Overflow = false;
  static const qsizetype cs_UpperLimitCap = 1000000000;
  static const qsizetype cs_CoresCount;
  static const qsizetype cs_MaxSizeBeforeOverflow =
      std::numeric_limits<qsizetype>::max() / 3 + 1;
  static std::vector<std::pair<qsizetype, qsizetype>> s_ThreadResults;
  static timer::Timer s_Timer;
  static std::atomic<qsizetype>* s_Cache;
  static std::vector<std::jthread> s_ThreadPool;

  void RequestStop();
  bool WillOverflow(qsizetype current_element);
  std::pair<qsizetype, qsizetype> StartProcessing(
      std::stop_token stop, const qsizetype CurrentThreadLimit,
      const qsizetype CurrentUpperLimit);
  void CalculateCollatz(qsizetype current_element, qsizetype& step_counter);
  std::pair<qsizetype, qsizetype> FindFinalResult();
  void Run(std::stop_token stop, const qsizetype IntervalBegin,
           const qsizetype IntervalEnd, const qsizetype IndexInResultsVector);
};

}  // namespace impl
}  // namespace Core
