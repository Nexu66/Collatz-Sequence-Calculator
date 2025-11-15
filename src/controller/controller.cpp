#include "controller.hpp"

namespace Ctrl {
Controller::Controller(Ui::UserInterface* ui, Core::Model* mod)
    : m_ui{ui}, m_mod{mod} {
  QObject::connect(m_ui.get(), &Ui::UserInterface::SendThreadLimit, m_mod.get(),
                   &Core::Model::SetThreadLimit);
  QObject::connect(m_ui.get(), &Ui::UserInterface::SendUpperLimit, m_mod.get(),
                   &Core::Model::SetUpperLimit);
}

void Controller::show() const noexcept { m_ui->show(); }

void Controller::Start(size_t Threads, size_t Limit) {
  qInfo() << "T:" << Threads << "L:" << Limit;
}
}  // namespace Ctrl
