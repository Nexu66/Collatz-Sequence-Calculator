#pragma once
#include <QDebug>
#include <QObject>

#include "coreImpl.hpp"
namespace Core {
class Model : public QObject {
  Q_OBJECT
 public:
  virtual void SetUpperLimit(qsizetype UpperLimit) noexcept = 0;
  virtual void SetThreadLimit(qsizetype ThreadLimit) noexcept = 0;

 protected:
  qsizetype m_currentUpperLimit = 0;
  qsizetype m_currentThreadLimit = 1;
};

class CollatzProcessor : public Model {
  Q_OBJECT
  impl::CollatzProcessorImpl impl;
 private slots:
  void SetUpperLimit(qsizetype UpperLimit) noexcept override;
  void SetThreadLimit(qsizetype ThreadLimit) noexcept override;
};

}  // namespace Core
