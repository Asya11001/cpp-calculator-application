#include "Parameters.h"

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

Parameters::Parameters() { Init(); }

Parameters::~Parameters() = default;

void Parameters::Init() {
  InitDepositAmount();
  InitInterestValue();
  InitDepositPostingPeriod();
  InitDepositDate();
  InitDepositFinishDate();
  InitDepositTerm();
  InitInterestRate();
  InitPeriodicityOfPayments();
  InitCapitalisationStatus();
  InitReplenishmentsList();
  InitPartialWithdrawalsList();
  InitMinimalBalance();

  GetReplenishmentsList().transactions_data_.reserve(20);
  GetPartialWithdrawalsList().transactions_data_.reserve(20);
  GetReplenishmentsList().transactions_data_.clear();
  GetPartialWithdrawalsList().transactions_data_.clear();
}

void Parameters::SetDepositAmount(const double &value) {
  deposit_amount_ = value;
}

void Parameters::SetMinimalBalance(const double &value) {
  minimal_balance_ = value;
}

int Parameters::SetDepositPeriod(int posting_period, TermType term) {
  int error_code = error_code::kNoError;
  int max_value_for_current_term = utility::GetMaxValueForCurrentTermType(term);

  if (max_value_for_current_term == constants::kInitValue) {
    error_code = error_code::kPostingPeriodIsIncorrect;
  } else if (posting_period < constants::kMinDepositAmountValue) {
    error_code = error_code::kPostingPeriodIsTooSmall;
  } else if (posting_period > max_value_for_current_term) {
    error_code = error_code::kPostingPeriodIsTooGreat;
  }
  if (!error_code) {
    deposit_period_.deposit_posting_period_ = posting_period;
    deposit_period_.deposit_term_ = term;
  }
  return error_code;
}

[[nodiscard]] DepositPeriod &Parameters::GetDepositPeriod() {
  return deposit_period_;
}

int Parameters::AddRefillTransaction(double value, RawDate raw_date,
                                     IntervalType interval) {
  int error_code = error_code::kNoError;
  int &refill_amount = GetReplenishmentsListNextIndex();

  if (refill_amount >= constants::kMaxTransactionsAmount) {
    error_code = error_code::kRefillListIsFull;
  }
  if (!error_code) {
    TransactionData new_transaction =
        GetReplenishmentsList().transactions_data_[refill_amount];

    error_code =
        utility::SetTransactionType(new_transaction, TransactionType::kRefill);
    if (!error_code) {
      error_code = utility::SetTransactionDate(new_transaction, raw_date);
    }
    if (!error_code) {
      error_code = utility::SetTransactionInterval(new_transaction, interval);
    }
    if (!error_code) {
      error_code = utility::SetTransactionValue(new_transaction, value);
    }

    GetReplenishmentsList().transactions_data_.insert(
        GetReplenishmentsList().transactions_data_.end(), new_transaction);

    GetReplenishmentsList().transactions_amount_++;
  }

  return error_code;
}

int Parameters::AddRefillTransactionStatic(Parameters &parameters, double value,
                                           RawDate raw_date,
                                           IntervalType interval) {
  int error_code = error_code::kNoError;
  int &refill_amount = parameters.GetReplenishmentsListNextIndex();

  if (refill_amount >= constants::kMaxTransactionsAmount) {
    error_code = error_code::kRefillListIsFull;
  }
  if (!error_code) {
    TransactionData new_transaction =
        parameters.GetReplenishmentsList().transactions_data_[refill_amount];

    error_code =
        utility::SetTransactionType(new_transaction, TransactionType::kRefill);
    if (!error_code) {
      error_code = utility::SetTransactionDate(new_transaction, raw_date);
    }
    if (!error_code) {
      error_code = utility::SetTransactionInterval(new_transaction, interval);
    }
    if (!error_code) {
      error_code = utility::SetTransactionValue(new_transaction, value);
    }

    parameters.GetReplenishmentsList().transactions_data_.insert(
        parameters.GetReplenishmentsList().transactions_data_.end(),
        new_transaction);

    parameters.GetReplenishmentsList().transactions_amount_++;
  }

  return error_code;
}

