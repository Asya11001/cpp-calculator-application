#include "ExpressionTokenizer.h"

#include <set>

namespace s21::expression {
using Data = data_structs::Data;
using DataStack = std::stack<Data>;
using TokenStatus = data_structs::TokenStatus;

ExpressionTokenizer::ExpressionTokenizer() = default;

ExpressionTokenizer::~ExpressionTokenizer() = default;

std::pair<std::string, std::string> ExpressionTokenizer::SplitExponentialString(
    const std::string &str) {
  std::size_t pos = str.find('e');
  if (pos == std::string::npos) {
    return std::make_pair(str, "");
  }

  std::string before_e = str.substr(0, pos);
  std::string after_e = str.substr(pos + 1);

  return std::make_pair(before_e, after_e);
}

int ExpressionTokenizer::HandleNumber(const std::string &token,
                                      TokenStatus &token_status) {
  int error_code = error_code::kNoError;

  if (!token.empty()) {
    error_code = IsExponentPartsFine(token);
    if (error_code) {
      return error_code;
    }
    data_structs::Data data{};
    data.data_type_ = data_types::DataType::kValue;
    double temp_value = stod(token, nullptr);
    utility::rounding::RoundValue(temp_value, constants::kRoundValue);
    data.value_ = temp_value;
    PushShell(data, token_status);
  }
  return 0;
}

int ExpressionTokenizer::IsExponentPartsFine(const std::string &token) {
  int error_code = error_code::kNoError;
  auto pair = SplitExponentialString(token);
  if (pair.first.length() >= constants::kMaxNumberLength) {
    error_code = error_code::kNumberIsTooLong;
  } else if (pair.second.length() >= constants::kMaxNumberLength) {
    error_code = error_code::kNumberIsTooLong;
  } else if (pair.first.empty()) {
    error_code = error_code::kNumberIsEmpty;
  }
  if (!pair.second.empty()) {
    double exp = std::stod(pair.second);
    if (fabs(exp) > constants::kMaxExponentValue) {
      error_code = error_code::kExponentIsTooGreat;
    }
  }
  return error_code;
}

int ExpressionTokenizer::HandleFunction(const std::string &token,
                                        TokenStatus &token_status) {
  int error_code = error_code::kNoError;
  Data data{};

  auto it = constants::kFunctionTypeMap.find(token);

  if (it != constants::kFunctionTypeMap.end()) {
    data.data_type_ = data_types::DataType::kFunction;
    data.function_type_ = it->second;
    PushShell(data, token_status);
  } else {
    error_code = error_code::kUnknownFunction;
  }
  return error_code;
}

int ExpressionTokenizer::HandleConstants(const std::string &token,
                                         TokenStatus &token_status) {
  int error_code = error_code::kNoError;
  Data data{};

  auto it = constants::kConstantTypeMap.find(token);

  if (it != constants::kConstantTypeMap.end()) {
    data.data_type_ = data_types::DataType::kConstant;
    data.constant_type_ = it->second;
    PushShell(data, token_status);
  } else {
    error_code = error_code::kUnknownConstant;
  }
  return error_code;
}

int ExpressionTokenizer::HandleOperator(const std::string &token,
                                        TokenStatus &token_status) {
  int error_code = error_code::kNoError;
  Data data{};

  auto it = constants::kOperatorTypeMap.find(token);

  if (it != constants::kOperatorTypeMap.end()) {
    data.data_type_ = data_types::DataType::kOperator;
    data.operator_type_ = it->second;
    PushShell(data, token_status);
  } else {
    error_code = error_code::kUnknownOperator;
  }
  return error_code;
}

int ExpressionTokenizer::HandleParentheses(const std::string &token,
                                           TokenStatus &token_status) {
  int error_code = error_code::kNoError;
  Data data{};

  auto it = constants::kParenthesesTypeMap.find(token);

  if (it != constants::kParenthesesTypeMap.end()) {
    data.data_type_ = data_types::DataType::kParentheses;
    data.parentheses_type_ = it->second;
    PushShell(data, token_status);
  } else {
    error_code = error_code::kUnknownParentheses;
  }
  return error_code;
}

int ExpressionTokenizer::FromConstantToValue(Data &data) {
  int error_code = error_code::kNoError;
  if (data.data_type_ == data_types::DataType::kConstant) {
    auto it = constants::kConstantsToValuesMap.find(data.constant_type_);

    if (it != constants::kConstantsToValuesMap.end()) {
      data.value_ = it->second;
      data.data_type_ = data_types::DataType::kValue;
      data.constant_type_ = data_types::ConstantType::kNone;
    } else {
      data.data_type_ = data_types::DataType::kNone;
      error_code = error_code::kUnknownConstant;
    }
  }
  return error_code;
}

void ExpressionTokenizer::HandleVariable(TokenStatus &token_status) {
  Data data{};
  data.data_type_ = data_types::DataType::kVariable;
  PushShell(data, token_status);
}

data_types::OperatorType ExpressionTokenizer::FromBinaryToUnaryCode(
    data_types::OperatorType operator_code) {
  data_types::OperatorType unary_code = data_types::OperatorType::kNone;

  if (operator_code == data_types::OperatorType::kAddition) {
    unary_code = data_types::OperatorType::kUnaryPlus;
  }
  if (operator_code == data_types::OperatorType::kSubtraction) {
    unary_code = data_types::OperatorType::kUnaryMinus;
  }

  return unary_code;
}

void ExpressionTokenizer::HandleUnaryOperatorsAfterOpenParentheses() {
  if (stack_.size() >= 2) {
    data_structs::Data binary_operator = stack_.top();
    stack_.pop();

    data_structs::Data parentheses = stack_.top();
    stack_.pop();

    binary_operator.operator_type_ =
        FromBinaryToUnaryCode(binary_operator.operator_type_);

    stack_.push(parentheses);
    stack_.push(binary_operator);
  }
}

void ExpressionTokenizer::HandleUnaryOperatorsStartExpression() {
  if (!stack_.empty()) {
    data_structs::Data binaryOperator = stack_.top();
    stack_.pop();

    binaryOperator.operator_type_ =
        FromBinaryToUnaryCode(binaryOperator.operator_type_);

    stack_.push(binaryOperator);
  }
}

void ExpressionTokenizer::PushShell(Data data, TokenStatus &token_status) {
  stack_.push(data);

  token_status.last_token_ = token_status.current_token_;
  token_status.current_token_ = data;

  TokenizeImplicitOperators(token_status);
}

void ExpressionTokenizer::TokenizeImplicitOperators(
    const TokenStatus &token_status) {
  const Data &current_token = token_status.current_token_;
  const Data &last_token = token_status.last_token_;

  if (IsUnaryOperatorAfterOpenParentheses(last_token, current_token)) {
    HandleUnaryOperatorsAfterOpenParentheses();
  } else if (IsUnaryOperatorStartExpression(last_token, current_token)) {
    HandleUnaryOperatorsStartExpression();
  } else if (IsImplicitMultiplication(last_token, current_token)) {
    PlaceMultiplicationBetweenTokens();
  }
}

void ExpressionTokenizer::PlaceMultiplicationBetweenTokens() {
  if (stack_.size() >= 2) {
    Data data{};
    data.data_type_ = data_types::DataType::kOperator;
    data.operator_type_ = OperatorType::kMultiplication;

    data_structs::Data first_token = stack_.top();
    stack_.pop();

    data_structs::Data second_token = stack_.top();
    stack_.pop();

    stack_.push(second_token);
    stack_.push(data);
    stack_.push(first_token);
  }
}

int ExpressionTokenizer::IsUnaryOperatorAfterOpenParentheses(
    const Data &last_token, const Data &current_token) {
  bool flag =
      (last_token.parentheses_type_ == data_types::ParenthesesType::kOpened &&
       (current_token.operator_type_ == data_types::OperatorType::kAddition ||
        current_token.operator_type_ ==
            data_types::OperatorType::kSubtraction));
  return flag;
}

int ExpressionTokenizer::IsImplicitMultiplication(const Data &last_token,
                                                  const Data &current_token) {
  bool is_start_of_expression =
      last_token.data_type_ == data_types::DataType::kNone ||
      current_token.data_type_ == data_types::DataType::kNone;
  if (is_start_of_expression) {
    return false;
  }

  auto combination =
      std::make_pair(last_token.data_type_, current_token.data_type_);
  auto it = constants::kImplicitMultiplicationMap.find(combination);
  if (it != constants::kImplicitMultiplicationMap.end()) {
    return it->second;
  }

  return false;
}

int ExpressionTokenizer::IsUnaryOperatorStartExpression(
    const Data &last_token, const Data &current_token) {
  bool flag =
      (last_token.data_type_ == data_types::DataType::kNone &&
       (current_token.operator_type_ == data_types::OperatorType::kAddition ||
        current_token.operator_type_ ==
            data_types::OperatorType::kSubtraction));
  return flag;
}

bool ExpressionTokenizer::IsScientificNotation(const std::string &token) {
  return std::regex_match(token, constants::kScientificNumberRegex);
}

bool ExpressionTokenizer::IsOperator(const std::string &token) {
  return std::regex_match(token, constants::kOperatorRegex);
}

bool ExpressionTokenizer::IsParentheses(const std::string &token) {
  return std::regex_match(token, constants::kParenthesesRegex);
}

bool ExpressionTokenizer::IsFunction(const std::string &token) {
  for (const auto &item : constants::kNotFunction) {
    if (token == item) {
      return false;
    }
  }
  return std::regex_match(token, constants::kFunctionRegex);
}

bool ExpressionTokenizer::IsConstant(const std::string &token) {
  return constants::kConstantTokens.count(token) > 0;
}

bool ExpressionTokenizer::IsVariable(const std::string &token) {
  return constants::kVariableTokens.count(token) > 0;
}

bool ExpressionTokenizer::IsConsistingOfXChars(const std::string &str, char x) {
  return std::all_of(str.begin(), str.end(), [x](char c) { return c == x; });
}

void ExpressionTokenizer::HandleMultipleVariablesInARow(
    const std::string &token, std::vector<std::string> &tokens) {
  for (char ch : token) {
    std::string string{ch};
    tokens.push_back(string);
  }
}

std::vector<std::string> ExpressionTokenizer::Tokenize(
    const std::string &input) {
  std::vector<std::string> tokens{};
  auto words_begin =
      std::sregex_iterator(input.begin(), input.end(), constants::kTokenRegex);
  auto words_end = std::sregex_iterator();

  for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
    const std::smatch &match = *it;
    if (IsConsistingOfXChars(match.str(), 'x')) {
      HandleMultipleVariablesInARow(match.str(), tokens);
    } else {
      tokens.push_back(match.str());
    }
  }
  return tokens;
}

