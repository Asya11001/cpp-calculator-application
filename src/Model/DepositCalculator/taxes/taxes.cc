#include "taxes.h"

#include "../common/constants.h"
#include "../logger/logger.h"

namespace s21::deposit::taxes {

double GetTaxPercentage(double tax_rate) {
  double result = tax_rate / 100;
  return result;
}

double GetTaxDeductionForYear(Parameters &parameters, int year) {
  int is_first_tax = IsFirstTaxForYear(parameters, year);

  double tax_deduction{0};

  if (is_first_tax) {
    tax_deduction = constants::kFirstFee;
  } else {
    tax_deduction = constants::kNonFirstFee;
  }

  return tax_deduction;
}

int IsFirstTaxForYear(Parameters &parameters, int year) {
  return parameters.GetStartDate().tm_year == year;
}

double CalculateTaxesFromAnnualInterestValue(Parameters &parameters,
                                             Result &result, int year) {
  double tax_percentage = GetTaxPercentage(parameters.GetTax());
  double interest_annual_income =
      result.GetIntermediateResults().last_annual_income_;
  double tax_deduction = GetTaxDeductionForYear(parameters, year);
  double income_after_deduction = interest_annual_income - tax_deduction;
  double tax_amount = income_after_deduction * tax_percentage;

  result.GetIntermediateResults().tax_deduction_ = tax_deduction;
  result.GetIntermediateResults().income_after_deduction_ =
      income_after_deduction;
  result.GetIntermediateResults().tax_amount_ = tax_amount;
  if (tax_amount > 0) {
    result.GetAllYearsTaxes() += tax_amount;
  }

  result.GetAllYearsIncome() += interest_annual_income;

  return tax_amount;
}

int HandleTaxes(Parameters &parameters, Result &result,
                const DateType &last_day, const DateType &current_day) {
  int flag_year_change = constants::kFlagFalse;
  int is_new_year_has_come = last_day.tm_year != current_day.tm_year;
  int is_the_end_of_deposit =
      utility::AreDatesEqual(last_day, parameters.GetFinishDate());

  if (is_new_year_has_come || is_the_end_of_deposit) {
    CalculateTaxesFromAnnualInterestValue(parameters, result, last_day.tm_year);

    double tax_amount = result.GetIntermediateResults().tax_amount_;

    if (tax_amount > 0) {
      logger::TaxesLogging(last_day.tm_year, result, LogStatus::kYes);
    } else {
      logger::TaxesLogging(last_day.tm_year, result, LogStatus::kNo);
    }

    flag_year_change = constants::kFlagTrue;
    result.GetIntermediateResults().last_annual_income_ =
        constants::kInitValueDouble;
  }

  return flag_year_change;
}

}  // namespace s21::deposit::taxes