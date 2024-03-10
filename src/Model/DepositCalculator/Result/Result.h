#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_RESULT_RESULT_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_RESULT_RESULT_H_

#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"

namespace s21::deposit {
class Result {
  using TermType = data_types::TermType;
  using IntervalType = data_types::IntervalType;
  using TransactionType = data_types::TransactionType;
  using InterestRateType = data_types::InterestRateType;
  using CapitalisationStatus = data_types::CapitalisationStatus;

  using RawDate = data_structs::RawDate;
  using DateType = data_structs::DateType;
  using InterestRateDataType = data_structs::InterestRateDataType;
  using InterestRateData = data_structs::InterestRateData;
  using TransactionData = data_structs::TransactionData;

  using TransactionsDataType = data_structs::TransactionsDataType;

  using Dates = data_structs::Dates;
  using DepositPeriod = data_structs::DepositPeriod;
  using DepositTransactions = data_structs::DepositTransactions;
  using IntermediateResults = data_structs::IntermediateResults;
  using PaymentDateArrayType = data_structs::PaymentDateArrayType;
  using TransactionDateType = data_structs::TransactionDateType;
  using TransactionDateArray = data_structs::TransactionDateArray;

 public:
  Result();

  ~Result();

  void Init();

  void ClearIntermediateResults();

  [[nodiscard]] IntermediateResults &GetIntermediateResults();

  [[nodiscard]] double &GetAllYearsIncome();

  [[nodiscard]] double &GetAllYearsTaxes();

  [[nodiscard]] double &GetTotalDeposit();

  [[nodiscard]] double &GetCapitalGains();

 private:
  IntermediateResults intermediate_results_{};
  double all_years_income_{};
  double all_years_taxes_{};
  double total_deposit_{};
  double capital_gains_{};
};
}  // namespace s21::deposit

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_RESULT_RESULT_H_
