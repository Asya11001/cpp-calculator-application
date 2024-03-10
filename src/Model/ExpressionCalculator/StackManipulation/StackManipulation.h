#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_STACK_MANIPULATION_STACK_MANIPULATION_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_STACK_MANIPULATION_STACK_MANIPULATION_H_

#include <algorithm>
#include <stack>
#include <vector>

#include "../common/data_structs.h"

namespace s21::expression {
class StackManipulation {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;

 public:
  static void ReverseStack(DataStack &stack);
};
}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_STACK_MANIPULATION_STACK_MANIPULATION_H_
