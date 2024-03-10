#include "Validator.h"

namespace s21::expression {
using Data = data_structs::Data;
using DataStack = std::stack<Data>;
using TokenStatus = data_structs::TokenStatus;

bool Validator::IsTwoOperatorsInARow(const Data &current_token,
                                     const Data &previous_token) {
  bool flag = (current_token.data_type_ == data_types::DataType::kOperator &&
               previous_token.data_type_ == data_types::DataType::kOperator);
  return flag;
}

bool Validator::IsEmptyParenthesis(const Data &current_token,
                                   const Data &previous_token) {
  bool flag = (current_token.parentheses_type_ ==
                   data_types::ParenthesesType::kOpened &&
               previous_token.parentheses_type_ ==
                   data_types::ParenthesesType::kClosed);
  return flag;
}
bool Validator::IsConstant(const Data &current_token) {
  bool flag = (current_token.data_type_ == data_types::DataType::kConstant);
  return flag;
}

int Validator::ValidateExpression(DataStack infix_notation) {
  int error_code = error_code::kNoError;

  Data previous_token{};

  while (!infix_notation.empty()) {
    Data current_token = infix_notation.top();
    infix_notation.pop();

    if (IsTwoOperatorsInARow(current_token, previous_token)) {
      error_code = error_code::kTwoOperatorsInARow;
    } else if (IsEmptyParenthesis(current_token, previous_token)) {
      error_code = error_code::kEmptyParenthesis;
    }

    previous_token = current_token;
  }
  return error_code;
}
}  // namespace s21::expression