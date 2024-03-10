#include "BaseCalculator.h"

#include <ctime>

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

BaseCalculator::BaseCalculator() = default;

BaseCalculator::~BaseCalculator() = default;

int BaseCalculator::SetDepositAmount(double value) {
  int error_code = error_code::kNoError;

  if (value < constants::kMinDepositAmountValue) {
    error_code = error_code::kAmountIsNegativeNumber;
  } else if (value > constants::kMaxDepositAmountValue) {
    error_code = error_code::kAmountIsTooBig;
  }

  if (!error_code) {
    params_.SetDepositAmount(value);
  }

  return error_code;
}

int BaseCalculator::GetNumberOfRecordsInArrayOfPayments() {
  if (params_.GetPeriodicityOfPayments() == IntervalType::kAtTheEndOfInterval) {
    return constants::kOnePayment;
  }

  int number_of_records = 0;
  int day_difference = 0;

  int error_code = error_code::kNoError;

  if (!utility::IsValidIntervalForPeriodicityOfPayments(
          params_.GetPeriodicityOfPayments())) {
    error_code =
        error_code::kPeriodicityOfPaymentsIsIncorrectForPeriodicityOfPayments;
  }
  if (error_code) {
    return error_code;
  }

  DateType deposit_start = params_.GetStartDate();
  DateType deposit_intermediate = deposit_start;
  DateType deposit_end{};

  utility::CopyDate(deposit_end, params_.GetFinishDate());

  do {
    error_code = utility::GetDayDifference(deposit_end, deposit_intermediate,
                                           day_difference);

    if (day_difference >= 0 && !error_code) {
      number_of_records++;
    }
    if (!error_code) {
      utility::AddIntervalToTheDate(params_.GetPeriodicityOfPayments(),
                                    deposit_intermediate, deposit_intermediate);
    }

  } while (day_difference >= 0 || error_code);

  return number_of_records;
}

bool BaseCalculator::HandleOnePaymentCase(PaymentDateArrayType &date_array) {
  int number_of_records = GetNumberOfRecordsInArrayOfPayments();

  bool is_one_payment = (number_of_records == constants::kOnePayment);
  bool is_periodicity_in_the_end_of_interval =
      (params_.GetPeriodicityOfPayments() == IntervalType::kAtTheEndOfInterval);

  bool is_one_payment_case =
      (is_one_payment && is_periodicity_in_the_end_of_interval);

  if (is_one_payment_case) {
    date_array.number_of_records_ = constants::kOnePayment;
    date_array.last_coefficient_ = constants::kMaxCoefficient;
    utility::CopyDate(date_array.date_array_[0], params_.GetFinishDate());
  }

  return is_one_payment_case;
}

void BaseCalculator::HandleCoefficientForLastPayment(
    PaymentDateArrayType &date_array) {
  DateType last_date{};
  int number_of_records = GetNumberOfRecordsInArrayOfPayments();

  utility::CopyDate(last_date, date_array.date_array_[number_of_records - 1]);

  date_array.last_coefficient_ = constants::kMaxCoefficient;

  if (utility::AreDatesNotEqual(last_date, params_.GetFinishDate())) {
    DateType date_penultimate{};
    DateType date_last{};
    DateType date_finish_deposit{};

    if (number_of_records > 1) {
      utility::CopyDate(date_penultimate,
                        date_array.date_array_[number_of_records - 2]);
    } else {
      utility::CopyDate(date_penultimate, params_.GetStartDate());
    }

    utility::CopyDate(date_last, date_array.date_array_[number_of_records - 1]);
    utility::CopyDate(date_finish_deposit, params_.GetFinishDate());

    time_t timePenultimate = std::mktime(&date_penultimate);
    time_t timeLast = std::mktime(&date_last);
    time_t timeFinishDeposit = std::mktime(&date_finish_deposit);

    timeFinishDeposit -= timePenultimate;
    timeLast -= timePenultimate;
    timePenultimate -= timePenultimate;

    double secondDifferenceLastFinish =
        utility::GetTimeDifference(timeLast, timeFinishDeposit);
    double secondDifferencePenultimateLast =
        utility::GetTimeDifference(timeLast, timePenultimate);

    double coefficient = utility::CalculateCurrentCoefficient(
        secondDifferenceLastFinish, secondDifferencePenultimateLast);

    if (coefficient == constants::kMinCoefficient) {
      coefficient = constants::kMaxCoefficient;
    }

    date_array.last_coefficient_ = coefficient;

    utility::CopyDate(date_array.date_array_[number_of_records - 1],
                      params_.GetFinishDate());
    std::mktime(&date_array.date_array_[number_of_records - 1]);
  }
}

int BaseCalculator::MakeArrayOfPayments(PaymentDateArrayType &date_array) {
  int error_code = error_code::kNoError;

  int number_of_records = GetNumberOfRecordsInArrayOfPayments();

  bool is_one_payment_case = HandleOnePaymentCase(date_array);
  if (!is_one_payment_case) {
    date_array.number_of_records_ = number_of_records;

    DateType start_date{};
    DateType previous_record{};

    utility::CopyDate(start_date, params_.GetStartDate());

    date_array.date_array_.insert(date_array.date_array_.end(), start_date);
    utility::CopyDate(date_array.date_array_[0], start_date);

    utility::AddIntervalToTheDate(params_.GetPeriodicityOfPayments(),
                                  date_array.date_array_[0], start_date);

    for (int i = 1; i < number_of_records && !error_code; ++i) {
      date_array.date_array_.insert(date_array.date_array_.end(), start_date);

      utility::CopyDate(previous_record, date_array.date_array_[i - 1]);

      utility::CopyDate(date_array.date_array_[i], previous_record);

      utility::AddIntervalToTheDate(params_.GetPeriodicityOfPayments(),
                                    date_array.date_array_[i], previous_record);

      std::mktime(&date_array.date_array_[i]);
    }

    HandleCoefficientForLastPayment(date_array);
  }

  return error_code;
}

