#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_STRUCTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_STRUCTS_H_

#include <map>

#include "constants.h"
#include "data_types.h"

namespace s21::credit::data_structs {
struct Parameters {
  double amount_{};
  int deadline_{};
  double interest_rate_{};
  data_types::PaymentType payment_type_{};
  data_types::TermType term_type_{};
};

struct Result {
  double monthly_payment_begin_{};
  double monthly_payments_end_{};
  double overpayment_{};
  double total_payment_{};
};

}  // namespace s21::credit::data_structs

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_CREDIT_CALCULATOR_COMMON_DATA_STRUCTS_H_
