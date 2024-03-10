#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_MODEL_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_MODEL_H_

#include "CreditCalculator/Calculator.h"
#include "DepositCalculator/Calculator.h"
#include "ExpressionCalculator/Calculator.h"

namespace s21 {
class Model {
  using CreditParameters = credit::data_structs::Parameters;
  using CreditResult = credit::data_structs::Result;
  using DepositParameters = deposit::Parameters;
  using DepositResult = deposit::Result;

 public:
  Model();
  ~Model();

  int ExpressionCalculate(const std::string &string);

  void ExpressionSetVariable(const double &value);

  [[nodiscard]] double ExpressionGetResult() const;

  [[nodiscard]] double ExpressionGetVariable();

  int CreditCalculate(const CreditParameters &parameters);

  [[nodiscard]] CreditResult CreditGetResult() const;

  int DepositCalculate(const DepositParameters &parameters);

  [[nodiscard]] DepositResult DepositGetResult() const;

 private:
  expression::Calculator expression_calculator_{};
  credit::Calculator credit_calculator_{};
  deposit::Calculator deposit_calculator_{};
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_MODEL_H_
