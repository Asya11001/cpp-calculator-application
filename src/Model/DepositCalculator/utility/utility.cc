#include "utility.h"

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

void RoundValue(double &value, int round_value) {
  double round_payment = value;

  round_payment *= round_value;

  round_payment = floor(round_payment);

  round_payment /= round_value;

  value = round_payment;
}

void SwapTransactions(TransactionDateType &a, TransactionDateType &b) {
  TransactionDateType temp_date = a;
  a = b;
  b = temp_date;
}

int PartitionDates(TransactionList &array, int lowest_index,
                   int highest_index) {
  TransactionDateType pivot = array[highest_index];

  int i = (lowest_index - 1);

  for (int j = lowest_index; j <= highest_index - 1; j++) {
    time_t timePivot = mktime(&pivot.date_);
    time_t timeElement = mktime(&array[j].date_);

    if (timeElement < timePivot) {
      i++;
      SwapTransactions(array[i], array[j]);
    }
  }

  SwapTransactions(array[i + 1], array[highest_index]);

  return (i + 1);
}

void QuickSortDates(TransactionList &transaction_list, int lowest_index,
                    int highest_index) {
  if (lowest_index < highest_index) {
    int pi = PartitionDates(transaction_list, lowest_index, highest_index);

    QuickSortDates(transaction_list, lowest_index, pi - 1);
    QuickSortDates(transaction_list, pi + 1, highest_index);
  }
}

int GetMaxValueForCurrentTermType(const TermType &term) {
  int max_value = 0;

  if (term == TermType::kDays) {
    max_value = constants::kMaxDepositPostingPeriodDaysValue;
  } else if (term == TermType::kMonths) {
    max_value = constants::kMaxDepositPostingPeriodMonthsValue;
  } else if (term == TermType::kYears) {
    max_value = constants::kMaxDepositPostingPeriodYearsValue;
  }

  return max_value;
}

void CopyDate(DateType &dest, const DateType &src) {
  dest.tm_mday = src.tm_mday;
  dest.tm_mon = src.tm_mon;
  dest.tm_year = src.tm_year;
}

[[nodiscard]] int IsNegativeDate(const RawDate &raw_date) {
  bool flag = (raw_date.day_ < constants::kMinValueInDate ||
               raw_date.month_ < constants::kMinValueInDate ||
               raw_date.year_ < constants::kMinValueInDate);
  return flag;
}

int AreDatesEqual(const DateType &date_1, const DateType &date_2) {
  bool flag =
      (date_1.tm_mday == date_2.tm_mday && date_1.tm_mon == date_2.tm_mon &&
       date_1.tm_year == date_2.tm_year);
  return flag;
}

int AreDatesNotEqual(const DateType &date_1, const DateType &date_2) {
  return !(utility::AreDatesEqual(date_1, date_2));
}

int IsDateValid(DateType date) {
  int error_code = error_code::kNoError;
  DateType date_copy{};

  CopyDate(date_copy, date);

  time_t time = std::mktime(&date_copy);

  DateType converted_date = *std::localtime(&time);

  if (time == constants::kMakeTimeError ||
      AreDatesNotEqual(date_copy, converted_date)) {
    error_code = error_code::kDateIsInvalid;
  }

  return error_code;
}

int SetDate(const RawDate &raw_date, DateType &date) {
  int error_code = error_code::kNoError;

  date.tm_mday = raw_date.day_;
  date.tm_mon = raw_date.month_;
  date.tm_year = raw_date.year_ - constants::kYearBase;

  if (!IsDateValid(date)) {
    error_code = IsDateValid(date);
  }

  return error_code;
}

void InitTransactionData(TransactionData &data) {
  data.transaction_type_ = TransactionType::kNone;
  data.value_ = constants::kInitTransactionValue;
  data.transaction_periodicity_ = IntervalType::kNone;
  data.transaction_date_ = constants::kInitDate;
}

int SetTransactionType(TransactionData &data, const TransactionType &type) {
  int error_code = error_code::kNoError;

  if (type == TransactionType::kNone) {
    error_code = error_code::kTransactionTypeIsNotSet;
  }
  if (!error_code) {
    data.transaction_type_ = type;
  }

  return error_code;
}

int SetTransactionDate(TransactionData &data, RawDate raw_date) {
  int error_code = error_code::kNoError;

  DateType result_date{};

  error_code = utility::SetDate(raw_date, result_date);

  if (!error_code) {
    data.transaction_date_ = result_date;
  }

  return error_code;
}

int SetTransactionInterval(TransactionData &data,
                           const IntervalType &interval) {
  int error_code = error_code::kNoError;

  bool is_transaction_interval = (interval == IntervalType::kAtOnce ||
                                  interval == IntervalType::kOneInMonth ||
                                  interval == IntervalType::kOneInTwoMonth ||
                                  interval == IntervalType::kOneInQuarter ||
                                  interval == IntervalType::kOneInHalfYear ||
                                  interval == IntervalType::kOneInYear);

  if (interval == data_types::IntervalType::kNone) {
    error_code = error_code::kIntervalTypeIsNotSet;
  } else if (!is_transaction_interval) {
    error_code = error_code::kIntervalTypeIsIncorrectForThisCase;
  }

  if (!error_code) {
    data.transaction_periodicity_ = interval;
  }

  return error_code;
}

