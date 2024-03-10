#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_STRUCTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_STRUCTS_H_

#include "constants.h"
#include "data_types.h"

namespace s21::expression::data_structs {
struct Data {
  double value_;
  data_types::DataType data_type_;
  data_types::OperatorType operator_type_;
  data_types::FunctionType function_type_;
  data_types::ParenthesesType parentheses_type_;
  data_types::ConstantType constant_type_;
};
struct TokenStatus {
  Data current_token_;
  Data last_token_;
};
}  // namespace s21::expression::data_structs

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_COMMON_DATA_STRUCTS_H_
