#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_STRUCTS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_STRUCTS_H_

#include <ctime>
#include <vector>

#include "data_types.h"
#include "error_code.h"

namespace s21::deposit::data_structs {
typedef struct tm DateType;

struct RawDate {
  int day_{};
  int month_{};
  int year_{};
};

struct InterestRateDataType {
  data_types::InterestRateType type_{};
  double aggregated_value_{};
  double interest_rate_{};
};

struct InterestRateData {
  std::vector<InterestRateDataType> interest_rate_data_{};
  int interest_rate_amount_{};
};

struct TransactionData {
  data_types::TransactionType transaction_type_{};
  DateType transaction_date_{};
  data_types::IntervalType transaction_periodicity_{};
  double value_{};
};
struct TransactionsDataType {
  std::vector<TransactionData> transactions_data_{};
  int transactions_amount_{};
};
struct Dates {
  DateType start_{};
  DateType finish_{};
};
struct DepositPeriod {
  int deposit_posting_period_{};
  data_types::TermType deposit_term_{};
};

struct DepositTransactions {
  TransactionsDataType replenishments_list_{};
  TransactionsDataType partial_withdrawals_list_{};
};

struct IntermediateResults {
  double last_annual_taxes_{};
  double last_annual_income_{};
  double tax_deduction_{};
  double income_after_deduction_{};
  double tax_amount_{};
  double deposit_changes_{};
};

struct DepositResult {
  IntermediateResults intermediate_results_{};
  double all_years_income_{};
  double all_years_taxes_{};
  double total_deposit_{};
  double capital_gains_{};
};
struct PaymentDateArrayType {
  double last_coefficient_{};
  int number_of_records_{};
  std::vector<DateType> date_array_{};
};
struct TransactionDateType {
  data_types::TransactionType transaction_type_{};
  DateType date_{};
  double value_{};
};
struct TransactionDateArray {
  std::vector<TransactionDateType> transaction_date_array_{};
  int number_of_records_{};
};
}  // namespace s21::deposit::data_structs

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_COMMON_DATA_STRUCTS_H_
