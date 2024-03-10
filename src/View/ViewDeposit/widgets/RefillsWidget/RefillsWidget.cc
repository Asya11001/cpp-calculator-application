#include "RefillsWidget.h"

namespace s21 {
using Parameters = deposit::Parameters;
RefillsWidget::RefillsWidget(QWidget *parent)
    : TransactionWidget("Add refill", "Remove refill", parent) {}

int RefillsWidget::SetTransactions(Parameters &parameters) const {
  return TransactionWidget::SetTransactions(
      parameters, Parameters::AddRefillTransactionStatic);
}

}  // namespace s21
