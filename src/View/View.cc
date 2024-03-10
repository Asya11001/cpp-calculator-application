
#include "View.h"

namespace s21 {

View::View(Controller *controller, QWidget *parent)
    : controller_(controller), QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);

  view_expression_ = new ViewExpression(controller_, ui_, this);
  view_graph_ = new ViewGraph(controller_, ui_, this);
  view_credit_ = new ViewCredit(controller_, ui_, this);
  view_deposit_ = new ViewDeposit(controller_, ui_, this);
  view_tab_switcher_ = new ViewTabSwitcher(controller_, ui_, this);
  ui_->line_edit_expression->setFocus();
}

View::~View() {
  delete ui_;
  delete view_expression_;
  delete view_graph_;
  delete view_credit_;
  delete view_deposit_;
  delete view_tab_switcher_;
}

}  // namespace s21
