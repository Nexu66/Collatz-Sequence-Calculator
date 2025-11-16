#pragma once
#include <QDebug>
#include <QObject>

#include "coreImpl.hpp"
namespace Core {
class Model : public QObject {
  Q_OBJECT
 public:
  virtual void StartProcessing(qsizetype CurrentCoresSelected,
                               qsizetype CurrentUpperLimit) noexcept = 0;
 signals:
  void SendCollatzResult(std::pair<qsizetype, qsizetype> CollatzResult);
};

class CollatzProcessor : public Model {
  Q_OBJECT
  impl::CollatzProcessorImpl impl;
 private slots:
  void StartProcessing(qsizetype CurrentCoresSelected,
                       qsizetype CurrentUpperLimit) noexcept override;
};

}  // namespace Core
