#ifndef CPP3_SMART_CALC_V_2_0_1_CONTROLLER_CONTROLLER_H_
#define CPP3_SMART_CALC_V_2_0_1_CONTROLLER_CONTROLLER_H_

#include "../Model/Model.h"

namespace s21 {
class Controller {
  using CreditParameters = credit::data_structs::Parameters;
  using CreditResult = credit::data_structs::Result;
  using DepositParameters = deposit::Parameters;
  using DepositResult = deposit::Result;

 public:
  explicit Controller(Model *model);

  ~Controller();

  int ExpressionCalculate(const std::string &string);

  void ExpressionSetVariable(const double &value);

  [[nodiscard]] double ExpressionGetResult() const;

  [[maybe_unused]] [[nodiscard]] double ExpressionGetVariable() const;

  int CreditCalculate(CreditParameters parameters);

  [[nodiscard]] CreditResult CreditGetResult() const;

  int DepositCalculate(const DepositParameters &parameters);

  [[nodiscard]] DepositResult DepositGetResult() const;

 private:
  Model *model_{};
};

}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_CONTROLLER_CONTROLLER_H_
