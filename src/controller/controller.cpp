#include "controller.hpp"

namespace Ctrl {

Controller::Controller(Ui::View* ui, Core::Model* mod) : m_ui{ui}, m_mod{mod} {
  QObject::connect(m_ui.get(), &Ui::View::SendViewInfo, this,
                   &Controller::LaunchModel);
  QObject::connect(m_mod.get(), &Core::Model::SendCollatzResult, m_ui.get(),
                   &Ui::View::DisplayCollatzResult);
}

void Controller::LaunchModel(qsizetype CurrentCoresSelected,
                             qsizetype CurrentUpperLimit) {
  ModelThread = std::jthread{
      [&] { m_mod->StartProcessing(CurrentCoresSelected, CurrentUpperLimit); }};
}

void Controller::show() const noexcept { m_ui->show(); }

}  // namespace Ctrl
