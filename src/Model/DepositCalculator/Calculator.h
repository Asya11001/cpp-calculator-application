#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_CALCULATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_CALCULATOR_H_

#include "BaseCalculator/BaseCalculator.h"
#include "logger/logger.h"
#include "taxes/taxes.h"
#include "utility/utility.h"

namespace s21::deposit {
class Calculator : public BaseCalculator {
  using LogType = logger::LogType;

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
  static double FromTransactionDateTypeToValue(
      TransactionDateType &transaction);

  static double GetBalanceChangesForDate(DateType last_day,
                                         TransactionList &transaction_list,
                                         int &transaction_index);

  static int FindFixInterestRate(const InterestRateData &interest_rate_data);

  static double GetInterestRateByIndex(
      const InterestRateData &interest_rate_data, int index);

  static int GetInterestValueFix(const InterestRateData &interest_rate_data,
                                 double &interest_rate);

  static double GetCurrentInterestRateByIndex(
      const InterestRateData &interest_rate_data, int index);

  static int IsSuitableInterestRate(bool is_aggregated_value_greater,
                                    int is_first_entry,
                                    double current_rate_value,
                                    const InterestRateData &interest_rate_data,
                                    int closest_index);

  static double GetInterestRateAggregatedValue(
      const InterestRateData &interest_rate_data, int index);

  static int GetCurrentInterestValueIndexDependsOnAggregatedValue(
      const InterestRateData &interest_rate_data, double aggregated_value);

  static int IsDependsOnDayIndexOrSum(InterestRateDataType data);

  static int GetInterestValueDependsOnAggregatedValue(
      const InterestRateData &interest_rate_data, double &interest_rate,
      double aggregated_value);

  static int IsInterestRateDependsOnSum(const InterestRateDataType &data);

  double GetInterestRate(int day_index);

  double GetPayment(const DateType &last_day, const int &day_index);

  static void HandleLastPayment(double &payment_size,
                                const PaymentDateArrayType &dates_payments,
                                const int &payment_index);

  int HandlePaymentMatch(const PaymentDateArrayType &dates_payments,
                         const DateType &current_day, int &payment_index,
                         const int &day_index);

  void PerformTransactionChanging(const double &balance_changes,
                                  const DateType &current_day);

  int HandleTransactionMatch(TransactionList &transaction_list,
                             DateType current_day, int &transaction_index);

  int HandlePaymentAtTheEndOfInterval(DateType current_day, int day_index);

  int IsPaymentPeriodicityAtTheEndOfInterval();

  void HandleLastPaymentCapitalisation(const int &error_code);

  int HandleDepositCalculations(TransactionList &transaction_list);

  void SetFinishDate();

  void AdjustParameters();

  void SetParameters(const Parameters &parameters);

  [[nodiscard]] Result GetResult() const;

  int Calculate();

  void ClearMembers();

  void ClearParameters();

  void ClearResult();

  static double GetDayCoefficient(double current_interest_rate,
                                  int days_in_previous_month);

  static double GetMonthCoefficient(int days_in_previous_month,
                                    double day_coefficient);

  static double GetActualCoefficient(double month_result_coefficient,
                                     double month_coefficient);

  double GetNormalizedActualCoefficient(double average_month_duration,
                                        double day_coefficient);

  double GetResultPayment(double actual_coefficient);
};
}  // namespace s21::deposit

#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_CALCULATOR_H_