int SetTransactionValue(TransactionData &data, const double &value) {
  int error_code = error_code::kNoError;

  if (value < constants::kMinTransactionAmountValue) {
    error_code = error_code::kValueForTransactionIsTooSmall;
  } else if (value > constants::kMaxTransactionAmountValue) {
    error_code = error_code::kValueForTransactionIsTooGreat;
  }

  if (!error_code) {
    data.value_ = value;
  }

  return error_code;
}

int GetDayDifference(DateType &date_1, DateType &date_2, int &day_difference) {
  int error_code = error_code::kNoError;

  time_t time1 = mktime(&date_1);
  time_t time2 = mktime(&date_2);

  if (time1 == constants::kMakeTimeError ||
      time2 == constants::kMakeTimeError) {
    error_code = error_code::kDateIsInvalid;
  }

  if (!error_code) {
    double difference_in_seconds = difftime(time1, time2);
    day_difference =
        static_cast<int>(difference_in_seconds / constants::kSecondsInDay);
  }

  return error_code;
}

int GetTransactionsCount(const TransactionsDataType &transactions_data) {
  return transactions_data.transactions_amount_;
}

void NegateDouble(double &value) { value *= (-1); }

void AddIntervalToTheDate(const IntervalType &interval, DateType &date,
                          const DateType previous_date) {
  if (interval == IntervalType::kOneInDay) {
    date.tm_mday = previous_date.tm_mday + 1;
  } else if (interval == IntervalType::kOneInWeek) {
    date.tm_mday = previous_date.tm_mday + constants::kDaysInWeek;
  } else if (interval == IntervalType::kOneInMonth) {
    date.tm_mon = previous_date.tm_mon + 1;
  } else if (interval == IntervalType::kOneInTwoMonth) {
    date.tm_mon = previous_date.tm_mon + 2;
  } else if (interval == IntervalType::kOneInQuarter) {
    date.tm_mon = previous_date.tm_mon + constants::kMonthsInQuarter;
  } else if (interval == IntervalType::kOneInHalfYear) {
    date.tm_mon = previous_date.tm_mon + constants::kMonthsInHalfOfYear;
  } else if (interval == IntervalType::kOneInYear) {
    date.tm_year = previous_date.tm_year + 1;
  } else if (interval == IntervalType::kAtOnce) {
    date.tm_year = previous_date.tm_year + constants::kYearBase;
  }

  mktime(&date);
}

bool IsValidIntervalForPeriodicityOfPayments(const IntervalType &interval) {
  bool flag = (interval == IntervalType::kAtTheEndOfInterval ||
               interval == IntervalType::kOneInDay ||
               interval == IntervalType::kOneInMonth ||
               interval == IntervalType::kOneInWeek ||
               interval == IntervalType::kOneInQuarter ||
               interval == IntervalType::kOneInHalfYear ||
               interval == IntervalType::kOneInYear);
  return flag;
}

double GetTimeDifference(const time_t &start_time, const time_t &finish_time) {
  double result =
      static_cast<double>(start_time) - static_cast<double>(finish_time);
  return result;
}

double CalculateCurrentCoefficient(double second_difference_last_finish,
                                   double second_difference_penultimate_last) {
  double result =
      (constants::kInitCoefficient -
       (second_difference_last_finish / second_difference_penultimate_last));
  return result;
}

int GetDaysInCurrentMonth(const DateType &date) {
  DateType start_month = date;
  DateType start_next_month = date;

  start_month.tm_mon = date.tm_mon;
  start_next_month.tm_mon = date.tm_mon + 1;

  int day_difference = constants::kZeroDays;

  GetDayDifference(start_next_month, start_month, day_difference);

  return day_difference;
}

int GetDaysInPreviousMonth(const DateType &date) {
  DateType start_month = date;
  DateType start_next_month = date;

  start_month.tm_mon = date.tm_mon - 1;
  start_next_month.tm_mon = date.tm_mon;

  int day_difference = constants::kZeroDays;

  GetDayDifference(start_next_month, start_month, day_difference);

  return day_difference;
}

int GetDaysInCurrentYear(const DateType &date) {
  DateType start_month = date;
  DateType start_next_month = date;

  start_month.tm_year = date.tm_year;
  start_next_month.tm_year = date.tm_year + 1;

  int day_difference = constants::kZeroDays;

  GetDayDifference(start_next_month, start_month, day_difference);

  return day_difference;
}

double GetAverageMonthDurationInThisYear(const DateType &date) {
  double average_month_duration = constants::kZeroDays;

  double days_in_year = GetDaysInCurrentYear(date);

  average_month_duration = days_in_year / constants::kMonthsInYear;

  return average_month_duration;
}

}  // namespace s21::deposit::utility
