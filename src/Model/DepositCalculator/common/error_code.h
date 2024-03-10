#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_ERROR_CODE_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_ERROR_CODE_H_

namespace s21::deposit::error_code {
const int kNoError = 0;
const int kAmountIsNegativeNumber = 1 << 0;
const int kAmountIsTooBig = 1 << 1;
const int kPostingPeriodIsTooSmall = 1 << 2;
const int kPostingPeriodIsTooGreat = 1 << 3;
const int kTermIsNotSet = 1 << 4;
const int kInterestListIsFull = 1 << 5;
const int kPeriodicityOfPaymentsIsNotSet = 1 << 6;
const int kCapitalisationStatusIsNotSet = 1 << 7;
const int kValueForRefillTransactionIsTooSmall = 1 << 8;
const int kValueForRefillTransactionIsTooGreat = 1 << 9;
const int kIntervalForRefillTransactionIsNotSet = 1 << 10;
const int kRefillListIsFull = 1 << 11;
const int kValueForPartialWithdrawalTransactionIsTooSmall = 1 << 12;
const int kIntervalForPartialWithdrawalTransactionIsNotSet = 1 << 13;
const int kPartialWithdrawalListIsFull = 1 << 14;
const int kTransactionTypeIsNotSet = 1 << 15;
const int kIntervalTypeIsNotSet = 1 << 16;
const int kValueForTransactionIsTooSmall = 1 << 17;
const int kValueForTransactionIsTooGreat = 1 << 18;
const int kValueForTaxIsTooSmall = 1 << 19;
const int kValueForTaxIsTooGreat = 1 << 20;
const int kDateIsNegativeNumber = 1 << 21;
const int kDateIsInvalid = 1 << 22;
const int kMemoryAllocationError = 1 << 23;
const int kIntervalTypeIsIncorrectForThisCase = 1 << 24;
const int kPeriodicityOfPaymentsIsIncorrectForPeriodicityOfPayments = 1 << 25;
const int kPostingPeriodIsIncorrect = 1 << 26;
const int kMinimalValueIsNegativeNumber = 1 << 27;
const int kMinimalValueIsTooBig = 1 << 28;
};  // namespace s21::deposit::error_code

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_ERROR_CODE_H_