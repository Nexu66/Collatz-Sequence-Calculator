#pragma once
#include <QAbstractButton>
#include <QScopedPointer>

#include "core.hpp"
#include "dialog.hpp"
namespace Ctrl {
class Controller : public QObject {
  Q_OBJECT
  QScopedPointer<Ui::UserInterface> m_ui;
  QScopedPointer<Core::Model> m_mod;

 public:
  Controller(Ui::UserInterface* ui, Core::Model* mod);
  void show() const noexcept;

 private slots:
  void Start(qsizetype Threads, qsizetype Limit);
};
}  // namespace Ctrl
