#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_EXPRESSION_TOKENIZER_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_EXPRESSION_TOKENIZER_H_

#include <cmath>
#include <iomanip>
#include <stack>
#include <utility>
#include <vector>

#include "../../../Model/ExpressionCalculator/common/constants.h"
#include "../../../Model/ExpressionCalculator/common/data_structs.h"
#include "../../../Model/ExpressionCalculator/common/data_types.h"
#include "../../../Model/ExpressionCalculator/common/error_code.h"
#include "../../utility.h"

namespace s21::expression {
class ExpressionTokenizer {
  using Data = data_structs::Data;
  using DataStack = std::stack<Data>;
  using TokenStatus = data_structs::TokenStatus;
  using OperatorType = data_types::OperatorType;

 public:
  ExpressionTokenizer();

  ~ExpressionTokenizer();

  static std::pair<std::string, std::string> SplitExponentialString(
      const std::string &str);

  int HandleConstants(const std::string &token, TokenStatus &token_status);

  int HandleNumber(const std::string &token, TokenStatus &token_status);

  int HandleFunction(const std::string &token, TokenStatus &token_status);

  int HandleOperator(const std::string &token, TokenStatus &token_status);

  int HandleParentheses(const std::string &token, TokenStatus &token_status);

  void HandleVariable(TokenStatus &token_status);

  static data_types::OperatorType FromBinaryToUnaryCode(
      OperatorType operator_code);

  int TokenizeExpression();

  static bool IsConsistingOfXChars(const std::string &str, char x);

  void HandleUnaryOperatorsAfterOpenParentheses();

  void HandleUnaryOperatorsStartExpression();

  static void HandleMultipleVariablesInARow(const std::string &token,
                                            std::vector<std::string> &tokens);

  int FromConstantToValue(Data &data);

  void PushShell(Data data, TokenStatus &token_status);

  void TokenizeImplicitOperators(const TokenStatus &token_status);

  static int IsUnaryOperatorAfterOpenParentheses(const Data &last_token,
                                                 const Data &current_token);

  static int IsUnaryOperatorStartExpression(const Data &last_token,
                                            const Data &current_token);

  static int IsImplicitMultiplication(const Data &last_token,
                                      const Data &current_token);

  void WriteTokenFromExpression(std::string &token, int *p_symbol_index);

  int FromExpressionToInfixNotation();

  void SetExpression(const std::string &string);

  [[maybe_unused]] void SetStack(const DataStack &stack);

  [[maybe_unused]] std::string GetExpression();

  DataStack GetStack();

  void ClearMembers();

  static bool IsScientificNotation(const std::string &token);

  static bool IsOperator(const std::string &token);

  static bool IsParentheses(const std::string &token);

  static bool IsFunction(const std::string &token);

  static bool IsConstant(const std::string &token);

  static bool IsVariable(const std::string &token);

  std::vector<std::string> Tokenize(const std::string &input);

 private:
  std::string expression_{};
  DataStack stack_{};

  static bool GetIsDataTypeFine(const Data &data);

  static bool GetIsFineFunction(int error_code, const Data &data,
                                bool is_data_type_fine);

  static int IsExponentPartsFine(const std::string &token);

  void PlaceMultiplicationBetweenTokens();

  void HandleConstantsInStack();
};

}  // namespace s21::expression

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_EXPRESSION_CALCULATOR_EXPRESSION_TOKENIZER_EXPRESSION_TOKENIZER_H_