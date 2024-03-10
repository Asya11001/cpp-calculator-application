#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_HANDLERS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_HANDLERS_H_

#include <cmath>
#include <stack>
#include <utility>

#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"

namespace s21::expression {
class CalculationHandler {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;

 public:
  static double FromRadianToDegree(const double &radian_value);

  static bool IsValueFineForInverseTrigonometryFunctions(const Data &data);

  static bool HandleUnaryOperator(const Data &token, const Data &operand,
                                  double &result);

  static void CalculateAddition(const Data &operand_1, const Data &operand_2,
                                double &result);

  static void CalculateSubtraction(const Data &operand_1, const Data &operand_2,
                                   double &result);

  static void CalculateMultiplication(const Data &operand_1,
                                      const Data &operand_2, double &result);

  static int CalculateDivision(const Data &operand_1, const Data &operand_2,
                               double &result);

  static int CalculatePower(const Data &operand_1, const Data &operand_2,
                            double &result);

  static int CalculateModulus(const Data &operand_1, const Data &operand_2,
                              double &result);

  static int CalculateArcSine(const Data &operand, double &result);

  static int CalculateArcCosine(const Data &operand, double &result);

  static void CalculateArcTangent(const Data &operand, double &result);

  static void CalculateSine(Data token, Data operand, double &result);

  static void CalculateCosine(const Data &token, Data operand, double &result);

  static void CalculateTangent(const Data &token, Data operand, double &result);

  static int CalculationSquareRoot(const Data &operand, double &result);

  static int CalculateNaturalLogarithm(const Data &operand, double &result);

  static int CalculateCommonLogarithm(const Data &operand, double &result);
};
}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_CALCULATION_CALCULATION_HANDLERS_H_
