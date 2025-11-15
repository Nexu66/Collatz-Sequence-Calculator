#include "core.hpp"
namespace Core {
void CollatzProcessor::SetUpperLimit(size_t UpperLimit) noexcept {
  this->m_currentUpperLimit = UpperLimit;
  qInfo() << "ul:" << m_currentUpperLimit;
}
void CollatzProcessor::SetThreadLimit(size_t ThreadLimit) noexcept {
  this->m_currentThreadLimit = ThreadLimit;
  qInfo() << "tl:" << m_currentThreadLimit;
}
}  // namespace Core
