#include "Controller.h"

namespace s21 {
using CreditParameters = credit::data_structs::Parameters;
using CreditResult = credit::data_structs::Result;
using DepositParameters = deposit::Parameters;
using DepositResult = deposit::Result;

Controller::Controller(Model *model) : model_(model){};

Controller::~Controller() = default;

int Controller::ExpressionCalculate(const std::string &string) {
  int error_code = model_->ExpressionCalculate(string);
  return error_code;
}

void Controller::ExpressionSetVariable(const double &value) {
  model_->ExpressionSetVariable(value);
}

[[nodiscard]] double Controller::ExpressionGetResult() const {
  return model_->ExpressionGetResult();
}

[[maybe_unused]] [[nodiscard]] double Controller::ExpressionGetVariable()
    const {
  return model_->ExpressionGetVariable();
}

int Controller::CreditCalculate(CreditParameters parameters) {
  int error_code = model_->CreditCalculate(parameters);
  return error_code;
}

[[nodiscard]] CreditResult Controller::CreditGetResult() const {
  return model_->CreditGetResult();
}

int Controller::DepositCalculate(const DepositParameters &parameters) {
  int error_code = model_->DepositCalculate(parameters);
  return error_code;
}

[[nodiscard]] DepositResult Controller::DepositGetResult() const {
  return model_->DepositGetResult();
}
}  // namespace s21
