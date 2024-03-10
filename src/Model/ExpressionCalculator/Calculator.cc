//
// Created by Evangelina Marj on 2/25/24.
//

#include "Calculator.h"

namespace s21::expression {

int Calculator::Calculate(const std::string &string) {
  std::stack<data_structs::Data> infix_stack{};
  std::stack<data_structs::Data> postfix_stack{};

  expression_tokenizer_.ClearMembers();
  shunting_yard_.ClearMembers();
  calculator_.ClearMembers();

  expression_tokenizer_.SetExpression(string);
  int error_code = expression_tokenizer_.FromExpressionToInfixNotation();
  if (!error_code) {
    infix_stack = expression_tokenizer_.GetStack();
    error_code = Validator::ValidateExpression(infix_stack);
  }
  if (!error_code) {
    shunting_yard_.SetInfixStack(infix_stack);
    error_code = shunting_yard_.FromInfixToPostfix();
  }
  if (!error_code) {
    postfix_stack = shunting_yard_.GetPostfixStack();

    calculator_.SetPostfixStack(postfix_stack);
    error_code = calculator_.CalculateExpression();
  }

  return error_code;
}

[[nodiscard]] double Calculator::GetResult() const {
  return calculator_.GetResult();
}

void Calculator::SetVariableValue(const double &value) {
  calculator_.SetVariableValue(value);
}

[[nodiscard]] double Calculator::GetVariableValue() {
  return calculator_.GetVariableValue();
}

}  // namespace s21::expression