#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_SETTINGS_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_SETTINGS_H_

#include "error_code.h"

namespace s21::settings {
[[maybe_unused]] static int error_code_expression = error_code::kNoError;
[[maybe_unused]] static int error_code_variable = error_code::kNoError;

[[maybe_unused]] static int error_code_domain = error_code::kNoError;
[[maybe_unused]] static int error_code_codomain = error_code::kNoError;
[[maybe_unused]] static int error_code_graph = error_code::kNoError;

[[maybe_unused]] static int error_code_credit_amount = error_code::kNoError;
[[maybe_unused]] static int error_code_credit_deadline = error_code::kNoError;
[[maybe_unused]] static int error_code_credit_interest_value =
    error_code::kNoError;

[[maybe_unused]] static int error_code_deposit_amount = error_code::kNoError;
[[maybe_unused]] static int error_code_deposit_placing_period =
    error_code::kNoError;
}  // namespace s21::settings

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_COMMON_SETTINGS_H_
