#include "core.hpp"
namespace Core {
void CollatzProcessor::SetUpperLimit(qsizetype UpperLimit) noexcept {
  this->m_currentUpperLimit = UpperLimit;
  qInfo() << "ul:" << m_currentUpperLimit;
}
void CollatzProcessor::SetThreadLimit(qsizetype ThreadLimit) noexcept {
  this->m_currentThreadLimit = ThreadLimit;
  qInfo() << "tl:" << m_currentThreadLimit;
}
}  // namespace Core
