#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_LOGGER_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_LOGGER_H_

#include "../Parameters/Parameters.h"
#include "../Result/Result.h"
#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"
#include "../taxes/data_types.h"
#include "../taxes/taxes.h"
#include "../utility/utility.h"
#include "data_types.h"

namespace s21::deposit::logger {
[[maybe_unused]] static const char* kFileLogName = "deposit.log";
[[maybe_unused]] static const char* kFileTaxesLogName = "taxes.log";

using TaxesLogStatus = s21::deposit::taxes::LogStatus;

using TransactionDateType = data_structs::TransactionDateType;
using TransactionList = std::vector<TransactionDateType>;

using TermType = s21::deposit::data_types::TermType;
using IntervalType = s21::deposit::data_types::IntervalType;
using TransactionType = s21::deposit::data_types::TransactionType;
using InterestRateType = s21::deposit::data_types::InterestRateType;
using CapitalisationStatus = s21::deposit::data_types::CapitalisationStatus;

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

void WriteFileOperation(DateType date, double accrued_interest_value,
                        double refill_value, double deposit_actual_value);

void ClearLogFile();

void ClearTaxesLogFile();

void PrintDateInStringHumanFormat(char* string_dest, DateType date);

void Logging(Parameters& parameters, DateType current_date,
             double aggregated_value, LogType log_type);

void TaxesLogging(const int& year, Result& result,
                  const TaxesLogStatus& log_status);

void FinishLogFile(Result& result);
}  // namespace s21::deposit::logger

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_LOGGER_LOGGER_H_
