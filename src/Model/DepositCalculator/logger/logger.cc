#include "logger.h"

#include <ostream>

namespace s21::deposit::logger {

void WriteFileOperation(DateType date, double accrued_interest_value,
                        double refill_value, double deposit_actual_value) {
  FILE *file_ptr = fopen(kFileLogName, "a+");
  fprintf(file_ptr, "%d.%d.%d", date.tm_mday, date.tm_mon, date.tm_year);
  fprintf(file_ptr, "%30lf", accrued_interest_value);
  fprintf(file_ptr, "%+30lf", refill_value);
  fprintf(file_ptr, "%30lf\n", deposit_actual_value);
  fclose(file_ptr);
}

void ClearLogFile() {
  FILE *file_ptr = fopen(kFileLogName, "w+");
  fclose(file_ptr);
}

void FromDoubleToString(char *string, double value) {
  sprintf(string, "%+.2lf", value);
}

void FinishLogFile(Result &result) {
  FILE *fPtr = fopen(kFileLogName, "a+");

  char all_years_income_string[128] = {'\0'};
  char deposit_balance_string[128] = {'\0'};

  FromDoubleToString(all_years_income_string, result.GetAllYearsIncome());
  FromDoubleToString(deposit_balance_string, result.GetTotalDeposit());

  fprintf(fPtr, "%s%30s%25s%19s\n", "Summary: ", all_years_income_string, "",
          deposit_balance_string);

  fclose(fPtr);
}

void ClearTaxesLogFile() {
  FILE *file_ptr = fopen(kFileTaxesLogName, "w+");
  fclose(file_ptr);
}

void PrintDateInStringHuman(char *string_dest, DateType date) {
  snprintf(string_dest, 128 - 1, "[%02d.%02d.%d]", date.tm_mday,
           date.tm_mon + 1, date.tm_year + 1900);
}

void WriteImpossibleWithdraw(char *string, double value_1, double value_2) {
  sprintf(string,
          "Withdraw in size %.2lf is impossible - minimal balance (%.2lf)",
          fabs(value_1), value_2);
}

void FromYearToString(char *string, int value) {
  sprintf(string, "%d", value + 1900);
}

void FromYearToDeadlineString(char *string, int value) {
  sprintf(string, "1 December %d", value + 1 + 1900);
}

void WriteEmptyDash(char *string) { sprintf(string, "–"); }

void Logging(Parameters &parameters, DateType current_date,
             double aggregated_value, LogType log_type) {
  char date_string[128] = {'\0'};
  char payment_string[128] = {'\0'};
  char balance_changing_string[128] = {'\0'};
  char deposit_balance_string[128] = {'\0'};

  PrintDateInStringHuman(date_string, current_date);

  if (log_type == LogType::kPayment) {
    FromDoubleToString(payment_string, aggregated_value);
  } else {
    WriteEmptyDash(payment_string);
  }

  if (log_type == LogType::kBalanceChanging) {
    FromDoubleToString(balance_changing_string, aggregated_value);
  } else {
    WriteEmptyDash(balance_changing_string);
  }

  if (log_type == LogType::kBalanceChanging) {
    FromDoubleToString(deposit_balance_string, parameters.GetAmount());
  } else if (log_type == LogType::kBalanceChangingImpossible) {
    WriteImpossibleWithdraw(balance_changing_string, aggregated_value,
                            parameters.GetMinimalBalance());
  } else {
    WriteEmptyDash(balance_changing_string);
  }

  FILE *file_ptr = fopen(kFileLogName, "a+");
  fprintf(file_ptr, "%s%25s%25s%25s\n", date_string, payment_string,
          balance_changing_string, deposit_balance_string);

  fclose(file_ptr);
}

void TaxesLogging(const int &year, Result &result,
                  const TaxesLogStatus &log_status) {
  char year_string[128] = {'\0'};
  char income_string[128] = {'\0'};
  char tax_deduction_string[128] = {'\0'};
  char income_after_deduction_string[128] = {'\0'};
  char tax_amount_string[128] = {'\0'};
  char deadline_string[128] = {'\0'};

  FromYearToString(year_string, year);

  FromDoubleToString(income_string,
                     result.GetIntermediateResults().last_annual_income_);

  FromDoubleToString(tax_deduction_string,
                     result.GetIntermediateResults().tax_deduction_);

  if (log_status == TaxesLogStatus::kYes) {
    FromDoubleToString(income_after_deduction_string,
                       result.GetIntermediateResults().income_after_deduction_);

    FromDoubleToString(tax_amount_string,
                       result.GetIntermediateResults().tax_amount_);

    FromYearToDeadlineString(deadline_string, year);

  } else {
    FromDoubleToString(income_after_deduction_string, 0);
    FromDoubleToString(tax_amount_string, 0);
  }

  FILE *file_ptr = fopen(kFileTaxesLogName, "a+");

  fprintf(file_ptr, "%s%25s%25s%25s%25s%25s\n", year_string, income_string,
          tax_deduction_string, income_after_deduction_string,
          tax_amount_string, deadline_string);

  fclose(file_ptr);
}

}  // namespace s21::deposit::logger