#include "coreImpl.hpp"

namespace Core {
namespace impl {
const qsizetype CollatzProcessorImpl::CoresCount = QThread::idealThreadCount();
const QList<std::jthread> CollatzProcessorImpl::thread_pool{
    CollatzProcessorImpl::CoresCount};
}  // namespace impl
}  // namespace Core
