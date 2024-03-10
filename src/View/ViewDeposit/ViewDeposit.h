#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_VIEW_DEPOSIT_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_VIEW_DEPOSIT_H_

#include <QMainWindow>
#include <ctime>

#include "../../Controller/Controller.h"
#include "../../Model/DepositCalculator/Parameters/Parameters.h"
#include "../../Model/DepositCalculator/Result/Result.h"
#include "../../Model/DepositCalculator/common/data_structs.h"
#include "../QCustomPlot/QCustomPlot.h"
#include "../common/error_code.h"
#include "../number_validator/number_validator.h"
#include "../ui_View.h"
#include "widgets/InterestRateWidget/InterestRateWidget.h"
#include "widgets/PartialWithdrawalsWidget/PartialWithdrawalsWidget.h"
#include "widgets/RefillsWidget/RefillsWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class ViewDeposit : public QMainWindow {
  Q_OBJECT
  using IntervalType = deposit::data_types::IntervalType;
  using InterestRateType = deposit::data_types::InterestRateType;
  using TermType = deposit::data_types::TermType;
  using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
  using Parameters = deposit::Parameters;
  using Result = deposit::Result;
  using RawDate = deposit::data_structs::RawDate;

 public:
  ViewDeposit(Controller *controller, Ui::View *ui, QWidget *parent = nullptr);

  ~ViewDeposit();

  void Setup();

  void SetupButtons();

  void SetupClearButton();

  void SetupCalculateButton();

  void SetupTaxesLogsButton();

  void SetupPaymentsLogsButton();

  void SetupLineEdits();

  void SetupAmountLineEdit();

  void SetupPlacementPeriodLineEdit();

  void SetupDateEdit();

  void HandleCalculateButtonClick();

  void HandleClearButtonClick();

  int ParseParameters(Parameters &parameters);

  [[nodiscard]] static IntervalType GetPaymentPeriodicity(
      const QString &string);

  [[nodiscard]] static TermType GetDepositTermType(const QString &string);

  [[nodiscard]] static InterestRateType GetInterestRate(const QString &string);

  [[nodiscard]] static IntervalType GetIntervalType(const QString &string);

  static int HandleSetDepositAmount(Parameters &parameters,
                                    QLineEdit *deposit_amount_line_edit);

  int HandleSetDepositPlacementPeriod(Parameters &parameters, QLineEdit *,
                                      QComboBox *);

  static void HandleTaxesLogsButton();
  static void HandleDepositLogsButton();

  static int TestCorrectnessPlacementDepositPeriod(const TermType &term_type,
                                                   const int &placement_period);

  int HandleSetDepositDate(Parameters &parameters, QDateEdit *deposit_date);

  int SetDepositDate(Parameters &parameters, const RawDate &raw_date);

  static int IsNegativeDate(const RawDate &raw_date);

  int SetDate(const RawDate &raw_date, DateType &date);

  int IsDateValid(DateType &date);

  static void CopyDate(DateType &dest, const DateType &src);

  static bool AreDatesEqual(DateType date1, DateType date2);

  int HandleSetPaymentPeriodicity(Parameters &parameters,
                                  QComboBox *payments_periodicity);

  int SetPeriodicityOfPayments(Parameters &parameters,
                               const IntervalType &periodicity);

  static bool IsValidIntervalForPeriodicityOfPayments(
      const IntervalType &interval);

  static void HandleSetCapitalisationStatus(Parameters &parameters,
                                            QCheckBox *check_box);

  void HandleSetDepositFinishDate(Parameters &parameters);

  void SetDepositFinishDate(Parameters &parameters);

  static int HandleSetTax(Parameters &parameters, const double &tax_value);

  int Calculate();

  void SetupCustomWidgets();

  void InitCustomWidgets();

  void ConfigureCustomWidgets();

  void HandleTextChanged(QLineEdit *line_edit, int &error_code);

  void HandleTextChangedDepositAmount(
      [[maybe_unused]] const QString &input_string);
  void HandleTextChangedDepositPlacementPeriod(
      [[maybe_unused]] const QString &input_string);

  void OutputDepositResult(Result &result);
  static QString FormatMoney(const double &number, int decimal_places = 2);

  void Clear();
  void ClearDepositResult();
  void ClearParameters();

  static void SetCurrentDate(QDateEdit *date_edit);

 protected:
  Ui::View *ui_;
  QWidget *parent_;
  Controller *controller_;
  InterestRateWidget *interest_rate_widget_;
  RefillsWidget *refills_widget_;
  PartialWithdrawalsWidget *partial_withdrawals_list_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_VIEW_DEPOSIT_H_
