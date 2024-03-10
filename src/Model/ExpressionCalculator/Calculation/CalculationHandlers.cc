#include "CalculationHandler.h"

namespace s21::expression {
using Data = data_structs::Data;
using DataStack = std::stack<Data>;

double CalculationHandler::FromRadianToDegree(const double &radian_value) {
  double degree_value = (radian_value * M_PI) / 180;
  return degree_value;
}

bool CalculationHandler::IsValueFineForInverseTrigonometryFunctions(
    const Data &data) {
  bool flag = std::fabs(data.value_) <=
              constants::kBoundValueForInverseTrigonometryFunctions;
  return flag;
}

bool CalculationHandler::HandleUnaryOperator(const Data &token,
                                             const Data &operand,
                                             double &result) {
  bool is_unary_operator{true};

  if (token.operator_type_ == data_types::OperatorType::kUnaryMinus) {
    result = operand.value_ * (-1);
  } else if (token.operator_type_ == data_types::OperatorType::kUnaryPlus) {
    result = operand.value_;
  } else {
    is_unary_operator = false;
  }
  return is_unary_operator;
}

void CalculationHandler::CalculateAddition(const Data &operand_1,
                                           const Data &operand_2,
                                           double &result) {
  result = operand_1.value_ + operand_2.value_;
}

void CalculationHandler::CalculateSubtraction(const Data &operand_1,
                                              const Data &operand_2,
                                              double &result) {
  result = operand_1.value_ - operand_2.value_;
}

void CalculationHandler::CalculateMultiplication(const Data &operand_1,
                                                 const Data &operand_2,
                                                 double &result) {
  result = operand_1.value_ * operand_2.value_;
}

int CalculationHandler::CalculateDivision(const Data &operand_1,
                                          const Data &operand_2,
                                          double &result) {
  int error_code = error_code::kNoError;
  if (operand_2.value_ == 0) {
    error_code = error_code::kDivisionByZero;
  } else {
    result = operand_1.value_ / operand_2.value_;
  }
  return error_code;
}

int CalculationHandler::CalculatePower(const Data &operand_1,
                                       const Data &operand_2, double &result) {
  int error_code = error_code::kNoError;
  if (operand_2.value_ > constants::kMaxPowerValue) {
    error_code = error_code::kPowerValueIsTooBig;
  } else {
    result = std::pow(operand_1.value_, operand_2.value_);
  }
  return error_code;
}

int CalculationHandler::CalculateModulus(const Data &operand_1,
                                         const Data &operand_2,
                                         double &result) {
  int error_code = error_code::kNoError;
  if (operand_2.value_ == 0) {
    error_code = error_code::kModulusMyZero;
  } else {
    result = std::fmod(operand_1.value_, operand_2.value_);
  }
  return error_code;
}

int CalculationHandler::CalculateArcSine(const Data &operand, double &result) {
  int error_code = error_code::kNoError;

  if (IsValueFineForInverseTrigonometryFunctions(operand)) {
    result = std::asin(operand.value_);
  } else {
    error_code = error_code::kIndeterminateResultForArcSine;
  }

  return error_code;
}

int CalculationHandler::CalculateArcCosine(const Data &operand,
                                           double &result) {
  int error_code = error_code::kNoError;

  if (IsValueFineForInverseTrigonometryFunctions(operand)) {
    result = std::acos(operand.value_);
  } else {
    error_code = error_code::kIndeterminateResultForArcCosine;
  }

  return error_code;
}

void CalculationHandler::CalculateArcTangent(const Data &operand,
                                             double &result) {
  result = std::atan(operand.value_);
}

void CalculationHandler::CalculateSine(Data token, Data operand,
                                       double &result) {
  if (token.function_type_ == data_types::FunctionType::kSine) {
    operand.value_ = FromRadianToDegree(operand.value_);
  }
  result = std::sin(operand.value_);
}

void CalculationHandler::CalculateCosine(const Data &token, Data operand,
                                         double &result) {
  if (token.function_type_ == data_types::FunctionType::kCosine) {
    operand.value_ = FromRadianToDegree(operand.value_);
  }
  result = std::cos(operand.value_);
}

void CalculationHandler::CalculateTangent(const Data &token, Data operand,
                                          double &result) {
  if (token.function_type_ == data_types::FunctionType::kTangent) {
    operand.value_ = FromRadianToDegree(operand.value_);
  }
  result = std::tan(operand.value_);
}

int CalculationHandler::CalculationSquareRoot(const Data &operand,
                                              double &result) {
  int error_code = error_code::kNoError;

  if (operand.value_ < 0) {
    error_code = error_code::kSquareOfNegativeNumber;
  } else {
    result = std::sqrt(operand.value_);
  }
  return error_code;
}

int CalculationHandler::CalculateNaturalLogarithm(const Data &operand,
                                                  double &result) {
  int error_code = error_code::kNoError;

  if (operand.value_ <= 0) {
    error_code = error_code::kIncorrectValueForNaturalLogarithm;
  } else {
    result = std::log(operand.value_);
  }
  return error_code;
}

int CalculationHandler::CalculateCommonLogarithm(const Data &operand,
                                                 double &result) {
  int error_code = error_code::kNoError;

  if (operand.value_ <= 0) {
    error_code = error_code::kIncorrectValueForCommonLogarithm;
  } else {
    result = std::log10(operand.value_);
  }
  return error_code;
}
}  // namespace s21::expression
