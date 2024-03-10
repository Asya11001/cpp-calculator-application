#include "ViewDeposit.h"

#include "../../Model/DepositCalculator/logger/logger.h"
#include "../common/constants.h"
#include "../common/error_code.h"
#include "../common/settings.h"
#include "View/style_handler/style_handler.h"

namespace s21 {

using IntervalType = deposit::data_types::IntervalType;
using InterestRateType = deposit::data_types::InterestRateType;
using TermType = deposit::data_types::TermType;
using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
using Parameters = deposit::Parameters;
using Result = deposit::Result;
using RawDate = deposit::data_structs::RawDate;
using DepositPeriod = deposit::data_structs::DepositPeriod;

ViewDeposit::ViewDeposit(Controller *controller, Ui::View *ui, QWidget *parent)
    : controller_(controller), ui_(ui), parent_(parent) {
  Setup();
}

ViewDeposit::~ViewDeposit() {
  remove(constants::kDepositLogsFileName);
  remove(constants::kTaxesLogsFileName);
  delete interest_rate_widget_;
  delete refills_widget_;
  delete partial_withdrawals_list_;
}

void ViewDeposit::Setup() {
  SetupButtons();
  SetupLineEdits();
  SetupCustomWidgets();
  SetupDateEdit();
  s21::deposit::logger::ClearLogFile();
  s21::deposit::logger::ClearTaxesLogFile();
}

void ViewDeposit::SetupCustomWidgets() {
  InitCustomWidgets();
  ConfigureCustomWidgets();
}

void ViewDeposit::InitCustomWidgets() {
  interest_rate_widget_ = new InterestRateWidget(this);
  refills_widget_ = new RefillsWidget(this);
  partial_withdrawals_list_ = new PartialWithdrawalsWidget(this);
}

void ViewDeposit::ConfigureCustomWidgets() {
  ui_->widget_interest_rate->setLayout(interest_rate_widget_->GetLayout());
  ui_->widget_refills->setLayout(refills_widget_->GetLayout());
  ui_->widget_withdrawals->setLayout(partial_withdrawals_list_->GetLayout());
}

void ViewDeposit::SetupButtons() {
  SetupClearButton();
  SetupCalculateButton();
  SetupTaxesLogsButton();
  SetupPaymentsLogsButton();
}

void ViewDeposit::SetupClearButton() {
  connect(ui_->push_button_deposit_calculate, &QPushButton::clicked, this,
          &ViewDeposit::HandleClearButtonClick);
}

void ViewDeposit::SetupCalculateButton() {
  connect(ui_->push_button_deposit_calculate, &QPushButton::clicked, this,
          &ViewDeposit::HandleCalculateButtonClick);
}

void ViewDeposit::SetupTaxesLogsButton() {
  connect(ui_->push_button_deposit_taxes_logs, &QPushButton::clicked, this,
          &ViewDeposit::HandleTaxesLogsButton);
}

void ViewDeposit::SetupPaymentsLogsButton() {
  connect(ui_->push_button_deposit_payments_logs, &QPushButton::clicked, this,
          &ViewDeposit::HandleDepositLogsButton);
}

/*
 * Insecure function uses system call!
 */
void ViewDeposit::HandleTaxesLogsButton() {
  char command[128] = {0};
#ifdef __linux__
  strncpy(command, "xdg-open ", 9);
#elif __APPLE__
  strncpy(command, "open ", 5);
#endif  //__linux__
  strncat(command, constants::kTaxesLogsFileName,
          strlen(constants::kTaxesLogsFileName));
  system(command);
}

/*
 * Insecure function uses system call!
 */
void ViewDeposit::HandleDepositLogsButton() {
  char command[128] = {0};
#ifdef __linux__
  strncpy(command, "xdg-open ", 9);
#elif __APPLE__
  strncpy(command, "open ", 5);
#endif  //__linux__
  strncat(command, constants::kDepositLogsFileName,
          strlen(constants::kDepositLogsFileName));
  system(command);
}

void ViewDeposit::SetupLineEdits() {
  SetupAmountLineEdit();
  SetupPlacementPeriodLineEdit();
}

void ViewDeposit::SetupAmountLineEdit() {
  connect(ui_->line_edit_deposit_deposit_amount, &QLineEdit::textChanged, this,
          &ViewDeposit::HandleTextChangedDepositAmount);
  connect(ui_->line_edit_deposit_deposit_amount, &QLineEdit::returnPressed,
          this, &ViewDeposit::Calculate);
}

void ViewDeposit::SetupPlacementPeriodLineEdit() {
  connect(ui_->line_edit_deposit_placement_period, &QLineEdit::textChanged,
          this, &ViewDeposit::HandleTextChangedDepositPlacementPeriod);
  connect(ui_->line_edit_deposit_placement_period, &QLineEdit::returnPressed,
          this, &ViewDeposit::Calculate);
}

void ViewDeposit::SetupDateEdit() {
  SetCurrentDate(ui_->date_edit_deposit_deposit_date);

  ui_->date_edit_deposit_deposit_date->setButtonSymbols(QDateEdit::NoButtons);
}

void ViewDeposit::HandleCalculateButtonClick() { Calculate(); }

void ViewDeposit::HandleClearButtonClick() {
  connect(ui_->push_button_deposit_clear, &QPushButton::clicked, this,
          &ViewDeposit::Clear);
}

int ViewDeposit::Calculate() {
  s21::deposit::logger::ClearLogFile();
  s21::deposit::logger::ClearTaxesLogFile();

  Parameters parameters{};
  int error_code = ParseParameters(parameters);
  if (!error_code) {
    error_code = controller_->DepositCalculate(parameters);
  }
  if (!error_code) {
    Result result = controller_->DepositGetResult();
    OutputDepositResult(result);
  }
  return error_code;
}

void ViewDeposit::OutputDepositResult(Result &result) {
  QString all_years_income_string = FormatMoney(result.GetAllYearsIncome());

  QString total_deposit_string = FormatMoney(result.GetTotalDeposit());

  QString all_years_taxes_string = FormatMoney(result.GetAllYearsTaxes());

  ui_->label_deposit_interest_charges_value->setText(all_years_income_string);
  ui_->label_deposit_deposit_plus_charges_value->setText(total_deposit_string);
  ui_->label_deposit_taxes_value->setText(all_years_taxes_string);
}

void ViewDeposit::Clear() {
  ClearParameters();
  ClearDepositResult();
}

void ViewDeposit::ClearDepositResult() {
  ui_->label_deposit_interest_charges_value->clear();
  ui_->label_deposit_deposit_plus_charges_value->clear();
  ui_->label_deposit_taxes_value->clear();
}

void ViewDeposit::ClearParameters() {
  ui_->line_edit_deposit_deposit_amount->clear();
  ui_->line_edit_deposit_placement_period->clear();
  SetCurrentDate(ui_->date_edit_deposit_deposit_date);
  interest_rate_widget_->RemoveLayout();
  interest_rate_widget_->RemoveLayout();
  interest_rate_widget_->RemoveLayout();
  refills_widget_->RemoveLayout();
  refills_widget_->RemoveLayout();
  refills_widget_->RemoveLayout();
  partial_withdrawals_list_->RemoveLayout();
  partial_withdrawals_list_->RemoveLayout();
  partial_withdrawals_list_->RemoveLayout();
  ui_->check_box_deposit_capitalization->setCheckState(Qt::Unchecked);
}

void ViewDeposit::SetCurrentDate(QDateEdit *date_edit) {
  QDate date = QDate::currentDate();
  date_edit->setDate(date);
}

QString ViewDeposit::FormatMoney(const double &number, int decimal_places) {
  QString formatted_amount = QString::number(number, 'f', decimal_places);

  QLocale locale(QLocale::English);
  formatted_amount =
      locale.toString(formatted_amount.toDouble(), 'f', decimal_places);

  return formatted_amount;
}

int ViewDeposit::ParseParameters(Parameters &parameters) {
  int error_code = error_code::kNoError;

  QLineEdit *deposit_amount = ui_->line_edit_deposit_deposit_amount;
  QLineEdit *deposit_placement_period = ui_->line_edit_deposit_placement_period;
  QComboBox *interval_type = ui_->combo_box_deposit_placement_period;
  QDateEdit *deposit_date = ui_->date_edit_deposit_deposit_date;
  QComboBox *payments_periodicity = ui_->combo_box_deposit_payments_periodicity;
  QCheckBox *capitalisation_check_box = ui_->check_box_deposit_capitalization;

  error_code |= HandleSetDepositAmount(parameters, deposit_amount);
  error_code |= HandleSetDepositPlacementPeriod(
      parameters, deposit_placement_period, interval_type);
  error_code |= interest_rate_widget_->SetInterestRates(parameters);
  error_code |= refills_widget_->SetTransactions(parameters);
  error_code |= partial_withdrawals_list_->SetTransactions(parameters);

  error_code |= HandleSetDepositDate(parameters, deposit_date);
  error_code |= HandleSetPaymentPeriodicity(parameters, payments_periodicity);
  HandleSetCapitalisationStatus(parameters, capitalisation_check_box);
  HandleSetDepositFinishDate(parameters);
  error_code |= HandleSetTax(parameters, 13);

  return error_code;
}

void ViewDeposit::HandleTextChanged(QLineEdit *line_edit, int &error_code) {
  if (error_code) {
    if (line_edit == ui_->line_edit_deposit_deposit_amount ||
        line_edit == ui_->line_edit_deposit_placement_period) {
      style_handler::SetDefaultLineEditDeposit(line_edit);
    }
    error_code = error_code::kNoError;
  }
}

void ViewDeposit::HandleTextChangedDepositAmount(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_deposit_deposit_amount,
                    settings::error_code_deposit_amount);
}

