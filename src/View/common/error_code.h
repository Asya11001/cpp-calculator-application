#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_ERROR_CODE_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_ERROR_CODE_H_

namespace s21::error_code {
static const int kNoError = 0;
static const int kInvalidExpressionFormat = 1 << 0;
static const int kInvalidVariableFormat = 1 << 1;

static const int kIncorrectInterestValue = 1 << 1;
static const int kIncorrectInterestRateType = 1 << 2;
static const int kUnableToFindChildren = 1 << 3;
static const int kIncorrectTransactionValue = 1 << 4;
static const int kZeroInterestRateAmount = 1 << 5;
static const int kIncorrectDepositValue = 1 << 6;
static const int kIncorrectPlacementPeriod = 1 << 7;

static const int kInvalidValueForDomain = 1 << 8;
static const int kInvalidValueForCodomain = 1 << 9;

static const int kUnableToBuildGraph = 1 << 10;

static const int kDateIsNegativeNumber = 1 << 11;
static const int kMktimeError = 1 << 12;
static const int kDateIsInvalid = 1 << 13;

static const int kPeriodicityOfPaymentsIsNotSet = 1 << 14;
static const int kPeriodicityOfPaymentsIsIncorrect = 1 << 15;
}  // namespace s21::error_code
#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_ERROR_CODE_H_
