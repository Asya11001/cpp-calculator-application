#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_TAXES_TAXES_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_TAXES_TAXES_H_

#include "../Parameters/Parameters.h"
#include "../Result/Result.h"
#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"
#include "../utility/utility.h"
#include "data_types.h"

namespace s21::deposit::taxes {

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

double GetTaxPercentage(double tax_rate);

double GetTaxDeductionForYear(Parameters &parameters, int year);

int IsFirstTaxForYear(Parameters &parameters, int year);

double CalculateTaxesFromAnnualInterestValue(Parameters &parameters,
                                             Result &result, int year);

int HandleTaxes(Parameters &parameters, Result &result,
                const DateType &last_day, const DateType &current_day);

}  // namespace s21::deposit::taxes

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_TAXES_TAXES_H_
