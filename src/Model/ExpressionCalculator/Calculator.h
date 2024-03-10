#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATOR_H_

#include "Calculation/Calculation.h"
#include "ExpressionTokenizer/ExpressionTokenizer.h"
#include "ExpressionTokenizer/Validator.h"
#include "ShuntingYard/ShuntingYard.h"

namespace s21::expression {
class Calculator {
 public:
  int Calculate(const std::string &string);

  [[nodiscard]] double GetResult() const;

  void SetVariableValue(const double &value);

  [[nodiscard]] double GetVariableValue();

 private:
  ExpressionTokenizer expression_tokenizer_{};
  ShuntingYard shunting_yard_{};
  Calculation calculator_{};
};

}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATOR_H_
