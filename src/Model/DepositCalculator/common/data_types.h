#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_TYPES_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_TYPES_H_

namespace s21::deposit::data_types {
enum class TermType {
  kNone = 0,
  kDays = 1 << 0,
  kMonths = 1 << 1,
  kYears = 1 << 2,
};

enum class IntervalType {
  kNone = 0,
  kOneInDay = 1 << 0,
  kOneInWeek = 1 << 1,
  kOneInMonth = 1 << 2,
  kOneInTwoMonth = 1 << 3,
  kOneInThreeMonth = 1 << 4,
  kOneInQuarter = 1 << 4,
  kOneInSixMonth = 1 << 6,
  kOneInHalfYear = 1 << 6,
  kOneInTwelveMonth = 1 << 6,
  kOneInYear = 1 << 6,
  kAtTheEndOfInterval = 1 << 7,
  kAtOnce = 1 << 8,
  kTransactions = (kAtOnce | kOneInMonth | kOneInTwoMonth | kOneInQuarter |
                   kOneInHalfYear | kOneInYear),
  kPeriodicityOfPayments =
      (kAtTheEndOfInterval | kOneInDay | kOneInMonth | kOneInWeek |
       kOneInQuarter | kOneInHalfYear | kOneInYear),
};
enum class TransactionType {
  kNone = 0,
  kRefill = 1 << 0,
  kWithdraw = 1 << 1,
};
enum class InterestRateType {
  kNone = 0,
  kFixed = 1 << 0,
  kDependsOnSum = 1 << 1,
  kDependsOnDayIndex = 1 << 2,
};
enum class CapitalisationStatus {
  kNone = 0,
  kOn = 1 << 0,
  kOff = 1 << 1,
};
}  // namespace s21::deposit::data_types
#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_TYPES_H_
