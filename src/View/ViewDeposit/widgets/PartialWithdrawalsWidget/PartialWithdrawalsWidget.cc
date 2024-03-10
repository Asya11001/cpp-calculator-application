#include "PartialWithdrawalsWidget.h"

namespace s21 {

using Parameters = deposit::Parameters;

PartialWithdrawalsWidget::PartialWithdrawalsWidget(QWidget *parent)
    : TransactionWidget("Add withdrawal", "Remove withdrawal", parent) {}

int PartialWithdrawalsWidget::SetTransactions(Parameters &parameters) const {
  return TransactionWidget::SetTransactions(
      parameters, Parameters::AddPartialWithdrawalTransactionStatic);
}

}  // namespace s21