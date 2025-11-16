#include "coreImpl.hpp"

namespace Core {
namespace impl {

const qsizetype CollatzProcessorImpl::s_CoresCount =
    QThread::idealThreadCount();
std::vector<std::jthread> CollatzProcessorImpl::s_ThreadPool{
    static_cast<size_t>(CollatzProcessorImpl::s_CoresCount)};
const qsizetype s_MaxSize = std::numeric_limits<qsizetype>::max();
std::atomic<qsizetype> CollatzProcessorImpl::Elements = 2;

std::pair<qsizetype, qsizetype> CollatzProcessorImpl::StartProcessing(
    std::stop_token stop, const qsizetype CurrentThreadLimit,
    const qsizetype CurrentUpperLimit) {
  Timer.StartTimer();
  for (int i = 0; i < CurrentThreadLimit; ++i) {
    s_ThreadPool[i] = std::jthread{
        std::bind_front(&CollatzProcessorImpl::Run, this, CurrentUpperLimit)};
  }

  for (int i = 0; i < CurrentThreadLimit; ++i) {
    s_ThreadPool[i].join();
  }
  Elements = 2;

  std::pair<qsizetype, qsizetype> res = FindFinalResult();
  std::cout << "Out time is: " << Timer.StopTimer() << "ms\n";
  std::cout << "Num: " << res.first << " Count: " << res.second << "\n";

  // CHECK FOR STOP SIGNAL

  return res;
}

std::pair<qsizetype, qsizetype> CollatzProcessorImpl::CalculateCollatz(
    qsizetype current_element) {
  qsizetype step_counter = 0;
  std::pair<qsizetype, qsizetype> local_result{current_element, step_counter};
  while (current_element != 1) {
    if (current_element % 2) {
      current_element = current_element * 3 + 1;
      // CHECK IF WE HAVE OVERFLOW
    } else {
      current_element /= 2;
    }
    ++step_counter;
  }
  local_result.second = step_counter;
  return local_result;
}

void CollatzProcessorImpl::SaveFinalThreadResult(
    std::pair<qsizetype, qsizetype> final_thread_result) {
  std::lock_guard<std::mutex> write_access_lock{ThreadResultsLock};
  ThreadResults.push_back(final_thread_result);
  // std::cout << std::this_thread::get_id() << " Vector:\n";
  // foreach (auto p, ThreadResults) {
  //   std::cout << "first: " << p.first << " second: " << p.second << "\n";
  // }
}

std::pair<qsizetype, qsizetype> CollatzProcessorImpl::FindFinalResult() {
  auto result = *std::ranges::max_element(
      ThreadResults, [](const std::pair<qsizetype, qsizetype> first_el,
                        const std::pair<qsizetype, qsizetype> second_el) {
        return first_el.second < second_el.second;
      });
  ThreadResults.clear();
  return result;
}

void CollatzProcessorImpl::Run(const qsizetype CurrentUpperLimit,
                               std::stop_token stop) {
  qsizetype current_element = Elements++;
  std::pair<qsizetype, qsizetype> local_thread_result{1, 0};

  while (current_element <= CurrentUpperLimit) {
    std::pair<qsizetype, qsizetype> current_result =
        CalculateCollatz(current_element);
    if (current_result.second > local_thread_result.second)
      local_thread_result = current_result;

    current_element = Elements++;
  }
  SaveFinalThreadResult(local_thread_result);

  // std::cout << std::this_thread::get_id() << " finished\n";
}
}  // namespace impl
}  // namespace Core