int BaseCalculator::GetNumberOfRecordsInTransactionsArray(
    const TransactionData &transaction_data) {
  int number_of_records = 0;
  int day_difference = 0;

  int error_code = error_code::kNoError;
  DateType transaction_start = transaction_data.transaction_date_;
  DateType deposit_intermediate = transaction_start;
  DateType deposit_end = params_.GetFinishDate();

  bool are_transaction_deposit_dates_equal =
      utility::AreDatesEqual(deposit_intermediate, params_.GetStartDate());

  if (are_transaction_deposit_dates_equal) {
    utility::AddIntervalToTheDate(transaction_data.transaction_periodicity_,
                                  deposit_intermediate, deposit_intermediate);
  }

  do {
    error_code = utility::GetDayDifference(deposit_end, deposit_intermediate,
                                           day_difference);

    if (day_difference > constants::kZeroDays && !error_code) {
      number_of_records++;
    }

    utility::AddIntervalToTheDate(transaction_data.transaction_periodicity_,
                                  deposit_intermediate, deposit_intermediate);

  } while (day_difference > constants::kZeroDays &&
           transaction_data.transaction_periodicity_ != IntervalType::kAtOnce &&
           !error_code);

  return number_of_records;
}

int BaseCalculator::MakeArrayOfTransactions(
    TransactionDateArray &date_array, const TransactionData &transaction_data) {
  int error_code = error_code::kNoError;

  int number_of_records =
      GetNumberOfRecordsInTransactionsArray(transaction_data);

  date_array.number_of_records_ = number_of_records;

  if (number_of_records > constants::kZeroDays) {
    DateType start_date{};
    DateType previous_record{};

    utility::CopyDate(start_date, transaction_data.transaction_date_);

    TransactionDateType init_value{};
    date_array.transaction_date_array_.insert(
        date_array.transaction_date_array_.end(), init_value);
    utility::CopyDate(date_array.transaction_date_array_[0].date_, start_date);

    date_array.transaction_date_array_[0].value_ = transaction_data.value_;

    if (utility::AreDatesEqual(date_array.transaction_date_array_[0].date_,
                               params_.GetStartDate())) {
      utility::AddIntervalToTheDate(transaction_data.transaction_periodicity_,
                                    date_array.transaction_date_array_[0].date_,
                                    start_date);
    }

    for (int i = 1; i < number_of_records; ++i) {
      date_array.transaction_date_array_.insert(
          date_array.transaction_date_array_.end(), init_value);

      utility::CopyDate(previous_record,
                        date_array.transaction_date_array_[i - 1].date_);

      utility::CopyDate(date_array.transaction_date_array_[i].date_,
                        previous_record);

      date_array.transaction_date_array_[i].value_ = transaction_data.value_;

      utility::AddIntervalToTheDate(transaction_data.transaction_periodicity_,
                                    date_array.transaction_date_array_[i].date_,
                                    previous_record);
    }
  }
  return error_code;
}

void BaseCalculator::SummarizeTransactions(
    TransactionList &transaction_list, TransactionDateArray &date_array,
    const TransactionType &transaction_type) {
  for (int i = 0; i < date_array.number_of_records_; ++i) {
    auto transaction = date_array.transaction_date_array_[i];
    transaction.transaction_type_ = transaction_type;

    transaction_list.insert(transaction_list.end(), transaction);
  }
}

int BaseCalculator::MakeAllTransactions(PaymentDateArrayType &dates_payments,
                                        TransactionList &transaction_list) {
  int error_code = error_code::kNoError;

  error_code = MakeArrayOfPayments(dates_payments);

  TransactionsDataType &replenishments_list = params_.GetReplenishmentsList();
  TransactionsDataType &partial_withdrawals_list =
      params_.GetPartialWithdrawalsList();

  int transactions_count = utility::GetTransactionsCount(replenishments_list);

  for (int i = 0; i < transactions_count && !error_code; ++i) {
    TransactionDateArray date_array{};
    date_array.transaction_date_array_.reserve(20000);

    error_code = MakeArrayOfTransactions(
        date_array, replenishments_list.transactions_data_[i]);
    if (!error_code) {
      SummarizeTransactions(transaction_list, date_array,
                            TransactionType::kRefill);
    }
  }

  transactions_count = utility::GetTransactionsCount(partial_withdrawals_list);

  for (int i = 0; i < transactions_count && !error_code; ++i) {
    TransactionDateArray date_array{};
    date_array.transaction_date_array_.reserve(20000);

    error_code = MakeArrayOfTransactions(
        date_array, partial_withdrawals_list.transactions_data_[i]);
    if (!error_code) {
      SummarizeTransactions(transaction_list, date_array,
                            TransactionType::kWithdraw);
    }
  }
  if (!error_code) {
    utility::QuickSortDates(transaction_list, 0,
                            static_cast<int>(transaction_list.size() - 1));
  }

  return error_code;
}

}  // namespace s21::deposit
