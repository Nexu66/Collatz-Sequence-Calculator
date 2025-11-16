#pragma once
#include <QDebug>
#include <QList>
#include <QThread>
#include <Timer.hpp>
#include <atomic>
#include <iostream>
#include <limits>
#include <mutex>
#include <ranges>
#include <semaphore>
#include <thread>
#include <vector>

namespace Core {
namespace impl {
class CollatzProcessorImpl {
 public:
  static const qsizetype s_CoresCount;
  static const qsizetype s_MaxSize;
  static std::atomic<qsizetype> Elements;
  std::vector<std::pair<qsizetype, qsizetype>> ThreadResults;
  std::mutex ThreadResultsLock;
  static std::vector<std::jthread> s_ThreadPool;
  timer::Timer Timer;

  std::pair<qsizetype, qsizetype> StartProcessing(
      std::stop_token stop, const qsizetype CurrentThreadLimit,
      const qsizetype CurrentUpperLimit);
  std::pair<qsizetype, qsizetype> CalculateCollatz(qsizetype current_element);
  void SaveFinalThreadResult(
      std::pair<qsizetype, qsizetype> final_thread_result);
  std::pair<qsizetype, qsizetype> FindFinalResult();
  void Run(const qsizetype CurrentUpperLimit, std::stop_token stop);
};

}  // namespace impl
}  // namespace Core
