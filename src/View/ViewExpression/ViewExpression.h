#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_EXPRESSION_VIEW_EXPRESSION_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_EXPRESSION_VIEW_EXPRESSION_H_

#include <QMainWindow>

#include "../../Controller/Controller.h"
#include "../QCustomPlot/QCustomPlot.h"
#include "../ui_View.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class ViewExpression : public QMainWindow {
  Q_OBJECT

 public:
  ViewExpression(Controller *controller, Ui::View *ui,
                 QWidget *parent = nullptr);
  ~ViewExpression();

  void Setup();

  void SetupClearButton();
  void SetupEqualButton();

  void SetupLineEditExpression();
  void SetupLineEditVariable();
  void HandleInsertButtonClick();
  void SetupNumberOperatorVariableButtons();
  void SetupFunctionsButtons();

  void HandleButtonEqualsClick();
  void HandleButtonClearClick();

  void HandleTextChanged(QLineEdit *line_edit, int &error_code);

  void HandleTextChangedLineEdit([[maybe_unused]] const QString &);
  void HandleTextChangedVariable([[maybe_unused]] const QString &);

  int GetVariableValue(double &variable_value);

  QString DoubleToSignificantString(const double &value);

  void SwitchLastCalculationsResult(const QString &);

 protected:
  Ui::View *ui_;
  QWidget *parent_;
  Controller *controller_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_EXPRESSION_VIEW_EXPRESSION_H_
