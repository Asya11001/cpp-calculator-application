#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_NUMBER_VALIDATOR_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_NUMBER_VALIDATOR_H_

#include <QRegularExpression>
#include <QString>

namespace s21::number_validator {
bool IsDoubleNumber(const QString &input);

bool IsIntNumber(const QString &input);
}  // namespace s21::number_validator

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_NUMBER_VALIDATOR_H_
