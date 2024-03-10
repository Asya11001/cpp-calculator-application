#include "Model.h"

namespace s21 {

using CreditParameters = credit::data_structs::Parameters;
using CreditResult = credit::data_structs::Result;
using DepositParameters = deposit::Parameters;
using DepositResult = deposit::Result;

Model::Model() = default;

Model::~Model() = default;

int Model::ExpressionCalculate(const std::string &string) {
  int error_code{expression::error_code::kNoError};
  error_code = expression_calculator_.Calculate(string);
  return error_code;
}

void Model::ExpressionSetVariable(const double &value) {
  expression_calculator_.SetVariableValue(value);
}

[[nodiscard]] double Model::ExpressionGetResult() const {
  return expression_calculator_.GetResult();
}

[[nodiscard]] double Model::ExpressionGetVariable() {
  return expression_calculator_.GetVariableValue();
}

int Model::CreditCalculate(const CreditParameters &parameters) {
  credit_calculator_.SetParameters(parameters);
  int error_code = credit_calculator_.Calculate();
  return error_code;
}

[[nodiscard]] CreditResult Model::CreditGetResult() const {
  return credit_calculator_.GetResult();
}

int Model::DepositCalculate(const DepositParameters &parameters) {
  int error_code{expression::error_code::kNoError};
  deposit_calculator_.SetParameters(parameters);
  error_code = deposit_calculator_.Calculate();
  return error_code;
}

[[nodiscard]] DepositResult Model::DepositGetResult() const {
  return deposit_calculator_.GetResult();
}
}  // namespace s21
