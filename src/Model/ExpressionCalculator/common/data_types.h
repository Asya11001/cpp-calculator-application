#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_TYPES_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_TYPES_H_

namespace s21::expression::data_types {
enum class DataType {
  kNone = 0,
  kValue = 1 << 0,
  kOperator = 1 << 1,
  kFunction = 1 << 2,
  kParentheses = 1 << 3,
  kVariable = 1 << 4,
  kConstant = 1 << 5,
};
enum class OperatorType {
  kNone = 0,
  kAddition = 1 << 0,
  kSubtraction = 1 << 1,
  kMultiplication = 1 << 2,
  kDivision = 1 << 3,
  kPower = 1 << 4,
  kModulus = 1 << 5,
  kUnaryPlus = 1 << 6,
  kUnaryMinus = 1 << 7,
};
enum class FunctionType {
  kNone = 0,
  kSine = 1 << 0,
  kCosine = 1 << 1,
  kTangent = 1 << 2,
  kSineRadian = 1 << 3,
  kCosineRadian = 1 << 4,
  kTangentRadian = 1 << 5,
  kArcSine = 1 << 6,
  kArcCosine = 1 << 7,
  kArcTangent = 1 << 8,
  kSquareRoot = 1 << 9,
  kNaturalLogarithm = 1 << 10,
  kCommonLogarithm = 1 << 11,
};
enum class ParenthesesType {
  kNone = 0,
  kOpened = 1 << 0,
  kClosed = 1 << 1,
};

enum class ConstantType {
  kNone = 0,
  kPi = 1 << 0,
  kE = 1 << 1,
};

enum class PrecedenceLevel {
  k0 = 0,
  k1 = 1,
  k2 = 2,
  k3 = 3,
  k4 = 4,
};
enum class LastToken {
  kNone = 0,
  kOperandOrFunction = 1,
};
}  // namespace s21::expression::data_types
#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_TYPES_H_
