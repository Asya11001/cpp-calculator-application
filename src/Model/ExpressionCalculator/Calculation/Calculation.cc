#include "Calculation.h"

namespace s21::expression {

using Data = data_structs::Data;
using DataStack = std::stack<Data>;

Calculation::Calculation() = default;

void Calculation::HandleVariable(data_structs::Data &token, double value) {
  if (token.data_type_ == data_types::DataType::kVariable) {
    token.data_type_ = data_types::DataType::kValue;
    token.value_ = value;
  }
}

int Calculation::PerformOperatorCalculations(const Data &token,
                                             const Data &operand_1,
                                             const Data &operand_2,
                                             double &result) {
  int error_code = error_code::kNoError;
  bool flag_incorrect_input =
      (operand_1.data_type_ == data_types::DataType::kNone ||
       operand_2.data_type_ == data_types::DataType::kNone);

  if (flag_incorrect_input) {
    error_code = error_code::kInvalidExpressionFormat;
  } else if (token.operator_type_ == data_types::OperatorType::kAddition) {
    CalculationHandler::CalculateAddition(operand_1, operand_2, result);
  } else if (token.operator_type_ == data_types::OperatorType::kSubtraction) {
    CalculationHandler::CalculateSubtraction(operand_1, operand_2, result);
  } else if (token.operator_type_ ==
             data_types::OperatorType::kMultiplication) {
    CalculationHandler::CalculateMultiplication(operand_1, operand_2, result);
  } else if (token.operator_type_ == data_types::OperatorType::kPower) {
    error_code =
        CalculationHandler::CalculatePower(operand_1, operand_2, result);
  } else if (token.operator_type_ == data_types::OperatorType::kDivision) {
    error_code =
        CalculationHandler::CalculateDivision(operand_1, operand_2, result);
  } else if (token.operator_type_ == data_types::OperatorType::kModulus) {
    error_code =
        CalculationHandler::CalculateModulus(operand_1, operand_2, result);
  } else {
    error_code = error_code::kUnknownOperator;
  }
  return error_code;
}

int Calculation::PerformFunctionCalculations(const Data &token,
                                             const Data &operand,
                                             double &result) {
  int error_code = error_code::kNoError;

  bool is_sine = GetIsSine(token);
  bool is_cosine = GetIsCosine(token);
  bool is_tangent = GetIsTangent(token);

  if (is_sine) {
    CalculationHandler::CalculateSine(token, operand, result);
  } else if (is_cosine) {
    CalculationHandler::CalculateCosine(token, operand, result);
  } else if (is_tangent) {
    CalculationHandler::CalculateTangent(token, operand, result);
  } else if (token.function_type_ == data_types::FunctionType::kSquareRoot) {
    error_code = CalculationHandler::CalculationSquareRoot(operand, result);
  } else if (token.function_type_ == data_types::FunctionType::kArcSine) {
    error_code = CalculationHandler::CalculateArcSine(operand, result);
  } else if (token.function_type_ == data_types::FunctionType::kArcCosine) {
    error_code = CalculationHandler::CalculateArcCosine(operand, result);
  } else if (token.function_type_ == data_types::FunctionType::kArcTangent) {
    CalculationHandler::CalculateArcTangent(operand, result);
  } else if (token.function_type_ ==
             data_types::FunctionType::kNaturalLogarithm) {
    error_code = CalculationHandler::CalculateNaturalLogarithm(operand, result);
  } else if (token.function_type_ ==
             data_types::FunctionType::kCommonLogarithm) {
    error_code = CalculationHandler::CalculateCommonLogarithm(operand, result);
  } else {
    error_code = error_code::kUnknownFunction;
  }

  return error_code;
}

bool Calculation::GetIsTangent(const Data &token) {
  return (token.function_type_ == data_types::FunctionType::kTangent ||
          (token.function_type_ == data_types::FunctionType::kTangentRadian));
}

bool Calculation::GetIsCosine(const Data &token) {
  return (token.function_type_ == data_types::FunctionType::kCosine ||
          (token.function_type_ == data_types::FunctionType::kCosineRadian));
}

bool Calculation::GetIsSine(const Data &token) {
  return (token.function_type_ == data_types::FunctionType::kSine ||
          (token.function_type_ == data_types::FunctionType::kSineRadian));
}

void Calculation::HandlePushingResultValueInCalculationStack(
    DataStack &calculation_stack, double &result, int error_code) {
  if (!error_code) {
    Data result_data{};
    result_data.data_type_ = data_types::DataType::kValue;
    result_data.value_ = result;
    calculation_stack.push(result_data);
  }
}

int Calculation::HandleCalculationOperators(DataStack &calculation_stack,
                                            const Data &token) {
  int error_code = error_code::kNoError;

  if (calculation_stack.empty()) {
    error_code = error_code::kInsufficientOperandsForOperator;
  }
  double result{};

  if (!error_code) {
    Data operand_2 = calculation_stack.top();
    calculation_stack.pop();

    if (operand_2.data_type_ == data_types::DataType::kNone) {
      error_code = error_code::kInvalidExpressionFormat;
    } else if (!CalculationHandler::HandleUnaryOperator(token, operand_2,
                                                        result)) {
      if (!calculation_stack.empty()) {
        Data operand_1 = calculation_stack.top();
        calculation_stack.pop();
        error_code =
            PerformOperatorCalculations(token, operand_1, operand_2, result);
      } else {
        error_code = error_code::kInsufficientOperandsForOperator;
      }
    }
  }
  HandlePushingResultValueInCalculationStack(calculation_stack, result,
                                             error_code);
  return error_code;
}

int Calculation::HandleCalculationFunctions(DataStack &calculation_stack,
                                            Data &token) {
  int error_code = error_code::kNoError;
  if (calculation_stack.empty()) {
    error_code = error_code::kInsufficientOperandsForFunction;
  }

  double result{0};

  if (!error_code) {
    Data operand = calculation_stack.top();
    calculation_stack.pop();
    error_code = PerformFunctionCalculations(token, operand, result);
  }

  HandlePushingResultValueInCalculationStack(calculation_stack, result,
                                             error_code);

  return error_code;
}

int Calculation::HandleCalculationsOperatorsAndFunctions(
    DataStack &calculation_stack, Data &token) {
  int error_code = error_code::kNoError;

  if (token.data_type_ == data_types::DataType::kOperator) {
    error_code |= HandleCalculationOperators(calculation_stack, token);
  } else if (token.data_type_ == data_types::DataType::kFunction) {
    error_code = HandleCalculationFunctions(calculation_stack, token);
  }

  return error_code;
}

int Calculation::HandleFinalResultAssigning(DataStack &calculation_stack) {
  int error_code = error_code::kNoError;

  if (calculation_stack.size() != 1) {
    error_code = error_code::kInvalidExpressionFormat;
  } else {
    Data final_result = calculation_stack.top();
    calculation_stack.pop();

    if (final_result.data_type_ == data_types::DataType::kNone) {
      error_code = error_code::kInvalidExpressionFormat;
    }
    result_ = final_result.value_;
    if (std::isnan(result_))
      error_code = error_code::kResultCalculatedValueIsNan;
  }

  return error_code;
}

int Calculation::CalculateExpression() {
  int error_code = error_code::kNoError;
  StackManipulation::ReverseStack(postfix_stack_);
  DataStack calculation_stack{};

  while (!postfix_stack_.empty() && !error_code) {
    Data token = postfix_stack_.top();
    postfix_stack_.pop();

    bool is_token_number = GetIsTokenNumber(token);
    bool is_token_modifier = GetIsTokenModifier(token);

    if (token.data_type_ == data_types::DataType::kNone) {
      error_code = error_code::kInvalidExpressionFormat;
    } else if (is_token_number) {
      HandleVariable(token, variable_value_);
      calculation_stack.push(token);
    } else if (is_token_modifier) {
      error_code =
          HandleCalculationsOperatorsAndFunctions(calculation_stack, token);
    }
  }
  if (!error_code) {
    error_code = HandleFinalResultAssigning(calculation_stack);
  }
  return error_code;
}

bool Calculation::GetIsTokenModifier(const Data &token) {
  bool flag = token.data_type_ == data_types::DataType::kOperator ||
              token.data_type_ == data_types::DataType::kFunction;
  return flag;
}

bool Calculation::GetIsTokenNumber(const Data &token) {
  bool flag = token.data_type_ == data_types::DataType::kValue ||
              token.data_type_ == data_types::DataType::kVariable;
  return flag;
}

void Calculation::SetPostfixStack(const DataStack &stack) {
  postfix_stack_ = stack;
}

double Calculation::GetResult() const { return result_; }

void Calculation::SetVariableValue(const double &value) {
  variable_value_ = value;
}

[[nodiscard]] double Calculation::GetVariableValue() const {
  return variable_value_;
}

void Calculation::ClearMembers() {
  while (!postfix_stack_.empty()) {
    postfix_stack_.pop();
  }
  result_ = 0;
}

}  // namespace s21::expression