#include "core.hpp"
namespace Core {
void CollatzProcessor::StartProcessing(std::stop_token stop,
                                       qsizetype CurrentThreadLimit,
                                       qsizetype CurrentUpperLimit) noexcept {
  qInfo() << "tl:" << CurrentThreadLimit << "ul:" << CurrentUpperLimit;
  emit SendCollatzResult(
      impl.StartProcessing(stop, CurrentThreadLimit, CurrentUpperLimit),
      impl.Timer);
}
}  // namespace Core
