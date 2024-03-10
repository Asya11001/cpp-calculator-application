#ifndef CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_PARAMETERS_PARAMETERS_H_
#define CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_PARAMETERS_PARAMETERS_H_

#include "../common/constants.h"
#include "../common/data_structs.h"
#include "../common/data_types.h"
#include "../common/error_code.h"
#include "../utility/utility.h"

namespace s21::deposit {
class Parameters {
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
  Parameters();

  ~Parameters();

  void Init();

  void SetDepositAmount(const double &value);

  void SetMinimalBalance(const double &value);

  int SetDepositPeriod(int posting_period, TermType term);

  [[nodiscard]] DepositPeriod &GetDepositPeriod();

  int AddRefillTransaction(double value, RawDate raw_date,
                           IntervalType interval);

  static int AddRefillTransactionStatic(Parameters &parameters, double value,
                                        RawDate raw_date,
                                        IntervalType interval);

  int AddPartialWithdrawalTransaction(double value, RawDate raw_date,
                                      IntervalType interval);

  static int AddPartialWithdrawalTransactionStatic(Parameters &parameters,
                                                   double value,
                                                   RawDate raw_date,
                                                   IntervalType interval);

  int AddInterestRate(InterestRateType type, double aggregated_value,
                      double interest_rate);

  int SetTax(const double &tax_value);

  [[nodiscard]] double &GetTax();

 public:
  [[nodiscard]] DateType &GetStartDate();

  [[nodiscard]] DateType &GetFinishDate();

  int &GetReplenishmentsListNextIndex();

  int &GetPartialWithdrawalsListNextIndex();

  TransactionsDataType &GetReplenishmentsList();

  TransactionsDataType &GetPartialWithdrawalsList();

  [[nodiscard]] IntervalType &GetPeriodicityOfPayments();

  [[nodiscard]] DepositTransactions &GetDepositTransactions();

  [[nodiscard]] TransactionsDataType &GetReplenishmentList();

  [[nodiscard]] TransactionsDataType &GetPartialWithdrawalList();

  [[nodiscard]] InterestRateData &GetInterestRate();

  [[nodiscard]] double &GetAmount();

  [[nodiscard]] double &GetInterestValue();

  [[nodiscard]] CapitalisationStatus &GetCapitalisationStatus();

  [[nodiscard]] double &GetMinimalBalance();

  [[nodiscard]] double &GetDepositAmount();

 private:
  void InitInterestRate();

  void InitDepositAmount();

  void InitDepositPostingPeriod();

  void InitDepositDate();

  void InitDepositFinishDate();

  void InitDepositTerm();

  void InitPeriodicityOfPayments();

  void InitInterestValue();

  void InitCapitalisationStatus();

  void InitReplenishmentsList();

  void InitPartialWithdrawalsList();

  void InitMinimalBalance();

 private:
  double deposit_amount_{};
  double interest_value_{};
  Dates dates_{};
  DepositPeriod deposit_period_{};
  InterestRateData interest_rate_{};
  IntervalType periodicity_of_payments_{};
  CapitalisationStatus capitalisation_status_{};
  DepositTransactions deposit_transactions_{};
  double tax_rate_{};
  double minimal_balance_{};
};

}  // namespace s21::deposit
#endif  // CPP3_SMART_CALC_V_2_0_1_MODEL_DEPOSIT_CALCULATOR_PARAMETERS_PARAMETERS_H_
