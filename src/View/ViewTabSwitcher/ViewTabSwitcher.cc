#include "ViewTabSwitcher.h"

#include <QObject>

#include "View/style_handler/style_handler.h"

namespace s21 {
ViewTabSwitcher::ViewTabSwitcher(Controller *controller, Ui::View *ui,
                                 QWidget *parent)
    : controller_(controller), ui_(ui), parent_(parent) {
  SetButtons();
};

void ViewTabSwitcher::SetButtons() {
  InitStackedWidgetIndex();

  connect(ui_->push_button_expression, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetExpressionCurrentIndex);
  connect(ui_->push_button_graph, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetGraphCurrentIndex);
  connect(ui_->push_button_credit, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetCreditCurrentIndex);
  connect(ui_->push_button_deposit, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetDepositCurrentIndex);
  SetExpressionCurrentIndex();
}

void ViewTabSwitcher::InitStackedWidgetIndex() {
  SetStyle(ui_->push_button_expression);
  ui_->stacked_widget->setCurrentIndex(constants::kExpressionTabIndex);
}

void ViewTabSwitcher::SetExpressionCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(constants::kExpressionTabIndex);
    ui_->line_edit_expression->setFocus();
  }
}
void ViewTabSwitcher::SetGraphCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(constants::kGraphTabIndex);
    ui_->line_edit_graph_expression->setFocus();
  }
}
void ViewTabSwitcher::SetCreditCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(constants::kCreditTabIndex);
    ui_->line_edit_credit_credit_amount->setFocus();
  }
}
void ViewTabSwitcher::SetDepositCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(constants::kDepositTabIndex);
    ui_->line_edit_deposit_deposit_amount->setFocus();
  }
}
void ViewTabSwitcher::SetStyle(QPushButton *push_button) {
  style_handler::SetUnselectedTabButton(ui_->push_button_expression);
  style_handler::SetUnselectedTabButton(ui_->push_button_graph);
  style_handler::SetUnselectedTabButton(ui_->push_button_credit);
  style_handler::SetUnselectedTabButton(ui_->push_button_deposit);
  if (push_button) {
    style_handler::SetSelectedTabButton(push_button);
  }
}
}  // namespace s21
