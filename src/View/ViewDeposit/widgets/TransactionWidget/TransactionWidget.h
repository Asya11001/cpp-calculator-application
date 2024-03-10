#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_TRANSACTION_WIDGET_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_TRANSACTION_WIDGET_H_

#include <QComboBox>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "../../../../Model/DepositCalculator/Parameters/Parameters.h"
#include "../../../common/constants.h"
#include "../../../common/error_code.h"
#include "../../../common/settings.h"
#include "../../../number_validator/number_validator.h"

namespace s21 {
class TransactionWidget : public QWidget {
  Q_OBJECT

  using IntervalType = deposit::data_types::IntervalType;
  using InterestRateType = deposit::data_types::InterestRateType;
  using TermType = deposit::data_types::TermType;
  using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
  using Parameters = deposit::Parameters;
  using RawDate = deposit::data_structs::RawDate;

 public:
  TransactionWidget(const QString &add_button_label,
                    const QString &remove_button_label,
                    QWidget *parent = nullptr);

  QVBoxLayout *GetLayout() const;

  virtual int SetTransactions(
      Parameters &parameters,
      std::function<void(Parameters &, double, RawDate, IntervalType)>
          add_transaction) const;

 public slots:

  void AddLayout();

  void RemoveLayout();

 private:
  QList<QHBoxLayout *> layouts_;
  QVBoxLayout *main_layout_;
  QHBoxLayout *button_layout_;
  QPushButton *add_button_;
  QPushButton *remove_button_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGETS_TRANSACTION_WIDGET_H_