int Parameters::AddPartialWithdrawalTransaction(double value, RawDate raw_date,
                                                IntervalType interval) {
  int error_code = error_code::kNoError;
  int &withdrawal_amount = GetPartialWithdrawalsListNextIndex();

  if (withdrawal_amount >= constants::kMaxTransactionsAmount) {
    error_code = error_code::kPartialWithdrawalListIsFull;
  }
  if (!error_code) {
    TransactionData new_transaction =
        GetPartialWithdrawalsList().transactions_data_[withdrawal_amount];

    error_code = utility::SetTransactionType(new_transaction,
                                             TransactionType::kWithdraw);
    if (!error_code) {
      error_code = utility::SetTransactionDate(new_transaction, raw_date);
    }
    if (!error_code) {
      error_code = utility::SetTransactionInterval(new_transaction, interval);
    }
    if (!error_code) {
      error_code = utility::SetTransactionValue(new_transaction, value);
    }

    GetPartialWithdrawalsList().transactions_data_.insert(
        GetPartialWithdrawalsList().transactions_data_.end(), new_transaction);

    GetPartialWithdrawalsList().transactions_amount_++;
  }

  return error_code;
}

int Parameters::AddPartialWithdrawalTransactionStatic(Parameters &parameters,
                                                      double value,
                                                      RawDate raw_date,
                                                      IntervalType interval) {
  int error_code = error_code::kNoError;
  int &withdrawal_amount = parameters.GetPartialWithdrawalsListNextIndex();

  if (withdrawal_amount >= constants::kMaxTransactionsAmount) {
    error_code = error_code::kPartialWithdrawalListIsFull;
  }
  if (!error_code) {
    TransactionData new_transaction =
        parameters.GetPartialWithdrawalsList()
            .transactions_data_[withdrawal_amount];

    error_code = utility::SetTransactionType(new_transaction,
                                             TransactionType::kWithdraw);
    if (!error_code) {
      error_code = utility::SetTransactionDate(new_transaction, raw_date);
    }
    if (!error_code) {
      error_code = utility::SetTransactionInterval(new_transaction, interval);
    }
    if (!error_code) {
      error_code = utility::SetTransactionValue(new_transaction, value);
    }

    parameters.GetPartialWithdrawalsList().transactions_data_.insert(
        parameters.GetPartialWithdrawalsList().transactions_data_.end(),
        new_transaction);

    parameters.GetPartialWithdrawalsList().transactions_amount_++;
  }

  return error_code;
}

int Parameters::AddInterestRate(InterestRateType type, double aggregated_value,
                                double interest_rate) {
  int error_code = error_code::kNoError;
  int &index = interest_rate_.interest_rate_amount_;

  if (index >= constants::kMaxInterestRateAmount) {
    error_code = error_code::kInterestListIsFull;
  }
  if (!error_code) {
    auto iter = interest_rate_.interest_rate_data_.end();
    InterestRateDataType interest_rate_data_type{};
    interest_rate_data_type.type_ = type;
    interest_rate_data_type.aggregated_value_ = aggregated_value;
    interest_rate_data_type.interest_rate_ = interest_rate;
    interest_rate_.interest_rate_data_.insert(iter, interest_rate_data_type);
    index++;
  }
  return error_code;
}

int Parameters::SetTax(const double &tax_value) {
  int error_code = error_code::kNoError;

  if (tax_value < constants::kMinTaxValue) {
    error_code = error_code::kValueForTaxIsTooSmall;
  } else if (tax_value >= constants::kMaxTaxValue) {
    error_code = error_code::kValueForTaxIsTooGreat;
  }

  if (!error_code) {
    tax_rate_ = tax_value;
  }

  return error_code;
}