void ViewDeposit::HandleTextChangedDepositPlacementPeriod(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_deposit_placement_period,
                    settings::error_code_deposit_placing_period);
}

[[nodiscard]] IntervalType ViewDeposit::GetPaymentPeriodicity(
    const QString &string) {
  IntervalType interval = IntervalType::kNone;

  if (string == "Every month") {
    interval = IntervalType::kOneInMonth;
  } else if (string == "At the end") {
    interval = IntervalType::kAtTheEndOfInterval;
  } else if (string == "Every day") {
    interval = IntervalType::kOneInDay;
  } else if (string == "Every week") {
    interval = IntervalType::kOneInWeek;
  } else if (string == "Every quarter") {
    interval = IntervalType::kOneInQuarter;
  } else if (string == "Every half of year") {
    interval = IntervalType::kOneInHalfYear;
  } else if (string == "Every year") {
    interval = IntervalType::kOneInYear;
  }

  return interval;
}

[[nodiscard]] TermType ViewDeposit::GetDepositTermType(const QString &string) {
  TermType term_type = TermType::kNone;

  if (string == "Year") {
    term_type = TermType::kYears;
  } else if (string == "Month") {
    term_type = TermType::kMonths;
  } else if (string == "Day") {
    term_type = TermType::kDays;
  }

  return term_type;
}

