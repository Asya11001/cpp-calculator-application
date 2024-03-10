#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_CONSTANTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_CONSTANTS_H_

#include <iostream>

namespace s21::credit::constants {
inline constexpr double kMinAmount{0};
inline constexpr double kMaxAmount{999999999999999};
inline constexpr double kMinInterestRate{0};
inline constexpr double kMaxInterestRate{999};
inline constexpr double kAverageDaysInMonths{30.45};
inline constexpr int kMaxDurationInYears{50};
inline constexpr int kMonthsInYear{12};
inline constexpr int kMaxDurationInMonths{kMaxDurationInYears * kMonthsInYear};
inline constexpr int kRoundValue{100};
}  // namespace s21::credit::constants

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_CONSTANTS_H_
