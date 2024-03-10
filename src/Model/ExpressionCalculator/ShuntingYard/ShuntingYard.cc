#include "ShuntingYard.h"

namespace s21::expression {
using Data = data_structs::Data;
using DataStack = std::stack<Data>;

ShuntingYard::ShuntingYard() = default;

ShuntingYard::~ShuntingYard() = default;

bool ShuntingYard::IsUnaryOperator(const data_structs::Data &token) {
  bool flag = (token.operator_type_ == data_types::OperatorType::kUnaryMinus ||
               token.operator_type_ == data_types::OperatorType::kUnaryPlus);
  return flag;
}

bool ShuntingYard::IsPower(const data_structs::Data &token) {
  bool flag = (token.operator_type_ == data_types::OperatorType::kPower);
  return flag;
}

bool ShuntingYard::IsMultiplicationOrDivisionOrModulus(
    const data_structs::Data &token) {
  bool flag =
      (token.operator_type_ == data_types::OperatorType::kMultiplication ||
       token.operator_type_ == data_types::OperatorType::kDivision ||
       token.operator_type_ == data_types::OperatorType::kModulus);
  return flag;
}

bool ShuntingYard::IsFunction(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kFunction);
  return flag;
}

bool ShuntingYard::IsAdditionOrSubtraction(const data_structs::Data &token) {
  bool flag = (token.operator_type_ == data_types::OperatorType::kAddition ||
               token.operator_type_ == data_types::OperatorType::kSubtraction);
  return flag;
}

bool ShuntingYard::IsOperatorOrFunction(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kOperator ||
               token.data_type_ == data_types::DataType::kFunction);
  return flag;
}

bool ShuntingYard::IsValueOrVariable(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kValue ||
               token.data_type_ == data_types::DataType::kVariable);
  return flag;
}

bool ShuntingYard::IsParentheses(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kParentheses);
  return flag;
}

bool ShuntingYard::IsOpenParentheses(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kParentheses &&
               token.parentheses_type_ == data_types::ParenthesesType::kOpened);
  return flag;
}

bool ShuntingYard::IsClosedParentheses(const data_structs::Data &token) {
  bool flag = (token.data_type_ == data_types::DataType::kParentheses &&
               token.parentheses_type_ == data_types::ParenthesesType::kClosed);
  return flag;
}

data_types::PrecedenceLevel ShuntingYard::GetOperatorPrecedence(
    const data_structs::Data &token) {
  data_types::PrecedenceLevel precedence_level =
      data_types::PrecedenceLevel::k0;

  if (IsFunction(token) || IsUnaryOperator(token)) {
    precedence_level = data_types::PrecedenceLevel::k4;
  } else if (IsPower(token)) {
    precedence_level = data_types::PrecedenceLevel::k3;
  } else if (IsMultiplicationOrDivisionOrModulus(token)) {
    precedence_level = data_types::PrecedenceLevel::k2;
  } else if (IsAdditionOrSubtraction(token)) {
    precedence_level = data_types::PrecedenceLevel::k1;
  }
  return precedence_level;
}

void ShuntingYard::HandleBinaryOperatorOrFunction(
    DataStack &operator_stack, const data_structs::Data &token) {
  bool stop_cycle_flag{false};

  while (!operator_stack.empty() && !stop_cycle_flag) {
    data_structs::Data top_token = operator_stack.top();
    operator_stack.pop();

    if (IsOpenParentheses(top_token)) {
      operator_stack.push(top_token);
      stop_cycle_flag = true;
    } else {
      data_types::PrecedenceLevel precedence_1 = GetOperatorPrecedence(token);
      data_types::PrecedenceLevel precedence_2 =
          GetOperatorPrecedence(top_token);

      if (precedence_1 > precedence_2) {
        operator_stack.push(top_token);
        stop_cycle_flag = true;
      } else {
        postfix_stack_.push(top_token);
      };
    }
  }
  operator_stack.push(token);
}

void ShuntingYard::HandleUnaryOperatorOrFunction(
    DataStack &operator_stack, const data_structs::Data &token) {
  operator_stack.push(token);
}

void ShuntingYard::HandleBinaryAndUnaryOperators(
    data_types::LastToken &last_token, data_structs::Data token,
    DataStack &operator_stack) {
  if (last_token == data_types::LastToken::kOperandOrFunction) {
    HandleBinaryOperatorOrFunction(operator_stack, token);
  } else {
    HandleUnaryOperatorOrFunction(operator_stack, token);
  }
}

void ShuntingYard::HandleOpenParentheses(const data_structs::Data &token,
                                         DataStack &operator_stack) {
  operator_stack.push(token);
}

int ShuntingYard::HandleCloseParentheses(DataStack &operator_stack) {
  int error_code = error_code::kNoError;
  bool flag_found_open_parentheses{false};

  while (!operator_stack.empty() && !flag_found_open_parentheses) {
    data_structs::Data token = operator_stack.top();
    operator_stack.pop();

    if (IsOpenParentheses(token)) {
      flag_found_open_parentheses = true;
    } else {
      postfix_stack_.push(token);
    }
  }
  if (!flag_found_open_parentheses) {
    error_code = error_code::kMismatchedParenthesis;
  }
  return error_code;
}

int ShuntingYard::HandleParentheses(data_types::LastToken &last_token,
                                    const data_structs::Data &token,
                                    DataStack &operator_stack) {
  int error_code = error_code::kNoError;

  if (IsOpenParentheses(token)) {
    HandleOpenParentheses(token, operator_stack);
    last_token = data_types::LastToken::kNone;
  } else if (IsClosedParentheses(token)) {
    error_code = HandleCloseParentheses(operator_stack);
    last_token = data_types::LastToken::kOperandOrFunction;
  }
  return error_code;
}

void ShuntingYard::HandleEndOfExpression(DataStack &operator_stack,
                                         int &error_code) {
  while (!operator_stack.empty() && !error_code) {
    data_structs::Data token = operator_stack.top();
    operator_stack.pop();

    if (token.data_type_ == data_types::DataType::kParentheses) {
      error_code = error_code::kMismatchedParenthesis;
    } else {
      postfix_stack_.push(token);
    }
  }
}

int ShuntingYard::FromInfixToPostfix() {
  StackManipulation::ReverseStack(infix_stack_);

  int error_code = error_code::kNoError;
  DataStack operator_stack;
  data_types::LastToken last_token = data_types::LastToken::kNone;

  while (!infix_stack_.empty() && !error_code) {
    data_structs::Data token = infix_stack_.top();
    infix_stack_.pop();

    if (IsValueOrVariable(token)) {
      postfix_stack_.push(token);
      last_token = data_types::LastToken::kOperandOrFunction;
    } else if (IsOperatorOrFunction(token)) {
      HandleBinaryAndUnaryOperators(last_token, token, operator_stack);
    } else if (IsParentheses(token)) {
      error_code = HandleParentheses(last_token, token, operator_stack);
    }
  }
  HandleEndOfExpression(operator_stack, error_code);
  return error_code;
}

void ShuntingYard::SetInfixStack(const DataStack &stack) {
  infix_stack_ = stack;
}

[[nodiscard]] DataStack ShuntingYard::GetPostfixStack() {
  return postfix_stack_;
}

void ShuntingYard::ClearMembers() {
  while (!infix_stack_.empty()) {
    infix_stack_.pop();
  }
  while (!postfix_stack_.empty()) {
    postfix_stack_.pop();
  }
}

}  // namespace s21::expression
