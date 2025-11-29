#pragma once

#include "coreImpl.hpp"
#include "model.hpp"
namespace Core {

class CollatzProcessor : public Model {
  Q_OBJECT
  impl::CollatzProcessorImpl m_Impl;

 protected:
  void StartProcessing(const std::stop_token StopToken,
                       const qsizetype CurrentCoresSelected,
                       const qsizetype CurrentUpperLimit) noexcept override;
};

}  // namespace Core
