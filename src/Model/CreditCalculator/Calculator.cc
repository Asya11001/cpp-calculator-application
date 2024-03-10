
#include "Calculator.h"

namespace s21::credit {
using VectorType = std::vector<double>;
using Parameters = data_structs::Parameters;
using Result = data_structs::Result;

Calculator::Calculator() = default;

Calculator::~Calculator() = default;

[[nodiscard]] bool Calculator::IsValidAmountValue() const {
  bool flag = (parameters_.amount_ > constants::kMinAmount ||
               parameters_.amount_ < constants::kMaxAmount);
  return flag;
}

[[nodiscard]] bool Calculator::IsValidInterestRate() const {
  bool flag = (parameters_.amount_ > constants::kMinInterestRate ||
               parameters_.amount_ < constants::kMaxInterestRate);
  return flag;
};

[[nodiscard]] bool Calculator::IsValidDeadline() const {
  bool flag = parameters_.deadline_ <= constants::kMaxDurationInMonths;
  return flag;
}

[[nodiscard]] int Calculator::ValidateParameters() const {
  int error_code = error_code::kNoError;

  if (!IsValidAmountValue()) {
    error_code = error_code::kInvalidCreditAmount;
  }
  if (!IsValidInterestRate()) {
    error_code |= error_code::kInvalidInterestRate;
  }
  return error_code;
}

int Calculator::NormalizeParameters() {
  int error_code = error_code::kNoError;
  error_code = ValidateParameters();
  if (parameters_.term_type_ == data_types::TermType::kYears && !error_code) {
    parameters_.deadline_ *= constants::kMonthsInYear;
    parameters_.term_type_ = data_types::TermType::kMonths;
  }
  if (!IsValidDeadline()) {
    error_code |= error_code::kInvalidDeadline;
  }
  if (!error_code) {
    parameters_.interest_rate_ /= 100;
  }
  return error_code;
}

[[nodiscard]] double Calculator::GetMonthlyInterestRate() const {
  double result{(parameters_.interest_rate_ / constants::kMonthsInYear)};
  return result;
}

[[nodiscard]] double Calculator::GetBaseForMonthlyPayment(
    double monthly_interest_rate, int number_of_payments) {
  double result{};
  result = (pow(1 + monthly_interest_rate, number_of_payments));
  return result;
}

[[nodiscard]] double Calculator::CalculateMonthlyPaymentAnnual(
    double monthly_interest_rate, const double &base) const {
  double result{};
  result = ((parameters_.amount_ * monthly_interest_rate * base) / (base - 1));
  return result;
}

[[nodiscard]] double Calculator::GetMonthlyInterestPayment(
    double remaining_credit) const {
  double result{};
  result = remaining_credit *
           (parameters_.interest_rate_ / constants::kMonthsInYear);
  return result;
}

double Calculator::CalculateTotalPayment(VectorType &monthly_payments) const {
  double total_payment{0};
  for (int month_index = 0; month_index < parameters_.deadline_;
       ++month_index) {
    total_payment += monthly_payments[month_index];
  }
  return total_payment;
}

[[nodiscard]] bool Calculator::IsAnnual() const {
  bool flag{};
  flag = parameters_.payment_type_ == data_types::PaymentType::kAnnual;
  return flag;
}

[[nodiscard]] bool Calculator::IsDifferential() const {
  bool flag{};
  flag = parameters_.payment_type_ == data_types::PaymentType::kDifferential;
  return flag;
}

[[nodiscard]] double Calculator::GetMonthlyPaymentDifferential() const {
  double result{};
  result = (parameters_.amount_ / parameters_.deadline_);
  return result;
}

void Calculator::CalculateMonthlyPaymentsDifferential(
    VectorType &monthly_payments) const {
  double monthly_principal_payment = GetMonthlyPaymentDifferential();

  double remaining_credit = parameters_.amount_;

  for (int month_index = 0; month_index < parameters_.deadline_;
       ++month_index) {
    double monthly_interest_payment =
        GetMonthlyInterestPayment(remaining_credit);
    double payment = monthly_principal_payment + monthly_interest_payment;
    monthly_payments.insert(monthly_payments.end(), payment);
    remaining_credit -= monthly_principal_payment;
  }
}

void Calculator::CalculateMonthlyPayments() {
  double monthly_interest_rate = GetMonthlyInterestRate();

  int number_of_payments{parameters_.deadline_};

  VectorType monthly_payments{};
  monthly_payments.reserve(number_of_payments);

  if (IsAnnual()) {
    double base =
        GetBaseForMonthlyPayment(monthly_interest_rate, number_of_payments);
    result_.monthly_payment_begin_ =
        CalculateMonthlyPaymentAnnual(monthly_interest_rate, base);
    result_.monthly_payments_end_ = result_.monthly_payment_begin_;

    for (int month_index = 0; month_index < number_of_payments; ++month_index) {
      monthly_payments[month_index] = result_.monthly_payment_begin_;
    }
  } else if (IsDifferential()) {
    CalculateMonthlyPaymentsDifferential(monthly_payments);
    result_.monthly_payment_begin_ = *monthly_payments.begin();
    result_.monthly_payments_end_ = *(--monthly_payments.end());
  }

  result_.total_payment_ = CalculateTotalPayment(monthly_payments);
  result_.overpayment_ = result_.total_payment_ - parameters_.amount_;
  utility::rounding::RoundValue(result_.total_payment_, constants::kRoundValue);
  utility::rounding::RoundValue(result_.overpayment_, constants::kRoundValue);
  utility::rounding::RoundValue(result_.monthly_payment_begin_,
                                constants::kRoundValue);
  utility::rounding::RoundValue(result_.monthly_payments_end_,
                                constants::kRoundValue);
}

int Calculator::Calculate() {
  int error_code = error_code::kNoError;

  error_code = NormalizeParameters();

  if (!error_code) {
    CalculateMonthlyPayments();
  }
  return error_code;
}

void Calculator::SetParameters(Parameters parameters) {
  parameters_ = parameters;
}

[[nodiscard]] Result Calculator::GetResult() const { return result_; }
}  // namespace s21::credit
