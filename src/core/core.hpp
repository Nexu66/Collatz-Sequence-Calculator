#pragma once
#include <QDebug>
#include <QObject>
namespace Core {
class Model : public QObject {
  Q_OBJECT
 public:
  virtual void SetUpperLimit(size_t UpperLimit) noexcept = 0;
  virtual void SetThreadLimit(size_t ThreadLimit) noexcept = 0;

 protected:
  size_t m_currentUpperLimit = 0;
  size_t m_currentThreadLimit = 1;
};

class CollatzProcessor : public Model {
  Q_OBJECT
 private slots:
  void SetUpperLimit(size_t UpperLimit) noexcept override;
  void SetThreadLimit(size_t ThreadLimit) noexcept override;
};

}  // namespace Core
