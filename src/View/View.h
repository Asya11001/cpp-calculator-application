#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_H_

#include <QMainWindow>

#include "../Controller/Controller.h"
#include "QCustomPlot/QCustomPlot.h"
#include "ViewCredit/ViewCredit.h"
#include "ViewDeposit/ViewDeposit.h"
#include "ViewExpression/ViewExpression.h"
#include "ViewGraph/ViewGraph.h"
#include "ViewTabSwitcher/ViewTabSwitcher.h"
#include "ui_View.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

 protected:
  Ui::View *ui_;
  Controller *controller_;
  ViewExpression *view_expression_;
  ViewGraph *view_graph_;
  ViewCredit *view_credit_;
  ViewDeposit *view_deposit_;
  ViewTabSwitcher *view_tab_switcher_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_H_
