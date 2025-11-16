#include "core.hpp"
namespace Core {
void CollatzProcessor::StartProcessing(std::stop_token stop,
                                       qsizetype CurrentThreadLimit,
                                       qsizetype CurrentUpperLimit) noexcept {
  qInfo() << "tl:" << CurrentThreadLimit << "ul:" << CurrentUpperLimit;
  auto algorithm_result =
      impl.StartProcessing(stop, CurrentThreadLimit, CurrentUpperLimit);
  if (algorithm_result.first != -1 && algorithm_result.second != -1)
    emit SendCollatzResult(algorithm_result, impl.Timer);
  else {
    emit SendStopMessage();
  }
}
}  // namespace Core
