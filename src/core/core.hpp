#pragma once

#include "coreImpl.hpp"
#include "model.hpp"
namespace Core {

class CollatzProcessor : public Model {
  Q_OBJECT
  impl::CollatzProcessorImpl impl;

 private:
  void StartProcessing(std::stop_token stop, qsizetype CurrentCoresSelected,
                       qsizetype CurrentUpperLimit) noexcept override;
};

}  // namespace Core
