#include "Result.h"

namespace s21::deposit {

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

Result::Result() = default;

Result::~Result() = default;

void Result::Init() {
  intermediate_results_.last_annual_taxes_ = constants::kInitValue;
  intermediate_results_.last_annual_income_ = constants::kInitValue;
  all_years_income_ = constants::kInitValue;
  all_years_taxes_ = constants::kInitValue;
  total_deposit_ = constants::kInitValue;
  capital_gains_ = constants::kInitValue;
}

void Result::ClearIntermediateResults() {
  intermediate_results_.income_after_deduction_ = 0;
  intermediate_results_.last_annual_taxes_ = 0;
  intermediate_results_.tax_amount_ = 0;
}

[[nodiscard]] IntermediateResults &Result::GetIntermediateResults() {
  return intermediate_results_;
}

[[nodiscard]] double &Result::GetAllYearsIncome() { return all_years_income_; }

[[nodiscard]] double &Result::GetAllYearsTaxes() { return all_years_taxes_; }

[[nodiscard]] double &Result::GetTotalDeposit() { return total_deposit_; }

[[nodiscard]] double &Result::GetCapitalGains() { return capital_gains_; }

}  // namespace s21::deposit