[[nodiscard]] InterestRateType ViewDeposit::GetInterestRate(
    const QString &string) {
  InterestRateType interest_rate_type = InterestRateType::kFixed;

  if (string == "Fix") {
    interest_rate_type = InterestRateType::kFixed;
  } else if (string == "Depends on sum") {
    interest_rate_type = InterestRateType::kDependsOnSum;
  } else if (string == "Depends on day") {
    interest_rate_type = InterestRateType::kDependsOnDayIndex;
  }

  return interest_rate_type;
}

[[nodiscard]] IntervalType ViewDeposit::GetIntervalType(const QString &string) {
  IntervalType interval_type = IntervalType::kOneInMonth;

  if (string == "Once") {
    interval_type = IntervalType::kAtOnce;
  } else if (string == "One in month") {
    interval_type = IntervalType::kOneInMonth;
  } else if (string == "One in two months") {
    interval_type = IntervalType::kOneInTwoMonth;
  } else if (string == "One in quarter") {
    interval_type = IntervalType::kOneInQuarter;
  } else if (string == "One in half of year") {
    interval_type = IntervalType::kOneInHalfYear;
  } else if (string == "One in year") {
    interval_type = IntervalType::kOneInYear;
  }

  return interval_type;
}

int ViewDeposit::HandleSetDepositAmount(Parameters &parameters,
                                        QLineEdit *amount_line_edit) {
  QString deposit_amount_string = amount_line_edit->text();

  double deposit_amount{0};

  int error_code = error_code::kNoError;

  if (!number_validator::IsDoubleNumber(deposit_amount_string)) {
    error_code = error_code::kIncorrectDepositValue;
    style_handler::SetIncorrectLineEditDeposit(amount_line_edit);
    settings::error_code_deposit_amount = error_code;
  }

  if (!error_code) {
    deposit_amount = deposit_amount_string.toDouble();
    if (deposit_amount <= constants::kMinDepositAmountValue) {
      error_code = error_code::kIncorrectDepositValue;
    }
    if (deposit_amount > constants::kMaxDepositAmountValue) {
      error_code = error_code::kIncorrectDepositValue;
    }
    if (error_code) {
      settings::error_code_deposit_amount = error_code;

      style_handler::SetIncorrectLineEditDeposit(amount_line_edit);
    }
  }

  if (!error_code) {
    parameters.GetAmount() = deposit_amount;
  }

  return error_code;
}

