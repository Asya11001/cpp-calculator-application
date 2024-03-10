#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_VALIDATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_VALIDATOR_H_

#include <stack>

#include "../StackManipulation/StackManipulation.h"
#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"

namespace s21::expression {
class Validator {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;
  using TokenStatus = data_structs::TokenStatus;

 public:
  static bool IsConstant(const Data &current_token);

  static bool IsTwoOperatorsInARow(const Data &current_token,
                                   const Data &previous_token);

  static bool IsEmptyParenthesis(const Data &current_token,
                                 const Data &previous_token);

  static int ValidateExpression(DataStack infix_notation);
};
}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_VALIDATOR_H_
