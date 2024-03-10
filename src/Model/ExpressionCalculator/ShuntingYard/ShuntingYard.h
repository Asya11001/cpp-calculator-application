#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_SHUNTING_YARD_SHUNTING_YARD_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_SHUNTING_YARD_SHUNTING_YARD_H_

#include <stack>
#include <vector>

#include "../../../Model/ExpressionCalculator/StackManipulation/StackManipulation.h"
#include "../../../Model/ExpressionCalculator/common/data_structs.h"
#include "../../../Model/ExpressionCalculator/common/error_code.h"

namespace s21::expression {
class ShuntingYard {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;

 public:
  ShuntingYard();

  ~ShuntingYard();

  static bool IsUnaryOperator(const data_structs::Data &token);

  static bool IsPower(const data_structs::Data &token);

  static bool IsMultiplicationOrDivisionOrModulus(
      const data_structs::Data &token);

  static bool IsFunction(const data_structs::Data &token);

  static bool IsAdditionOrSubtraction(const data_structs::Data &token);

  static bool IsOperatorOrFunction(const data_structs::Data &token);

  static bool IsValueOrVariable(const data_structs::Data &token);

  static bool IsParentheses(const data_structs::Data &token);

  static bool IsOpenParentheses(const data_structs::Data &token);

  static bool IsClosedParentheses(const data_structs::Data &token);

  static data_types::PrecedenceLevel GetOperatorPrecedence(
      const data_structs::Data &token);

  void HandleBinaryOperatorOrFunction(DataStack &operator_stack,
                                      const data_structs::Data &token);

  static void HandleUnaryOperatorOrFunction(DataStack &operator_stack,
                                            const data_structs::Data &token);

  void HandleBinaryAndUnaryOperators(data_types::LastToken &last_token,
                                     data_structs::Data token,
                                     DataStack &operator_stack);

  static void HandleOpenParentheses(const data_structs::Data &token,
                                    DataStack &operator_stack);

  int HandleCloseParentheses(DataStack &operator_stack);

  int HandleParentheses(data_types::LastToken &last_token,
                        const data_structs::Data &token,
                        DataStack &operator_stack);

  void HandleEndOfExpression(DataStack &operator_stack, int &error_code);

  int FromInfixToPostfix();

  void SetInfixStack(const DataStack &stack);

  [[nodiscard]] DataStack GetPostfixStack();

  void ClearMembers();

 private:
  DataStack infix_stack_{};
  DataStack postfix_stack_{};
};
}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_SHUNTING_YARD_SHUNTING_YARD_H_
