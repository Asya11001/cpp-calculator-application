#include "number_validator.h"

namespace s21::number_validator {
bool IsDoubleNumber(const QString &input) {
  QRegularExpression pattern("^[-+]?[0-9]*\\.?[0-9]+$");

  QRegularExpressionMatch match = pattern.match(input);

  return match.hasMatch() && match.captured(0) == input;
}

bool IsIntNumber(const QString &input) {
  QRegularExpression pattern("^[-+]?\\d+$");

  QRegularExpressionMatch match = pattern.match(input);

  return match.hasMatch() && match.captured(0) == input;
}
}  // namespace s21::number_validator