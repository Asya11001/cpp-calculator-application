#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_CONSTANTS_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_CONSTANTS_H_

namespace s21::constants {
inline constexpr int kInitValue{0};
inline constexpr double kInitValueDouble{0};

inline constexpr int kExpressionTabIndex{0};
inline constexpr int kGraphTabIndex{3};
inline constexpr int kCreditTabIndex{1};
inline constexpr int kDepositTabIndex{2};

inline constexpr double kBigNumber{10000000000};

inline constexpr int kPlotPointCount{512};
inline constexpr double kMaxCreditAmount{kBigNumber};
inline constexpr int kMaxMonthCreditDuration{600};
inline constexpr double kMinInterestValue{0};
inline constexpr double kMaxInterestValue{999};

inline constexpr double kMinDepositAmountValue{0};
inline constexpr double kMaxDepositAmountValue{kBigNumber};

inline constexpr int kMinDepositPostingPeriod{1};
inline constexpr int kMaxDepositPostingPeriodDays{18250};
inline constexpr int kMaxDepositPostingPeriodMonths{600};
inline constexpr int kMaxDepositPostingPeriodYears{50};

inline constexpr double kMinTransactionAmountValue{0};
inline constexpr double kMaxTransactionAmountValue{kBigNumber};
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

inline constexpr int kYearBase{1900};
static const char* kTaxesLogsFileName{"taxes.log"};
static const char* kDepositLogsFileName{"deposit.log"};

inline constexpr double kDomainBoundValue{1000000};
}  // namespace s21::constants

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_CONSTANTS_H_
