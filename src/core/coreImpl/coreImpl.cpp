#include "coreImpl.hpp"

namespace Core {
namespace impl {

const qsizetype CollatzProcessorImpl::s_CoresCount =
    QThread::idealThreadCount();
std::vector<std::jthread> CollatzProcessorImpl::s_ThreadPool{
    static_cast<size_t>(CollatzProcessorImpl::s_CoresCount)};
const qsizetype s_MaxSize = std::numeric_limits<qsizetype>::max();
std::atomic<int> CollatzProcessorImpl::elements = 0;

std::pair<int, int> CollatzProcessorImpl::StartProcessing(
    const qsizetype CurrentThreadLimit, const qsizetype CurrentUpperLimit) {
  for (int i = 0; i < CurrentThreadLimit; ++i) {
    s_ThreadPool[i] = std::jthread{[&](std::stop_token stop) {
      int current_element = elements++;
      qInfo() << current_element << " " << elements;
    }};
  }

  qInfo() << "Hellow";
  return std::make_pair(1, 0);
}
}  // namespace impl
}  // namespace Core
