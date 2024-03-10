#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_BASE_CALCULATOR_BASE_CALCULATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_BASE_CALCULATOR_BASE_CALCULATOR_H_

#include <ctime>

#include "../Parameters/Parameters.h"
#include "../Result/Result.h"
#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"
#include "../utility/utility.h"

namespace s21::deposit {
class BaseCalculator {
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

  using TransactionList = std::vector<TransactionDateType>;

 public:
  BaseCalculator();

  ~BaseCalculator();

  int SetDepositAmount(double value);

  int GetNumberOfRecordsInArrayOfPayments();

  bool HandleOnePaymentCase(PaymentDateArrayType &date_array);

  void HandleCoefficientForLastPayment(PaymentDateArrayType &date_array);

  int MakeArrayOfPayments(PaymentDateArrayType &date_array);

  int GetNumberOfRecordsInTransactionsArray(
      const TransactionData &transaction_data);

  int MakeArrayOfTransactions(TransactionDateArray &date_array,
                              const TransactionData &transaction_data);

  static void SummarizeTransactions(TransactionList &transaction_list,
                                    TransactionDateArray &date_array,
                                    const TransactionType &transaction_type);

  int MakeAllTransactions(PaymentDateArrayType &dates_payments,
                          TransactionList &transaction_list);

 protected:
  Parameters params_{};
  Result result_{};
};
}  // namespace s21::deposit

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_BASE_CALCULATOR_BASE_CALCULATOR_H_
