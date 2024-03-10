#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_CREDIT_VIEW_CREDIT_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_CREDIT_VIEW_CREDIT_H_

#include <QMainWindow>

#include "../../Controller/Controller.h"
#include "../QCustomPlot/QCustomPlot.h"
#include "../number_validator/number_validator.h"
#include "../ui_View.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class ViewCredit : public QMainWindow {
  Q_OBJECT

  using Result = credit::data_structs::Result;
  using Parameters = credit::data_structs::Parameters;
  using TermType = credit::data_types::TermType;
  using PaymentType = credit::data_types::PaymentType;

 public:
  ViewCredit(Controller *controller, Ui::View *ui, QWidget *parent = nullptr);

  ~ViewCredit();

  void Setup();

  void SetupLineEdits();

  void SetupCreditAmountLineEdit();

  void SetupCreditDeadlineLineEdit();

  void SetupCreditInterestValueLineEdit();

  void SetupButtons();

  void SetupClearButton();

  void SetupCalculateButton();

  void HandleCalculateButtonClick();

  void HandleUpdateResults(const Result &result);

  void HandleClearResults();

  int ParseParameters(Parameters &);

  TermType GetCreditTermType(const std::string &string);

  PaymentType GetCreditPaymentType(const std::string &string);

  QString FormatMoney(const double &number, int decimal_places = 2);

  void HandleTextChanged(QLineEdit *line_edit, int &error_code);

  void HandleTextChangedAmount([[maybe_unused]] const QString &input_string);

  void HandleTextChangedDeadline([[maybe_unused]] const QString &input_string);

  void HandleTextChangedInterestValue(
      [[maybe_unused]] const QString &input_string);

 protected:
  Ui::View *ui_;
  QWidget *parent_;
  Controller *controller_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_CREDIT_VIEW_CREDIT_H_
