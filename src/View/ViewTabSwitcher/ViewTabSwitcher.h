#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_TAB_SWITCHER_VIEW_TAB_SWITCHER_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_TAB_SWITCHER_VIEW_TAB_SWITCHER_H_

#include <QMainWindow>

#include "../../Controller/Controller.h"
#include "../QCustomPlot/QCustomPlot.h"
#include "../ui_View.h"
#include "View/common/constants.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class ViewTabSwitcher : public QWidget {
  Q_OBJECT

 public:
  ViewTabSwitcher(Controller *controller, Ui::View *ui,
                  QWidget *parent = nullptr);
  ~ViewTabSwitcher() = default;

  void SetButtons();

 public slots:
  void SetExpressionCurrentIndex();
  void SetGraphCurrentIndex();
  void SetCreditCurrentIndex();
  void SetDepositCurrentIndex();
  void InitStackedWidgetIndex();

  void SetStyle(QPushButton *);

 protected:
  Ui::View *ui_;
  QWidget *parent_;
  Controller *controller_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_TAB_SWITCHER_VIEW_TAB_SWITCHER_H_