[[nodiscard]] double &Parameters::GetTax() { return tax_rate_; }

[[nodiscard]] DateType &Parameters::GetStartDate() { return dates_.start_; }

[[nodiscard]] DateType &Parameters::GetFinishDate() { return dates_.finish_; }

int &Parameters::GetReplenishmentsListNextIndex() {
  return deposit_transactions_.replenishments_list_.transactions_amount_;
}

int &Parameters::GetPartialWithdrawalsListNextIndex() {
  return deposit_transactions_.partial_withdrawals_list_.transactions_amount_;
}

TransactionsDataType &Parameters::GetReplenishmentsList() {
  return deposit_transactions_.replenishments_list_;
}

TransactionsDataType &Parameters::GetPartialWithdrawalsList() {
  return deposit_transactions_.partial_withdrawals_list_;
}

[[nodiscard]] IntervalType &Parameters::GetPeriodicityOfPayments() {
  return periodicity_of_payments_;
}

[[nodiscard]] DepositTransactions &Parameters::GetDepositTransactions() {
  return deposit_transactions_;
}

[[nodiscard]] TransactionsDataType &Parameters::GetReplenishmentList() {
  return deposit_transactions_.replenishments_list_;
}

[[nodiscard]] TransactionsDataType &Parameters::GetPartialWithdrawalList() {
  return deposit_transactions_.partial_withdrawals_list_;
}

[[nodiscard]] InterestRateData &Parameters::GetInterestRate() {
  return interest_rate_;
}

[[nodiscard]] double &Parameters::GetAmount() { return deposit_amount_; }

[[nodiscard]] double &Parameters::GetInterestValue() { return interest_value_; }

[[nodiscard]] CapitalisationStatus &Parameters::GetCapitalisationStatus() {
  return capitalisation_status_;
}

[[nodiscard]] double &Parameters::GetMinimalBalance() {
  return minimal_balance_;
}

[[nodiscard]] double &Parameters::GetDepositAmount() { return deposit_amount_; }

void Parameters::InitInterestRate() {
  interest_rate_.interest_rate_data_.clear();
  interest_rate_.interest_rate_amount_ = constants::kInitValue;
}

void Parameters::InitDepositAmount() {
  deposit_amount_ = constants::kInitDepositAmountValue;
}

void Parameters::InitDepositPostingPeriod() {
  deposit_period_.deposit_posting_period_ =
      constants::kInitDepositPostingPeriodValue;
}

void Parameters::InitDepositDate() {
  std::time_t now = std::time(nullptr);
  std::tm *currentTime = std::localtime(&now);
  dates_.start_ = *currentTime;
}

void Parameters::InitDepositFinishDate() {
  dates_.finish_ = constants::kInitDate;
}

void Parameters::InitDepositTerm() {
  deposit_period_.deposit_term_ = TermType::kNone;
}

void Parameters::InitPeriodicityOfPayments() {
  periodicity_of_payments_ = IntervalType::kNone;
}

void Parameters::InitInterestValue() {
  interest_value_ = constants::kInitValue;
}

void Parameters::InitCapitalisationStatus() {
  capitalisation_status_ = data_types::CapitalisationStatus::kNone;
}

void Parameters::InitReplenishmentsList() {
  deposit_transactions_.replenishments_list_.transactions_data_.clear();
  deposit_transactions_.replenishments_list_.transactions_amount_ =
      constants::kInitValue;
}

void Parameters::InitPartialWithdrawalsList() {
  deposit_transactions_.partial_withdrawals_list_.transactions_data_.clear();
  deposit_transactions_.partial_withdrawals_list_.transactions_amount_ =
      constants::kInitValue;
}

void Parameters::InitMinimalBalance() {
  minimal_balance_ = constants::kInitMinimalBalanceValue;
}

}  // namespace s21::deposit
