#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_ERROR_CODE_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_ERROR_CODE_H_

namespace s21::credit::error_code {
const int kNoError = 0;
const int kInvalidInput = 1 << 0;
const int kInvalidDeadline = 1 << 1;
const int kInvalidCreditAmount = 1 << 3;
const int kInvalidInterestRate = 1 << 4;
};  // namespace s21::credit::error_code

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_ERROR_CODE_H_
