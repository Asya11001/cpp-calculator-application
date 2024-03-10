#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_UTILITY_UTILITY_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_UTILITY_UTILITY_H_

#include <cmath>

#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"

namespace s21::deposit::utility {
using TransactionDateType = data_structs::TransactionDateType;
using TransactionList = std::vector<TransactionDateType>;

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

void RoundValue(double &value, int round_value);

void SwapTransactions(TransactionDateType &a, TransactionDateType &b);

int PartitionDates(TransactionList &array, int lowest_index, int highest_index);

void QuickSortDates(TransactionList &transaction_list, int lowest_index,
                    int highest_index);

int GetMaxValueForCurrentTermType(const data_types::TermType &term);

void CopyDate(DateType &dest, const DateType &src);

[[nodiscard]] int IsNegativeDate(const RawDate &raw_date);

int AreDatesEqual(const DateType &date_1, const DateType &date_2);

int AreDatesNotEqual(const DateType &date_1, const DateType &date_2);

int IsDateValid(DateType date);

int SetDate(const RawDate &raw_date, DateType &date);

void InitTransactionData(TransactionData &data);

int SetTransactionType(TransactionData &data, const TransactionType &type);

int SetTransactionDate(TransactionData &data, RawDate raw_date);

int SetTransactionInterval(TransactionData &data, const IntervalType &interval);

int SetTransactionValue(TransactionData &data, const double &value);

int GetDayDifference(DateType &date_1, DateType &date_2, int &day_difference);

int GetTransactionsCount(const TransactionsDataType &transactions_data);

void NegateDouble(double &value);

void AddIntervalToTheDate(const IntervalType &interval, DateType &date,
                          const DateType previous_date);

bool IsValidIntervalForPeriodicityOfPayments(const IntervalType &interval);

double CalculateCurrentCoefficient(double second_difference_last_finish,
                                   double second_difference_penultimate_last);

double GetTimeDifference(const time_t &start_time, const time_t &finish_time);

int GetDaysInCurrentMonth(const DateType &date);

int GetDaysInPreviousMonth(const DateType &date);

int GetDaysInCurrentYear(const DateType &date);

double GetAverageMonthDurationInThisYear(const DateType &date);

}  // namespace s21::deposit::utility

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_UTILITY_UTILITY_H_