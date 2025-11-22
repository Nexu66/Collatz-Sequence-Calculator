#pragma once
#include <QDebug>
#include <QObject>
#include <stop_token>

#include "Timer.hpp"

namespace Core {
class Model : public QObject {
  Q_OBJECT
 public:
  virtual void StartProcessing(std::stop_token stop,
                               qsizetype CurrentCoresSelected,
                               qsizetype CurrentUpperLimit) noexcept = 0;
 signals:
  void SendCollatzResult(std::pair<qsizetype, qsizetype> CollatzResult,
                         timer::Timer Time);
  void SendStopMessage();
  void SendOverflowMessage();
  void RetryBtnStart();
};
}  // namespace Core
