#include "utility.h"

void s21::utility::rounding::RoundValue(double &value, int round_value) {
  double round_payment = value;

  round_payment *= round_value;

  round_payment = floor(round_payment);

  round_payment /= round_value;

  value = round_payment;
}
