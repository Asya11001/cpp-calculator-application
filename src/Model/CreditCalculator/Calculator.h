#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_CALCULATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_CALCULATOR_H_

#include <cmath>
#include <vector>

#include "../utility.h"
#include "common/constants.h"
#include "common/data_structs.h"
#include "common/data_types.h"
#include "common/error_code.h"

namespace s21::credit {
class Calculator {
  using VectorType = std::vector<double>;
  using Parameters = data_structs::Parameters;
  using Result = data_structs::Result;

 public:
  Calculator();

  ~Calculator();

  [[nodiscard]] bool IsValidAmountValue() const;

  [[nodiscard]] bool IsValidInterestRate() const;

  [[nodiscard]] bool IsValidDeadline() const;

  [[nodiscard]] int ValidateParameters() const;

  int NormalizeParameters();

  [[nodiscard]] double GetMonthlyInterestRate() const;

  [[nodiscard]] static double GetBaseForMonthlyPayment(
      double monthly_interest_rate, int number_of_payments);

  [[nodiscard]] double CalculateMonthlyPaymentAnnual(
      double monthly_interest_rate, const double &base) const;

  [[nodiscard]] double GetMonthlyInterestPayment(double remaining_credit) const;

  double CalculateTotalPayment(VectorType &monthly_payments) const;

  [[nodiscard]] bool IsAnnual() const;

  [[nodiscard]] bool IsDifferential() const;

  [[nodiscard]] double GetMonthlyPaymentDifferential() const;

  void CalculateMonthlyPaymentsDifferential(VectorType &monthly_payments) const;

  void CalculateMonthlyPayments();

  int Calculate();

  void SetParameters(Parameters parameters);

  [[nodiscard]] Result GetResult() const;

 private:
  Parameters parameters_{};
  Result result_{};
};
}  // namespace s21::credit

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_CALCULATOR_H_