int ViewDeposit::HandleSetDepositPlacementPeriod(
    Parameters &parameters, QLineEdit *deposit_placement_period_element,
    QComboBox *interval_type) {
  QString deposit_placement_period_string =
      deposit_placement_period_element->text();

  int deposit_placement_period{0};

  int error_code = error_code::kNoError;

  if (!number_validator::IsIntNumber(deposit_placement_period_string)) {
    error_code = error_code::kIncorrectPlacementPeriod;
    style_handler::SetIncorrectLineEditDeposit(
        deposit_placement_period_element);
    settings::error_code_deposit_placing_period = error_code;
  }
  if (!error_code) {
    deposit_placement_period = deposit_placement_period_string.toInt();
  }

  TermType deposit_term_type = GetDepositTermType(interval_type->currentText());

  error_code = TestCorrectnessPlacementDepositPeriod(deposit_term_type,
                                                     deposit_placement_period);

  if (error_code) {
    error_code = error_code::kIncorrectPlacementPeriod;
    style_handler::SetIncorrectLineEditDeposit(
        deposit_placement_period_element);
    settings::error_code_deposit_placing_period = error_code;
  }
  if (!settings::error_code_deposit_amount &&
      !settings::error_code_deposit_placing_period) {
    parameters.GetDepositPeriod().deposit_posting_period_ =
        deposit_placement_period;
    parameters.GetDepositPeriod().deposit_term_ = deposit_term_type;
  }

  error_code = settings::error_code_deposit_amount |
               settings::error_code_deposit_placing_period;
  return error_code;
}

int ViewDeposit::TestCorrectnessPlacementDepositPeriod(
    const TermType &term_type, const int &placement_period) {
  int errorCode = error_code::kNoError;

  if (term_type == TermType::kDays)
    if (placement_period > constants::kMaxDepositPostingPeriodDays) {
      errorCode = error_code::kIncorrectPlacementPeriod;
    }
  if (term_type == TermType::kMonths)
    if (placement_period > constants::kMaxDepositPostingPeriodMonths) {
      errorCode = error_code::kIncorrectPlacementPeriod;
    }
  if (term_type == TermType::kYears)
    if (placement_period > constants::kMaxDepositPostingPeriodYears) {
      errorCode = error_code::kIncorrectPlacementPeriod;
    }
  if (placement_period < constants::kMinDepositPostingPeriod) {
    errorCode = error_code::kIncorrectPlacementPeriod;
  }

  return errorCode;
}

int ViewDeposit::HandleSetDepositDate(Parameters &parameters,
                                      QDateEdit *deposit_date) {
  int error_code = error_code::kNoError;
  QDate date = deposit_date->date();

  RawDate raw_date = {date.day(), date.month() - 1, date.year()};

  error_code = SetDepositDate(parameters, raw_date);

  return error_code;
}

int ViewDeposit::SetDepositDate(Parameters &parameters,
                                const RawDate &raw_date) {
  int error_code = error_code::kNoError;
  DateType date = constants::kInitDate;

  if (IsNegativeDate(raw_date)) {
    error_code = error_code::kDateIsNegativeNumber;
  }
  if (!error_code) {
    error_code = SetDate(raw_date, date);
  }
  if (!error_code) {
    parameters.GetStartDate() = date;
  }

  return error_code;
}

int ViewDeposit::IsNegativeDate(const RawDate &raw_date) {
  bool flag = (raw_date.day_ < constants::kInitValue ||
               raw_date.month_ < constants::kInitValue ||
               raw_date.year_ < constants::kInitValue);
  return flag;
}