int ExpressionTokenizer::TokenizeExpression() {
  int error_code = error_code::kNoError;
  data_structs::TokenStatus token_status{};

  auto token_vector = Tokenize(expression_);
  for (const auto &token : token_vector) {
    if (IsScientificNotation(token)) {
      error_code = HandleNumber(token, token_status);
    } else if (IsOperator(token)) {
      HandleOperator(token, token_status);
    } else if (IsParentheses(token)) {
      HandleParentheses(token, token_status);
    } else if (IsFunction(token)) {
      error_code = HandleFunction(token, token_status);
    } else if (IsConstant(token)) {
      error_code = HandleConstants(token, token_status);
    } else if (IsVariable(token)) {
      HandleVariable(token_status);
    } else {
      error_code = error_code::kUnknownToken;
    }
    if (error_code) {
      return error_code;
    }
  }
  return error_code;
}

int ExpressionTokenizer::FromExpressionToInfixNotation() {
  int error_code = error_code::kNoError;
  error_code = TokenizeExpression();
  if (!error_code) {
    HandleConstantsInStack();
  }
  return error_code;
}

void ExpressionTokenizer::HandleConstantsInStack() {
  std::vector<Data> temp_vector;

  while (!stack_.empty()) {
    temp_vector.push_back(stack_.top());
    stack_.pop();
  }

  for (Data &elem : temp_vector) {
    FromConstantToValue(elem);
  }

  for (auto it = temp_vector.rbegin(); it != temp_vector.rend(); ++it) {
    stack_.push(*it);
  }
}

void ExpressionTokenizer::SetExpression(const std::string &string) {
  expression_ = string;
}

void ExpressionTokenizer::SetStack(const DataStack &stack) { stack_ = stack; }

std::string ExpressionTokenizer::GetExpression() { return expression_; }

DataStack ExpressionTokenizer::GetStack() { return stack_; }

void ExpressionTokenizer::ClearMembers() {
  expression_.clear();
  while (!stack_.empty()) {
    stack_.pop();
  }
}

}  // namespace s21::expression