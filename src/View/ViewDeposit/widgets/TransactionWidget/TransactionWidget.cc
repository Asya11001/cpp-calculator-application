#include "TransactionWidget.h"

#include "../../ViewDeposit.h"
#include "View/style_handler/style_handler.h"

namespace s21 {

using IntervalType = deposit::data_types::IntervalType;
using InterestRateType = deposit::data_types::InterestRateType;
using TermType = deposit::data_types::TermType;
using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
using Parameters = deposit::Parameters;
using RawDate = deposit::data_structs::RawDate;

TransactionWidget::TransactionWidget(const QString &addButtonLabel,
                                     const QString &removeButtonLabel,
                                     QWidget *parent)
    : QWidget(parent) {
  main_layout_ = new QVBoxLayout(this);

  button_layout_ = new QHBoxLayout();

  add_button_ = new QPushButton(addButtonLabel, this);
  remove_button_ = new QPushButton(removeButtonLabel, this);

  QPushButton *buttons[] = {add_button_, remove_button_};

  for (int i = 0; i < 2; i++) {
    buttons[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttons[i]->setFixedSize(120, 14);
    style_handler::SetDefaultPushButtonWidget(buttons[i]);
  }

  connect(add_button_, &QPushButton::clicked, this,
          &TransactionWidget::AddLayout);
  connect(remove_button_, &QPushButton::clicked, this,
          &TransactionWidget::RemoveLayout);

  remove_button_->setEnabled(false);

  button_layout_->addWidget(add_button_);
  button_layout_->addWidget(remove_button_);

  main_layout_->addLayout(button_layout_);
}

QVBoxLayout *TransactionWidget::GetLayout() const { return main_layout_; }

void TransactionWidget::AddLayout() {
  button_layout_->setSizeConstraint(QLayout::SetFixedSize);

  QHBoxLayout *layout = new QHBoxLayout;

  QComboBox *combo_box = new QComboBox();
  QDateEdit *transaction_date = new QDateEdit();
  QLineEdit *transaction_amount = new QLineEdit();

  combo_box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  transaction_date->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  transaction_amount->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  transaction_amount->setMaxLength(25);

  combo_box->setFixedSize(90, 14);
  transaction_date->setFixedSize(55, 14);
  transaction_amount->setFixedSize(90, 14);

  transaction_date->setButtonSymbols(QAbstractSpinBox::NoButtons);
  style_handler::SetDefaultDateEditWidget(transaction_date);

  QDate date = QDate::currentDate();
  transaction_date->setDate(date);

  connect(transaction_amount, &QLineEdit::textChanged, [=]() {
    style_handler::SetDefaultLineEditWidget(transaction_amount);  // TODO look
  });

  style_handler::SetDefaultLineEditWidget(transaction_amount);  // TODO look

  combo_box->addItems({"Once", "One in month", "One in two months",
                       "One in quarter", "One in half of year", "One in year"});
  combo_box->setCurrentIndex(1);

  style_handler::SetDefaultWidgetComboBox(combo_box);

  layout->addWidget(combo_box);
  layout->addWidget(transaction_date);
  layout->addWidget(transaction_amount);

  layouts_.append(layout);
  main_layout_->addLayout(layout);

  transaction_amount->setFocus();

  remove_button_->setEnabled(true);

  if (layouts_.length() > 2) {
    add_button_->setEnabled(false);
    button_layout_->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

void TransactionWidget::RemoveLayout() {
  if (!layouts_.isEmpty()) {
    QLayout *layout = layouts_.takeLast();

    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
      QWidget *widget = item->widget();
      if (widget) {
        widget->hide();
        delete widget;
      }
      delete item;
    }
    main_layout_->removeItem(layout);
    delete layout;

    if (layouts_.isEmpty()) {
      remove_button_->setEnabled(false);

      button_layout_->setSizeConstraint(QLayout::SetDefaultConstraint);
    }
  }
  if (layouts_.length() < 3) {
    add_button_->setEnabled(true);
    button_layout_->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

int TransactionWidget::SetTransactions(
    Parameters &parameters,
    std::function<void(Parameters &, double, RawDate, IntervalType)>
        add_transaction) const {
  int error_code = error_code::kNoError;
  int return_error_code = error_code::kNoError;

  for (const QHBoxLayout *layout : layouts_) {
    auto *transaction_periodicity_element =
        qobject_cast<QComboBox *>(layout->itemAt(0)->widget());
    auto *transaction_date_element =
        qobject_cast<QDateEdit *>(layout->itemAt(1)->widget());
    auto *transaction_amount_element =
        qobject_cast<QLineEdit *>(layout->itemAt(2)->widget());

    if (!transaction_periodicity_element || !transaction_date_element ||
        !transaction_amount_element) {
      error_code = error_code::kUnableToFindChildren;
    }

    if (!error_code) {
      QString transaction_periodicity_string =
          transaction_periodicity_element->currentText();
      QDate transactionDate = transaction_date_element->date();
      RawDate raw_date = {transactionDate.day(), transactionDate.month() - 1,
                          transactionDate.year()};
      QString transactionAmount = transaction_amount_element->text();

      if (!number_validator::IsDoubleNumber(transactionAmount)) {
        error_code = error_code::kIncorrectTransactionValue;
        style_handler::SetIncorrectLineEditWidget(transaction_amount_element);
      }

      if (!error_code) {
        double transaction_amount_value = transactionAmount.toDouble();
        bool is_amount_fine =
            (transaction_amount_value < constants::kMinTransactionAmountValue ||
             transaction_amount_value > constants::kMaxTransactionAmountValue);
        if (is_amount_fine) {
          error_code = error_code::kIncorrectTransactionValue;
          style_handler::SetIncorrectLineEditWidget(transaction_amount_element);
        } else {
          IntervalType interval =
              ViewDeposit::GetIntervalType(transaction_periodicity_string);
          add_transaction(parameters, transaction_amount_value, raw_date,
                          interval);
        }
      }
    }
    return_error_code |= error_code;
  }

  return return_error_code;
}

}  // namespace s21
