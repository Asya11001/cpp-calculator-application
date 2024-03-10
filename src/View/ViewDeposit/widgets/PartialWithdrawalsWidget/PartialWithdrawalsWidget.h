#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_H_

#include "../TransactionWidget/TransactionWidget.h"
#include "Model/DepositCalculator/Parameters/Parameters.h"

namespace s21 {
class PartialWithdrawalsWidget : public TransactionWidget {
  Q_OBJECT

  using Parameters = deposit::Parameters;

 public:
  PartialWithdrawalsWidget(QWidget *parent = nullptr);

  int SetTransactions(Parameters &depositParams) const;
};

}  // namespace s21
#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_DEPOSIT_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_PARTIAL_WITHDRAWALS_WIDGET_H_