int ViewDeposit::SetDate(const RawDate &raw_date, DateType &date) {
  int error_code = error_code::kNoError;

  date.tm_mday = raw_date.day_;
  date.tm_mon = raw_date.month_;
  date.tm_year = raw_date.year_ - constants::kYearBase;

  error_code = IsDateValid(date);

  return error_code;
}

int ViewDeposit::IsDateValid(DateType &date) {
  int error_code = error_code::kNoError;
  DateType date_copy{};

  CopyDate(date_copy, date);

  time_t time = mktime(&date);

  DateType convertedDate = *localtime(&time);

  if (time == (error_code::kMktimeError) ||
      !AreDatesEqual(date_copy, convertedDate)) {
    error_code = error_code::kDateIsInvalid;
  }
  return error_code;
}

void ViewDeposit::CopyDate(DateType &dest, const DateType &src) {
  dest.tm_mday = src.tm_mday;
  dest.tm_mon = src.tm_mon;
  dest.tm_year = src.tm_year;
}

bool ViewDeposit::AreDatesEqual(DateType date1, DateType date2) {
  bool flag = (date1.tm_mday == date2.tm_mday && date1.tm_mon == date2.tm_mon &&
               date1.tm_year == date2.tm_year);
  return flag;
}

int ViewDeposit::HandleSetPaymentPeriodicity(Parameters &parameters,
                                             QComboBox *payments_periodicity) {
  int error_code = error_code::kNoError;

  QString payment_string = payments_periodicity->currentText();

  IntervalType interval = GetPaymentPeriodicity(payment_string);

  error_code = SetPeriodicityOfPayments(parameters, interval);

  return error_code;
}

int ViewDeposit::SetPeriodicityOfPayments(Parameters &parameters,
                                          const IntervalType &periodicity) {
  int error_code = error_code::kNoError;

  if (periodicity == IntervalType::kNone) {
    error_code = error_code::kPeriodicityOfPaymentsIsNotSet;
  }
  if (!IsValidIntervalForPeriodicityOfPayments(periodicity)) {
    error_code = error_code::kPeriodicityOfPaymentsIsIncorrect;
  }
  if (!error_code) {
    parameters.GetPeriodicityOfPayments() = periodicity;
  }

  return error_code;
}

bool ViewDeposit::IsValidIntervalForPeriodicityOfPayments(
    const IntervalType &interval) {
  bool flag = (interval == IntervalType::kAtTheEndOfInterval ||
               interval == IntervalType::kOneInDay ||
               interval == IntervalType::kOneInMonth ||
               interval == IntervalType::kOneInWeek ||
               interval == IntervalType::kOneInQuarter ||
               interval == IntervalType::kOneInHalfYear ||
               interval == IntervalType::kOneInYear);
  return flag;
}

void ViewDeposit::HandleSetCapitalisationStatus(Parameters &parameters,
                                                QCheckBox *check_box) {
  CapitalisationStatus status = CapitalisationStatus::kOff;

  int check_box_status = check_box->isChecked();

  if (check_box_status) {
    status = CapitalisationStatus::kOn;
  }

  parameters.GetCapitalisationStatus() = status;
}

void ViewDeposit::HandleSetDepositFinishDate(Parameters &parameters) {
  SetDepositFinishDate(parameters);
}

void ViewDeposit::SetDepositFinishDate(Parameters &parameters) {
  DateType deposit_end = parameters.GetStartDate();

  int deposit_posting_period =
      parameters.GetDepositPeriod().deposit_posting_period_;

  if (parameters.GetDepositPeriod().deposit_term_ == TermType::kDays) {
    deposit_end.tm_mday += deposit_posting_period;
  } else if (parameters.GetDepositPeriod().deposit_term_ == TermType::kMonths) {
    deposit_end.tm_mon += deposit_posting_period;
  } else if (parameters.GetDepositPeriod().deposit_term_ == TermType::kYears) {
    deposit_end.tm_year += deposit_posting_period;
  }

  mktime(&deposit_end);
  CopyDate(parameters.GetFinishDate(), deposit_end);
}

int ViewDeposit::HandleSetTax(Parameters &parameters, const double &tax_value) {
  return parameters.SetTax(tax_value);
}

}  // namespace s21
