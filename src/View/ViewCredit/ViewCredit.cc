#include "ViewCredit.h"

#include "../../Model/CreditCalculator/common/data_structs.h"
#include "../common/constants.h"
#include "../common/error_code.h"
#include "../common/settings.h"
#include "View/style_handler/style_handler.h"

namespace s21 {

using Parameters = credit::data_structs::Parameters;
using Result = credit::data_structs::Result;
using TermType = credit::data_types::TermType;
using PaymentType = credit::data_types::PaymentType;

ViewCredit::ViewCredit(Controller *controller, Ui::View *ui, QWidget *parent)
    : controller_(controller), ui_(ui), parent_(parent) {
  Setup();
};

ViewCredit::~ViewCredit() = default;

void ViewCredit::Setup() {
  SetupLineEdits();
  SetupButtons();
}

void ViewCredit::SetupLineEdits() {
  SetupCreditAmountLineEdit();
  SetupCreditDeadlineLineEdit();
  SetupCreditInterestValueLineEdit();
}

void ViewCredit::SetupCreditAmountLineEdit() {
  connect(ui_->line_edit_credit_credit_amount, &QLineEdit::returnPressed, this,
          &ViewCredit::HandleCalculateButtonClick);
  connect(ui_->line_edit_credit_credit_amount, &QLineEdit::textChanged, this,
          &ViewCredit::HandleTextChangedAmount);
}

void ViewCredit::SetupCreditDeadlineLineEdit() {
  connect(ui_->line_edit_credit_credit_deadline, &QLineEdit::returnPressed,
          this, &ViewCredit::HandleCalculateButtonClick);
  connect(ui_->line_edit_credit_credit_deadline, &QLineEdit::textChanged, this,
          &ViewCredit::HandleTextChangedDeadline);
}

void ViewCredit::SetupCreditInterestValueLineEdit() {
  connect(ui_->line_edit_credit_interest_value, &QLineEdit::returnPressed, this,
          &ViewCredit::HandleCalculateButtonClick);
  connect(ui_->line_edit_credit_interest_value, &QLineEdit::textChanged, this,
          &ViewCredit::HandleTextChangedInterestValue);
}

void ViewCredit::SetupButtons() {
  SetupClearButton();
  SetupCalculateButton();
}

void ViewCredit::SetupClearButton() {
  connect(ui_->push_button_credit_clear, &QPushButton::clicked, this,
          &ViewCredit::HandleClearResults);
}

void ViewCredit::SetupCalculateButton() {
  connect(ui_->push_button_credit_calculate, &QPushButton::clicked, this,
          &ViewCredit::HandleCalculateButtonClick);
}

void ViewCredit::HandleCalculateButtonClick() {
  Parameters parameters{};
  int error_code = ParseParameters(parameters);
  if (!error_code) {
    error_code = controller_->CreditCalculate(parameters);
  }
  if (!error_code) {
    Result result = controller_->CreditGetResult();
    HandleClearResults();
    HandleUpdateResults(result);
  }
}

void ViewCredit::HandleUpdateResults(const Result &result) {
  QString monthly_payment_string = FormatMoney(result.monthly_payment_begin_);

  if (result.monthly_payment_begin_ != result.monthly_payments_end_) {
    monthly_payment_string += "...";
    QString monthly_payment_end_string =
        FormatMoney(result.monthly_payments_end_);
    monthly_payment_string += monthly_payment_end_string;
  }
  QString charges_string = FormatMoney(result.overpayment_);

  QString overpayment_size_string = FormatMoney(result.total_payment_);

  ui_->label_credit_monthly_payment_result_value->setText(
      monthly_payment_string);
  ui_->label_credit_interest_charges_value->setText(charges_string);
  ui_->label_credit_debt_plus_charges_value->setText(overpayment_size_string);
}

void ViewCredit::HandleClearResults() {
  ui_->label_credit_monthly_payment_result_value->clear();
  ui_->label_credit_interest_charges_value->clear();
  ui_->label_credit_debt_plus_charges_value->clear();
}

int ViewCredit::ParseParameters(Parameters &parameters) {
  QString credit_amount_string = ui_->line_edit_credit_credit_amount->text();
  QString credit_deadline_string =
      ui_->line_edit_credit_credit_deadline->text();
  QString credit_interest_value_string =
      ui_->line_edit_credit_interest_value->text();
  std::string credit_term_type_string;
  std::string credit_payment_type_string;

  credit_term_type_string =
      ui_->combo_box_credit_term_type->currentText().toStdString();
  credit_payment_type_string =
      ui_->combo_box_credit_payments_type->currentText().toStdString();

  PaymentType payment_type = GetCreditPaymentType(credit_payment_type_string);
  TermType credit_term_type = GetCreditTermType(credit_term_type_string);

  int error_code = error_code::kNoError;

  double amount = credit_amount_string.toDouble();
  int deadline = credit_deadline_string.toInt();
  double interest_value = credit_interest_value_string.toDouble();

  int is_credit_value_ok =
      number_validator::IsDoubleNumber(credit_amount_string);
  int is_credit_deadline_ok =
      number_validator::IsIntNumber(credit_deadline_string);
  int is_interest_value_ok =
      number_validator::IsDoubleNumber(credit_interest_value_string);

  if (credit_term_type == TermType::kYears) {
    deadline *= 12;
    credit_term_type = TermType::kMonths;
  }
  bool is_credit_value_bad = (!is_credit_value_ok || amount <= 0 ||
                              amount >= constants::kMaxCreditAmount);
  if (is_credit_value_bad) {
    error_code = 1;
    settings::error_code_credit_amount = error_code::kInvalidExpressionFormat;
    style_handler::SetIncorrectCreditLineEdit(
        ui_->line_edit_credit_credit_amount);
  }

  bool is_credit_deadline_bad = (!is_credit_deadline_ok || deadline <= 0 ||
                                 deadline > constants::kMaxMonthCreditDuration);
  if (is_credit_deadline_bad) {
    error_code = error_code::kInvalidExpressionFormat;
    settings::error_code_credit_deadline = error_code::kInvalidExpressionFormat;
    style_handler::SetIncorrectCreditLineEdit(
        ui_->line_edit_credit_credit_deadline);
  }

  bool is_interest_rate_bad = (!is_interest_value_ok ||
                               interest_value <= constants::kMinInterestValue ||
                               interest_value > constants::kMaxInterestValue);
  if (is_interest_rate_bad) {
    error_code = error_code::kInvalidExpressionFormat;
    settings::error_code_credit_interest_value =
        error_code::kInvalidExpressionFormat;
    style_handler::SetIncorrectCreditLineEdit(
        ui_->line_edit_credit_interest_value);
  }

  if (!error_code) {
    parameters.amount_ = amount;
    parameters.deadline_ = deadline;
    parameters.interest_rate_ = interest_value;
    parameters.payment_type_ = payment_type;
    parameters.term_type_ = credit_term_type;
  }

  return error_code;  // TODO refactoring function
}

TermType ViewCredit::GetCreditTermType(const std::string &string) {
  TermType result_value = TermType::kNone;

  if (string.find("Year") == 0) {
    result_value = credit::data_types::TermType::kYears;
  } else if (string.find("Month") == 0) {
    result_value = credit::data_types::TermType::kMonths;
  }

  return result_value;
}

PaymentType ViewCredit::GetCreditPaymentType(const std::string &string) {
  PaymentType result_value = PaymentType::kNone;

  if (string.find("Differential") == 0) {
    result_value = PaymentType::kDifferential;
  } else if (string.find("Annual") == 0) {
    result_value = PaymentType::kAnnual;
  }

  return result_value;
}

QString ViewCredit::FormatMoney(const double &number, int decimal_places) {
  QString formatted_amount = QString::number(number, 'f', decimal_places);

  QLocale locale(QLocale::English);
  formatted_amount =
      locale.toString(formatted_amount.toDouble(), 'f', decimal_places);

  return formatted_amount;
}

void ViewCredit::HandleTextChanged(QLineEdit *line_edit, int &error_code) {
  if (error_code) {
    if (line_edit == ui_->line_edit_credit_credit_amount) {
      style_handler::SetDefaultCreditLineEdit(line_edit);
    } else if (line_edit == ui_->line_edit_credit_credit_deadline) {
      style_handler::SetDefaultCreditLineEdit(line_edit);
    } else if (line_edit == ui_->line_edit_credit_interest_value) {
      style_handler::SetDefaultCreditLineEdit(line_edit);
    }
    error_code = 0;
  }
}

void ViewCredit::HandleTextChangedAmount(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_credit_credit_amount,
                    settings::error_code_credit_amount);
}

void ViewCredit::HandleTextChangedDeadline(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_credit_credit_deadline,
                    settings::error_code_credit_deadline);
}

void ViewCredit::HandleTextChangedInterestValue(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_credit_interest_value,
                    settings::error_code_credit_interest_value);
}

}  // namespace s21
