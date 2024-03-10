#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_TYPES_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_TYPES_H_
namespace s21::credit::data_types {

enum class TermType {
  kNone = 0,
  kDays = 1 << 0,
  kMonths = 1 << 1,
  kYears = 1 << 2,
};

enum class PaymentType {
  kNone = 0,
  kAnnual = 1 << 0,
  kDifferential = 1 << 1,
};

}  // namespace s21::credit::data_types
#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_TYPES_H_
