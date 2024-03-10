#include "Calculator.h"

namespace s21::deposit {

double Calculator::FromTransactionDateTypeToValue(
    TransactionDateType &transaction) {
  double result_value = transaction.value_;

  if (transaction.transaction_type_ == TransactionType::kWithdraw) {
    utility::NegateDouble(result_value);
  }
  return result_value;
}

double Calculator::GetBalanceChangesForDate(DateType last_day,
                                            TransactionList &transaction_list,
                                            int &transaction_index) {
  double balance_changes = constants::kInitValueDouble;

  TransactionDateType &transaction = transaction_list[transaction_index];

  while (utility::AreDatesEqual(last_day, transaction.date_)) {
    transaction_index++;

    balance_changes += FromTransactionDateTypeToValue(transaction);

    transaction = transaction_list[transaction_index];
  }

  return balance_changes;
}

int Calculator::FindFixInterestRate(
    const InterestRateData &interest_rate_data) {
  int length = interest_rate_data.interest_rate_amount_;
  int return_index = -1;

  for (int index = 0; index < length && return_index == -1; ++index) {
    InterestRateDataType interest_rate =
        interest_rate_data.interest_rate_data_[index];
    if (interest_rate.type_ == InterestRateType::kFixed) {
      return_index = index;
    }
  }

  return return_index;
}

double Calculator::GetInterestRateByIndex(
    const InterestRateData &interest_rate_data, int index) {
  double result = interest_rate_data.interest_rate_data_[index].interest_rate_;
  return result;
}

int Calculator::GetInterestValueFix(const InterestRateData &interest_rate_data,
                                    double &interest_rate) {
  int flag_found = constants::kFlagFalse;
  int index = FindFixInterestRate(interest_rate_data);

  if (index != 1) {
    interest_rate = GetInterestRateByIndex(interest_rate_data, index);

    flag_found = constants::kFlagTrue;
  }
  return flag_found;
}

double Calculator::GetCurrentInterestRateByIndex(
    const InterestRateData &interest_rate_data, int index) {
  double result =
      interest_rate_data.interest_rate_data_[index].aggregated_value_;
  return result;
}

int Calculator::IsSuitableInterestRate(
    bool is_aggregated_value_greater, int is_first_entry,
    double current_rate_value, const InterestRateData &interest_rate_data,
    int closest_index) {
  bool flag = (is_aggregated_value_greater && !is_first_entry &&
               current_rate_value >
                   interest_rate_data.interest_rate_data_[closest_index]
                       .aggregated_value_);
  return flag;
}

double Calculator::GetInterestRateAggregatedValue(
    const InterestRateData &interest_rate_data, int index) {
  return interest_rate_data.interest_rate_data_[index].aggregated_value_;
}

int Calculator::GetCurrentInterestValueIndexDependsOnAggregatedValue(
    const InterestRateData &interest_rate_data, double aggregated_value) {
  int closest_index = -1;

  for (int index = 0; index < interest_rate_data.interest_rate_amount_;
       ++index) {
    double current_rate_value =
        GetCurrentInterestRateByIndex(interest_rate_data, index);

    int is_aggregated_value_greater = aggregated_value > current_rate_value;

    int is_first_entry = closest_index == -1;

    if (is_aggregated_value_greater && is_first_entry) {
      closest_index = index;
    }

    if (IsSuitableInterestRate(is_aggregated_value_greater, is_first_entry,
                               current_rate_value, interest_rate_data,
                               closest_index)) {
      closest_index = index;
    }
  }
  for (int index = 0; index < interest_rate_data.interest_rate_amount_;
       ++index) {
    double current_rate_value =
        GetInterestRateAggregatedValue(interest_rate_data, index);
    double closest_rate_value =
        GetInterestRateAggregatedValue(interest_rate_data, index);

    int is_aggregated_value_greater_or_equals =
        aggregated_value >= current_rate_value;
    int is_closest_value = closest_rate_value < current_rate_value;

    if (is_aggregated_value_greater_or_equals && is_closest_value) {
      closest_index = index;
    }
  }

  return closest_index;
}

int Calculator::IsDependsOnDayIndexOrSum(InterestRateDataType data) {
  int flag = (data.type_ == InterestRateType::kDependsOnSum ||
              data.type_ == InterestRateType::kDependsOnDayIndex);
  return flag;
}

int Calculator::GetInterestValueDependsOnAggregatedValue(
    const InterestRateData &interest_rate_data, double &interest_rate,
    double aggregated_value) {
  int flag_found = constants::kFlagFalse;

  if (IsDependsOnDayIndexOrSum(interest_rate_data.interest_rate_data_[0])) {
    int current_rate_index =
        GetCurrentInterestValueIndexDependsOnAggregatedValue(interest_rate_data,
                                                             aggregated_value);

    interest_rate =
        GetInterestRateByIndex(interest_rate_data, current_rate_index);

    flag_found = constants::kFlagTrue;
  }

  return flag_found;
}

int Calculator::IsInterestRateDependsOnSum(const InterestRateDataType &data) {
  int flag = (data.type_ == data_types::InterestRateType::kDependsOnSum);
  return flag;
}

double Calculator::GetInterestRate(int day_index) {
  double interest_rate = constants::kInitValueDouble;

  double aggregated_value = day_index;
  if (IsInterestRateDependsOnSum(
          params_.GetInterestRate().interest_rate_data_[0])) {
    aggregated_value = params_.GetAmount();
  }

  GetInterestValueFix(params_.GetInterestRate(), interest_rate);

  GetInterestValueDependsOnAggregatedValue(params_.GetInterestRate(),
                                           interest_rate, aggregated_value);

  return interest_rate;
}

double Calculator::GetPayment(const DateType &last_day, const int &day_index) {
  double result_payment = constants::kInitValueDouble;
  double current_interest_rate = GetInterestRate(day_index);

  int days_in_previous_month = utility::GetDaysInPreviousMonth(last_day);

  double average_month_duration =
      utility::GetAverageMonthDurationInThisYear(last_day);

  double day_coefficient =
      GetDayCoefficient(current_interest_rate, days_in_previous_month);

  double actual_coefficient =
      GetNormalizedActualCoefficient(average_month_duration, day_coefficient);

  result_payment = GetResultPayment(actual_coefficient);

  utility::RoundValue(result_payment, constants::kRoundValue);

  return result_payment;
}

double Calculator::GetResultPayment(double actual_coefficient) {
  return params_.GetAmount() * (actual_coefficient);
}

double Calculator::GetNormalizedActualCoefficient(double average_month_duration,
                                                  double day_coefficient) {
  double actual_coefficient;
  if (params_.GetPeriodicityOfPayments() == IntervalType::kOneInDay) {
    actual_coefficient = day_coefficient;
  } else if (params_.GetPeriodicityOfPayments() == IntervalType::kOneInWeek) {
    actual_coefficient = day_coefficient * constants::kDaysInWeek;
  } else if (params_.GetPeriodicityOfPayments() ==
             IntervalType::kOneInQuarter) {
    actual_coefficient =
        day_coefficient * average_month_duration * constants::kMonthsInQuarter;
  } else if (params_.GetPeriodicityOfPayments() ==
             IntervalType::kOneInHalfYear) {
    actual_coefficient = day_coefficient * average_month_duration *
                         constants::kMonthsInHalfOfYear;
  } else if (params_.GetPeriodicityOfPayments() == IntervalType::kOneInYear) {
    actual_coefficient =
        day_coefficient * average_month_duration * constants::kMonthsInYear;
  } else if (params_.GetPeriodicityOfPayments() ==
             IntervalType::kAtTheEndOfInterval) {
    actual_coefficient = day_coefficient;
  } else {
    actual_coefficient = 1;
  }
  return actual_coefficient;
}

double Calculator::GetActualCoefficient(double month_result_coefficient,
                                        double month_coefficient) {
  return month_coefficient * month_result_coefficient;
}

double Calculator::GetMonthCoefficient(int days_in_previous_month,
                                       double day_coefficient) {
  return (day_coefficient * days_in_previous_month);
}

double Calculator::GetDayCoefficient(double current_interest_rate,
                                     int days_in_previous_month) {
  return (current_interest_rate /
          (100 * constants::kMonthsInYear * days_in_previous_month));
}

void Calculator::HandleLastPayment(double &payment_size,
                                   const PaymentDateArrayType &dates_payments,
                                   const int &payment_index) {
  if (dates_payments.number_of_records_ - 1 == payment_index) {
    payment_size *= dates_payments.last_coefficient_;
  }
}

int Calculator::HandlePaymentMatch(const PaymentDateArrayType &dates_payments,
                                   const DateType &current_day,
                                   int &payment_index, const int &day_index) {
  int handled_flag = constants::kFlagFalse;

  if (utility::AreDatesEqual(current_day,
                             dates_payments.date_array_[payment_index])) {
    double payment_size = 0;
    payment_index++;
    handled_flag = constants::kFlagTrue;

    payment_size = GetPayment(current_day, day_index);

    HandleLastPayment(payment_size, dates_payments, payment_index);

    params_.GetInterestValue() += payment_size;

    if (params_.GetCapitalisationStatus() ==
        data_types::CapitalisationStatus::kOn) {
      params_.GetAmount() += payment_size;
    }

    logger::Logging(params_, current_day, payment_size, LogType::kPayment);

    result_.GetIntermediateResults().last_annual_income_ += payment_size;
  }

  return handled_flag;
}

void Calculator::PerformTransactionChanging(const double &balance_changes,
                                            const DateType &current_day) {
  bool is_transaction_available =
      params_.GetAmount() + balance_changes >= params_.GetMinimalBalance();

  if (is_transaction_available) {
    params_.GetAmount() += balance_changes;
    logger::Logging(params_, current_day, balance_changes,
                    LogType::kBalanceChanging);
  } else {
    logger::Logging(params_, current_day, balance_changes,
                    LogType::kBalanceChangingImpossible);
  }
}

int Calculator::HandleTransactionMatch(TransactionList &transaction_list,
                                       DateType current_day,
                                       int &transaction_index) {
  int handled_flag = constants::kFlagFalse;
  if (transaction_list.empty()) {
    return handled_flag;
  }

  if (utility::AreDatesEqual(current_day,
                             transaction_list[transaction_index].date_)) {
    handled_flag = constants::kFlagTrue;

    double balance_changes = GetBalanceChangesForDate(
        current_day, transaction_list, transaction_index);
    PerformTransactionChanging(balance_changes, current_day);
    result_.GetIntermediateResults().deposit_changes_ += balance_changes;
  }

  return handled_flag;
}

int Calculator::HandlePaymentAtTheEndOfInterval(DateType current_day,
                                                int day_index) {
  int handled_flag = constants::kFlagFalse;

  if (params_.GetPeriodicityOfPayments() ==
      data_types::IntervalType::kAtTheEndOfInterval) {
    handled_flag = constants::kFlagTrue;
    double payment_size = GetPayment(current_day, day_index);
    params_.GetInterestValue() += payment_size;
  }

  return handled_flag;
}

int Calculator::IsPaymentPeriodicityAtTheEndOfInterval() {
  bool flag = params_.GetPeriodicityOfPayments() ==
              data_types::IntervalType::kAtTheEndOfInterval;
  return flag;
}

void Calculator::HandleLastPaymentCapitalisation(const int &error_code) {
  if (IsPaymentPeriodicityAtTheEndOfInterval() && !error_code) {
    if (params_.GetCapitalisationStatus() ==
        data_types::CapitalisationStatus::kOn) {
      params_.GetAmount() += params_.GetInterestValue();
    }
    logger::Logging(params_, params_.GetFinishDate(),
                    params_.GetInterestValue(), LogType::kPayment);
  }
}

int Calculator::HandleDepositCalculations(TransactionList &transaction_list) {
  int error_code = error_code::kNoError;

  PaymentDateArrayType dates_payments{0};
  DateType current_day = params_.GetStartDate();

  DateType last_day = current_day;

  int payment_index = 0;
  int transaction_index = 0;

  int deposit_duration = 0;

  error_code = utility::GetDayDifference(
      params_.GetFinishDate(), params_.GetStartDate(), deposit_duration);

  if (!error_code) {
    MakeAllTransactions(dates_payments, transaction_list);
  }

  for (int day_index = 0; day_index < deposit_duration + 2 && !error_code;
       ++day_index) {
    if (!HandlePaymentAtTheEndOfInterval(current_day, day_index)) {
      HandlePaymentMatch(dates_payments, current_day, payment_index, day_index);

      HandleTransactionMatch(transaction_list, current_day, transaction_index);
    }

    taxes::HandleTaxes(params_, result_, last_day, current_day);

    last_day = current_day;

    utility::AddIntervalToTheDate(IntervalType::kOneInDay, current_day,
                                  current_day);
  }

  HandleLastPaymentCapitalisation(error_code);

  return error_code;
}

void Calculator::SetFinishDate() {
  DateType deposit_end = params_.GetStartDate();

  int depositPostingPeriod = params_.GetDepositPeriod().deposit_posting_period_;

  if (params_.GetDepositPeriod().deposit_term_ == TermType::kDays) {
    deposit_end.tm_mday += depositPostingPeriod;
  } else if (params_.GetDepositPeriod().deposit_term_ == TermType::kMonths) {
    deposit_end.tm_mon += depositPostingPeriod;
  } else if (params_.GetDepositPeriod().deposit_term_ == TermType::kYears) {
    deposit_end.tm_year += depositPostingPeriod;
  }

  mktime(&deposit_end);
  utility::CopyDate(params_.GetFinishDate(), deposit_end);
}

void Calculator::AdjustParameters() { SetFinishDate(); }

void Calculator::SetParameters(const Parameters &parameters) {
  ClearMembers();
  params_ = parameters;
  AdjustParameters();
}

[[nodiscard]] Result Calculator::GetResult() const { return result_; }

int Calculator::Calculate() {
  TransactionList transaction_list{};

  int error_code = HandleDepositCalculations(transaction_list);

  result_.GetTotalDeposit() = params_.GetAmount();
  if (params_.GetCapitalisationStatus() == CapitalisationStatus::kOff) {
    result_.GetTotalDeposit() += result_.GetAllYearsIncome();
  }
  return error_code;
}

void Calculator::ClearMembers() {
  ClearParameters();
  ClearResult();
}

void Calculator::ClearParameters() { params_.Init(); }

void Calculator::ClearResult() { result_.Init(); }
}  // namespace s21::deposit