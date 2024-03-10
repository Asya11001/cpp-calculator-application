#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_H_

#include <cmath>
#include <stack>
#include <utility>

#include "../StackManipulation/StackManipulation.h"
#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"
#include "CalculationHandler.h"

namespace s21::expression {
class Calculation {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;

 public:
  Calculation();

  static void HandleVariable(data_structs::Data &token, double value);

  static int PerformOperatorCalculations(const Data &token,
                                         const Data &operand_1,
                                         const Data &operand_2, double &result);

  static int PerformFunctionCalculations(const Data &token, const Data &operand,
                                         double &result);

  static void HandlePushingResultValueInCalculationStack(
      DataStack &calculation_stack, double &result, int error_code);

  static int HandleCalculationOperators(DataStack &calculation_stack,
                                        const Data &token);

  static int HandleCalculationFunctions(DataStack &calculation_stack,
                                        Data &token);

  static int HandleCalculationsOperatorsAndFunctions(
      DataStack &calculation_stack, Data &token);

  int HandleFinalResultAssigning(DataStack &calculation_stack);

  int CalculateExpression();

  void SetPostfixStack(const DataStack &stack);

  [[nodiscard]] double GetResult() const;

  void SetVariableValue(const double &value);

  [[nodiscard]] double GetVariableValue() const;

  void ClearMembers();

 private:
  DataStack postfix_stack_;
  double result_{};
  double variable_value_{};

  static bool GetIsSine(const Data &token);

  static bool GetIsCosine(const Data &token);

  static bool GetIsTangent(const Data &token);

  static bool GetIsTokenNumber(const Data &token);

  static bool GetIsTokenModifier(const Data &token);
};
}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_H_
