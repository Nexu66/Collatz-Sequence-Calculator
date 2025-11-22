#include "coreImpl.hpp"

namespace Core {
namespace impl {

const qsizetype CollatzProcessorImpl::cs_CoresCount =
    QThread::idealThreadCount();
std::vector<std::jthread> CollatzProcessorImpl::s_ThreadPool{
    static_cast<size_t>(CollatzProcessorImpl::cs_CoresCount)};

timer::Timer CollatzProcessorImpl::s_Timer{};

std::atomic<qsizetype>* CollatzProcessorImpl::s_Cache =
    new std::atomic<qsizetype>[cs_UpperLimitCap] { 0 };

CollatzProcessorImpl::CollatzProcessorImpl() {
  s_ThreadResults.resize(cs_CoresCount);
}

CollatzProcessorImpl::~CollatzProcessorImpl() { delete[] s_Cache; }

std::vector<std::pair<qsizetype, qsizetype>>
    CollatzProcessorImpl::s_ThreadResults{};

void CollatzProcessorImpl::RequestStop() {
  s_ThreadPool.begin()->request_stop();
}

bool CollatzProcessorImpl::WillOverflow(qsizetype current_element) {
  if (current_element > this->cs_MaxSizeBeforeOverflow) is_Overflow = true;
  return is_Overflow;
}

std::pair<qsizetype, qsizetype> CollatzProcessorImpl::StartProcessing(
    std::stop_token stop, const qsizetype CurrentThreadLimit,
    const qsizetype CurrentUpperLimit) {
  std::cout << "CURRENT CORES IN coreImpl: " << CurrentThreadLimit << "\n";
  const qsizetype ElementsPerThread = CurrentUpperLimit / CurrentThreadLimit;
  s_Timer.StartTimer();
  int i = 0;
  for (; i < CurrentThreadLimit - 1; ++i) {
    s_ThreadPool[i] = std::jthread{
        &CollatzProcessorImpl::Run,  this, stop, ElementsPerThread * i,
        ElementsPerThread * (i + 1), i};
  }
  s_ThreadPool[i] = std::jthread{
      &CollatzProcessorImpl::Run, this, stop, ElementsPerThread * i,
      CurrentUpperLimit,          i};

  for (int i = 0; i < CurrentThreadLimit; ++i) {
    s_ThreadPool[i].join();
  }

  if (stop.stop_requested() && is_Overflow)
    return std::make_pair(Signals::VALUE_OVERFLOWED, Signals::VALUE_OVERFLOWED);
  if (stop.stop_requested())
    return std::make_pair(Signals::STOP, Signals::STOP);

  std::pair<qsizetype, qsizetype> res = FindFinalResult();
  std::cout << "Out time is: " << s_Timer.StopTimer() << "ms\n";
  std::cout << "Num: " << res.first << " Count: " << res.second << "\n";

  return res;
}
void CollatzProcessorImpl::Run(std::stop_token stop,
                               const qsizetype IntervalBegin,
                               const qsizetype IntervalEnd,
                               const qsizetype IndexInResultsVector) {
  qsizetype current_element = IntervalEnd;
  qsizetype& result_element = s_ThreadResults[IndexInResultsVector].first;
  qsizetype& result_step_counter = s_ThreadResults[IndexInResultsVector].second;

  while (current_element > IntervalBegin) {
    qsizetype local_step_counter = 0;
    if (s_Cache[current_element - 1].load() == 0) {
      CalculateCollatz(current_element, local_step_counter);
    }
    if (result_step_counter < s_Cache[current_element - 1].load()) {
      result_step_counter = s_Cache[current_element - 1].load();
      result_element = current_element;
      result_step_counter = s_Cache[current_element - 1].load();
    }

    if (stop.stop_requested()) return;
    --current_element;
    ;
  }
  return;
}

void CollatzProcessorImpl::CalculateCollatz(qsizetype current_element,
                                            qsizetype& step_counter) {
  if (current_element == 1) return;
  if (current_element < cs_UpperLimitCap + 1 &&
      s_Cache[current_element - 1].load() != 0) {
    step_counter += s_Cache[current_element - 1].load();
    return;
  }
  if (WillOverflow(current_element)) this->RequestStop();
  CalculateCollatz(
      current_element % 2 ? current_element * 3 + 1 : current_element / 2,
      step_counter);
  ++step_counter;
  if (current_element < cs_UpperLimitCap + 1 &&
      s_Cache[current_element - 1].load() == 0)
    s_Cache[current_element - 1].store(std::atomic<qsizetype>{step_counter});
  return;
}

std::pair<qsizetype, qsizetype> CollatzProcessorImpl::FindFinalResult() {
  qsizetype largest_count = 0;
  qsizetype number = 1;
  for (int i = 0; i < s_ThreadResults.size(); ++i) {
    if (s_ThreadResults[i].second > largest_count) {
      largest_count = s_ThreadResults[i].second;
      number = s_ThreadResults[i].first;
    }
  }
  s_ThreadResults.assign(s_ThreadResults.size(),
                         std::pair<qsizetype, qsizetype>{0, 0});
  return std::make_pair(number, largest_count);
}

}  // namespace impl
}  // namespace Core
