#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_INTEREST_RATE_WIDGET_INTERST_RATE_WIDGET_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_INTEREST_RATE_WIDGET_INTERST_RATE_WIDGET_H_

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "../../../../Model/DepositCalculator/Parameters/Parameters.h"
#include "../../../common/constants.h"
#include "../../../common/error_code.h"
#include "../../../common/settings.h"
#include "../../../number_validator/number_validator.h"

namespace s21 {
struct InterestRate {
  QString value1{};
  QString value2{};
  QString comboBoxValue{};

  InterestRate(const QString &v1, const QString &v2, const QString &comboValue)
      : value1(v1), value2(v2), comboBoxValue(comboValue) {}
};

class InterestRateWidget : public QWidget {
  Q_OBJECT

  using IntervalType = deposit::data_types::IntervalType;
  using InterestRateType = deposit::data_types::InterestRateType;
  using TermType = deposit::data_types::TermType;
  using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
  using Parameters = deposit::Parameters;

 public:
  InterestRateWidget(QWidget *parent = nullptr);

  int IsEmptyInterestRate(Parameters &parameters, const int &error_code) const;

  QVBoxLayout *GetLayout() const;

  int SetInterestRates(Parameters &parameters) const;

 public slots:

  void AddLayout();

  void RemoveLayout();

 private:
  QVBoxLayout *main_layout_;
  QHBoxLayout *button_layout_;
  QPushButton *add_button_;
  QPushButton *remove_button_;
  QList<QHBoxLayout *> layouts_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_INTEREST_RATE_WIDGET_INTERST_RATE_WIDGET_H_
