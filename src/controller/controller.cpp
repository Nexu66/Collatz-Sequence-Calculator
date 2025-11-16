#include "controller.hpp"

namespace Ctrl {
Controller::Controller(Ui::View* ui, Core::Model* mod) : m_ui{ui}, m_mod{mod} {
  QObject::connect(m_ui.get(), &Ui::View::SendViewInfo, m_mod.get(),
                   &Core::Model::StartProcessing);
}

void Controller::show() const noexcept { m_ui->show(); }

}  // namespace Ctrl
