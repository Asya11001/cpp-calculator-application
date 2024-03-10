#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_CONSTANTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_CONSTANTS_H_

#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <vector>

#include "data_types.h"

namespace s21::expression::constants {
const int kMaxExpressionLength{256};
inline constexpr int kMaxPowerValue{128};
inline constexpr int kInitTokenIndex{0};
inline constexpr int kRoundValue{1000000000};

const std::string kStringPlus{"+"};
const std::string kStringDash{"-"};
const std::string kStringAsterisk{"*"};
const std::string kStringSlash{"/"};
const std::string kStringCircumflex{"^"};
const std::string kStringPercent{"%"};
const std::string kStringOpenParentheses{"("};
const std::string kStringCloseParentheses{")"};

const std::string kStringPi{"pi"};
const std::string kStringE{"e"};

const std::string kStringCos{"cos"};
const std::string kStringSin{"sin"};
const std::string kStringTan{"tan"};
const std::string kStringCosRadian{"Cos"};
const std::string kStringSinRadian{"Sin"};
const std::string kStringTanRadian{"Tan"};
const std::string kStringAcos{"acos"};
const std::string kStringAsin{"asin"};
const std::string kStringAtan{"atan"};
const std::string kStringSqrt{"sqrt"};
const std::string kStringLn{"ln"};
const std::string kStringLog{"log"};
const std::string kStringX{"x"};

inline constexpr double kPiValue{3.141592653589793238462643383};
inline constexpr double kEValue{2.718281828459045235360287471};

const std::regex kTokenRegex(
    R"(([+\-*/%^()])|(pi|e)|(\d+(\.\d+)?(?:[eE][-+]?\d+)?)|([a-zA-Z]+)|(\.))");
const std::regex kFunctionRegex("[a-zA-Z]+");
const std::regex kParenthesesRegex("[()]");
const std::regex kOperatorRegex("[\\^%*/+-]");
const std::regex kScientificNumberRegex(R"(\d+(\.\d+)?([eE][-+]?\d+)?)");

const std::vector<std::string> kNotFunction = {kStringX, kStringPi, kStringE};
const std::set<std::string> kConstantTokens = {
    kStringPi,
    kStringE,
};
const std::set<std::string> kVariableTokens = {kStringX};

const double kBoundValueForInverseTrigonometryFunctions{1};

inline constexpr int kMaxNumberLength{16};
inline constexpr int kMaxExponentValue{16};

const std::map<std::string, data_types::FunctionType> kFunctionTypeMap = {
    {constants::kStringSin, data_types::FunctionType::kSine},
    {constants::kStringCos, data_types::FunctionType::kCosine},
    {constants::kStringTan, data_types::FunctionType::kTangent},
    {constants::kStringSinRadian, data_types::FunctionType::kSineRadian},
    {constants::kStringCosRadian, data_types::FunctionType::kCosineRadian},
    {constants::kStringTanRadian, data_types::FunctionType::kTangentRadian},
    {constants::kStringAsin, data_types::FunctionType::kArcSine},
    {constants::kStringAcos, data_types::FunctionType::kArcCosine},
    {constants::kStringAtan, data_types::FunctionType::kArcTangent},
    {constants::kStringSqrt, data_types::FunctionType::kSquareRoot},
    {constants::kStringLn, data_types::FunctionType::kNaturalLogarithm},
    {constants::kStringLog, data_types::FunctionType::kCommonLogarithm},
};
const std::map<std::string, data_types::OperatorType> kOperatorTypeMap = {
    {constants::kStringCircumflex, data_types::OperatorType::kPower},
    {constants::kStringPercent, data_types::OperatorType::kModulus},
    {constants::kStringAsterisk, data_types::OperatorType::kMultiplication},
    {constants::kStringSlash, data_types::OperatorType::kDivision},
    {constants::kStringPlus, data_types::OperatorType::kAddition},
    {constants::kStringDash, data_types::OperatorType::kSubtraction},
};
const std::map<std::string, data_types::ParenthesesType> kParenthesesTypeMap = {
    {constants::kStringCloseParentheses, data_types::ParenthesesType::kClosed},
    {constants::kStringOpenParentheses, data_types::ParenthesesType::kOpened},
};

const std::map<std::string, data_types::ConstantType> kConstantTypeMap = {
    {constants::kStringPi, data_types::ConstantType::kPi},
    {constants::kStringE, data_types::ConstantType::kE},
};
const std::map<data_types::ConstantType, const double> kConstantsToValuesMap = {
    {data_types::ConstantType::kPi, kPiValue},
    {data_types::ConstantType::kE, kEValue},
};

const std::map<std::pair<data_types::DataType, data_types::DataType>, bool>
    kImplicitMultiplicationMap = {
        {{data_types::DataType::kConstant, data_types::DataType::kConstant},
         true},
        {{data_types::DataType::kConstant, data_types::DataType::kFunction},
         true},
        {{data_types::DataType::kConstant, data_types::DataType::kVariable},
         true},
        {{data_types::DataType::kConstant, data_types::DataType::kValue}, true},
        {{data_types::DataType::kVariable, data_types::DataType::kConstant},
         true},
        {{data_types::DataType::kVariable, data_types::DataType::kFunction},
         true},
        {{data_types::DataType::kVariable, data_types::DataType::kVariable},
         true},
        {{data_types::DataType::kVariable, data_types::DataType::kValue}, true},
        {{data_types::DataType::kValue, data_types::DataType::kConstant}, true},
        {{data_types::DataType::kValue, data_types::DataType::kFunction}, true},
        {{data_types::DataType::kValue, data_types::DataType::kVariable}, true},
        {{data_types::DataType::kValue, data_types::DataType::kValue}, true},
};

}  // namespace s21::expression::constants

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_CONSTANTS_H_
