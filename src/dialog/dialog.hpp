#pragma once

#include "view.hpp"

namespace Ui {

class Dialog;

class MainDialog : public View {
  Q_OBJECT

 public:
  MainDialog(QWidget* parent = nullptr);
  ~MainDialog();

 private slots:
  void on_btnStart_clicked() noexcept override;
  void on_btnExit_clicked() noexcept override;

  void on_sliderThreadCountSelector_valueChanged(int value) const noexcept;

  void DisplayCollatzResult(std::pair<qsizetype, qsizetype> CollatzResult,
                            timer::Timer Timer) noexcept override;
  void DisplayStopMessage() noexcept override;
  void DisplayOverflowMessage() noexcept override;
  void RetrySendingViewInfo() noexcept override;

 private:
  Dialog* m_ui;
};

}  // namespace Ui
