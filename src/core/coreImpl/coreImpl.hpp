#pragma once
#include <QList>
#include <QThread>
#include <thread>

namespace Core {
namespace impl {
class CollatzProcessorImpl {
 public:
  static const qsizetype CoresCount;
  static const QList<std::jthread> thread_pool;
};

}  // namespace impl
}  // namespace Core
