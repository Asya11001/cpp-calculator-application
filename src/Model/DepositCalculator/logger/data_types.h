#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_DATA_TYPES_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_DATA_TYPES_H_

namespace s21::deposit::logger {
enum class LogType {
  kNone = 0,
  kPayment = 1 << 0,
  kBalanceChanging = 1 << 1,
  kBalanceChangingImpossible = 1 << 2,
};
}

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_DATA_TYPES_H_
