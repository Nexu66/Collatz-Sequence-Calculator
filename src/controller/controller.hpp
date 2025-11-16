#pragma once
#include <QAbstractButton>
#include <QScopedPointer>
#include <thread>

#include "core.hpp"
#include "dialog.hpp"
namespace Ctrl {
class Controller : public QObject {
  Q_OBJECT
  QScopedPointer<Ui::View> m_ui;
  QScopedPointer<Core::Model> m_mod;
  std::jthread ModelThread;

 private slots:
  void LaunchModel(qsizetype CurrentCoresSelected, qsizetype CurrentUpperLimit);
  void StopAlgorithm();

 public:
  Controller(Ui::View* ui, Core::Model* mod);
  void show() const noexcept;

};
}  // namespace Ctrl
