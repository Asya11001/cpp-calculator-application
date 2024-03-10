#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_ERROR_CODE_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_ERROR_CODE_H_

namespace s21::expression::error_code {
const int kNoError = 0;
const int kMismatchedParenthesis = 1 << 0;
const int kInvalidExpressionFormat = 1 << 1;
const int kResultCalculatedValueIsNan = 1 << 2;
const int kInsufficientOperandsForOperator = 1 << 3;
const int kDivisionByZero = 1 << 4;
const int kModulusMyZero = 1 << 5;
const int kUnknownOperator = 1 << 6;
const int kIncorrectValueForNaturalLogarithm = 1 << 8;
const int kIncorrectValueForCommonLogarithm = 1 << 9;
const int kSquareOfNegativeNumber = 1 << 10;
const int kIndeterminateResultForArcSine = 1 << 11;
const int kIndeterminateResultForArcCosine = 1 << 12;
const int kTwoOperatorsInARow = 1 << 15;
const int kEmptyParenthesis = 1 << 16;
const int kInsufficientOperandsForFunction = 1 << 19;

const int kUnknownFunction = 1 << 19;
const int kUnknownToken = 1 << 20;
const int kNumberIsEmpty = 1 << 21;
const int kExponentIsTooGreat = 1 << 22;
const int kNumberIsTooLong = 1 << 23;
const int kUnknownConstant = 1 << 24;
const int kUnknownParentheses = 1 << 25;

const int kPowerValueIsTooBig = 1 << 26;
};  // namespace s21::expression::error_code

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_ERROR_CODE_H_
