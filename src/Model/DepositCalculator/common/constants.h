#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_CONSTANTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_CONSTANTS_H_

#include "data_structs.h"
#include "iostream"

typedef struct tm DateType;

namespace s21::deposit::constants {
inline constexpr bool kFlagFalse{false};
inline constexpr bool kFlagTrue{true};

inline constexpr double kBigNumber{999999999999999.0};
inline constexpr double kSmallNumber{1};

inline constexpr int kDaysInWeek{7};
inline constexpr int kMonthsInQuarter{3};
inline constexpr int kMonthsInHalfOfYear{6};
inline constexpr int kMonthsInYear{12};

inline constexpr int kYearBase{1900};
inline constexpr int kMakeTimeError{-1};

inline constexpr int kSecondsInMinute{60};
inline constexpr int kMinutesInHour{60};
inline constexpr int kHoursInDay{24};
inline constexpr int kSecondsInDay{kSecondsInMinute * kMinutesInHour *
                                   kHoursInDay};

inline constexpr int kMinDayValueInDate{1};
inline constexpr int kMinValueInDate{0};

inline constexpr double kMinTransactionValue{kSmallNumber};
inline constexpr double kMaxTransactionValue{kBigNumber};

inline constexpr double kNegativeOne{-1};

inline constexpr int kMaxInterestRateAmount{10};
inline constexpr int kMaxTransactionsAmount{10};

inline constexpr int kZeroDays{0};
inline constexpr int kInitValue{0};
inline constexpr double kInitValueDouble{0};

inline constexpr double kInitDepositAmountValue{kInitValue};
inline constexpr double kInitTransactionValue{kInitValue};
inline constexpr int kInitDepositPostingPeriodValue{kInitValue};
inline constexpr double kInitTransactionAmountValue{kInitValue};
inline constexpr double kInitMinimalBalanceValue{kInitValue};

inline constexpr double kMinTransactionAmountValue{kInitValue};
inline constexpr double kMaxTransactionAmountValue{kBigNumber};

inline constexpr double kMinDepositAmountValue{kInitValue};
inline constexpr double kMaxDepositAmountValue{kBigNumber};

inline constexpr int kMinDepositPostingPeriodValue{1};
inline constexpr int kMaxDepositPostingPeriodDaysValue{18250};
inline constexpr int kMaxDepositPostingPeriodMonthsValue{600};
inline constexpr int kMaxDepositPostingPeriodYearsValue{50};

inline constexpr double kMinTaxValue{1e-6};
inline constexpr double kMaxTaxValue{100};

inline constexpr double kMinCoefficient{0.0};
inline constexpr double kMaxCoefficient{1.0};
inline constexpr double kInitCoefficient{1.0};

inline constexpr DateType kInitDate = {
    .tm_sec = 0,
    .tm_min = 0,
    .tm_hour = 0,
    .tm_mday = 0,
    .tm_mon = 0,
    .tm_year = 0,
    .tm_wday = 0,
    .tm_yday = 0,
    .tm_isdst = 0,
    .tm_gmtoff = 0,
    .tm_zone = nullptr,
};
inline constexpr int kOnePayment{1};
inline constexpr int kRoundValue{100};

inline constexpr double kFirstFee{75000};
inline constexpr double kNonFirstFee{130000};
}  // namespace s21::deposit::constants

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_CONSTANTS_H_
