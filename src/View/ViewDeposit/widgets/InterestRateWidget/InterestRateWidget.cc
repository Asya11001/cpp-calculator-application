#include "InterestRateWidget.h"

#include "../../ViewDeposit.h"
#include "View/style_handler/style_handler.h"

namespace s21 {

using IntervalType = deposit::data_types::IntervalType;
using InterestRateType = deposit::data_types::InterestRateType;
using TermType = deposit::data_types::TermType;
using CapitalisationStatus = deposit::data_types::CapitalisationStatus;
using Parameters = deposit::Parameters;

int InterestRateWidget::IsEmptyInterestRate(Parameters &parameters,
                                            const int &error_code) const {
  bool flag = parameters.GetInterestRate().interest_rate_amount_ ==
                  constants::kInitValueDouble &&
              !error_code;
  return flag;
}

InterestRateWidget::InterestRateWidget(QWidget *parent) : QWidget(parent) {
  main_layout_ = new QVBoxLayout(this);

  button_layout_ = new QHBoxLayout();

  add_button_ = new QPushButton("Add interest rate", this);
  remove_button_ = new QPushButton("Remove interest rate", this);

  QPushButton *buttons[] = {add_button_, remove_button_};
  for (auto &button : buttons) {
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setFixedSize(120, 14);
    style_handler::SetDefaultPushButtonWidget(button);
  }

  connect(add_button_, &QPushButton::clicked, this,
          &InterestRateWidget::AddLayout);
  connect(remove_button_, &QPushButton::clicked, this,
          &InterestRateWidget::RemoveLayout);

  connect(add_button_, &QPushButton::clicked,
          [=]() { style_handler::SetDefaultPushButtonWidget(add_button_); });

  remove_button_->setEnabled(false);

  button_layout_->addWidget(add_button_);
  button_layout_->addWidget(remove_button_);

  main_layout_->addLayout(button_layout_);
}

QVBoxLayout *InterestRateWidget::GetLayout() const { return main_layout_; }

int InterestRateWidget::SetInterestRates(Parameters &parameters) const {
  int error_code = error_code::kNoError;

  for (const QHBoxLayout *layout : layouts_) {
    error_code = error_code::kNoError;
    QLineEdit *line_edit_1 =
        qobject_cast<QLineEdit *>(layout->itemAt(0)->widget());
    QLineEdit *line_edit_2 =
        qobject_cast<QLineEdit *>(layout->itemAt(1)->widget());
    QComboBox *combo_box =
        qobject_cast<QComboBox *>(layout->itemAt(2)->widget());

    if (!line_edit_1 || !line_edit_2 || !combo_box) {
      error_code = error_code::kUnableToFindChildren;
    }
    if (!error_code) {
      QString interest_rate_string = line_edit_1->text();
      QString aggregated_value_string = line_edit_2->text();
      QString interest_rate_type_string = combo_box->currentText();

      if (!number_validator::IsDoubleNumber(interest_rate_string)) {
        error_code |= error_code::kIncorrectInterestValue;
        style_handler::SetIncorrectLineEditWidget(line_edit_1);
      }

      if (!number_validator::IsDoubleNumber(aggregated_value_string) &&
          ViewDeposit::GetInterestRate(interest_rate_type_string) !=
              InterestRateType::kFixed) {
        error_code |= error_code::kIncorrectInterestValue;
        style_handler::SetIncorrectLineEditWidget(line_edit_2);
      }
      if (interest_rate_string.toDouble() < 0) {
        error_code |= error_code::kIncorrectInterestValue;
        style_handler::SetIncorrectLineEditWidget(line_edit_1);
      }
      if (!error_code) {
        InterestRateType interest_rate_type =
            ViewDeposit::GetInterestRate(interest_rate_type_string);
        double interest_rate_aggregated_value =
            aggregated_value_string.toDouble();
        double interest_rate_value = interest_rate_string.toDouble();
        parameters.AddInterestRate(interest_rate_type,
                                   interest_rate_aggregated_value,
                                   interest_rate_value);
      }
    }
  }

  int is_empty_interest_rate = IsEmptyInterestRate(parameters, error_code);

  if (is_empty_interest_rate) {
    error_code = error_code::kZeroInterestRateAmount;
    style_handler::SetIncorrectPushButtonWidget(add_button_);
  }

  return error_code;
}

void InterestRateWidget::AddLayout() {
  button_layout_->setSizeConstraint(QLayout::SetFixedSize);

  QHBoxLayout *layout = new QHBoxLayout;

  QLineEdit *line_edit_interest_rate_ratio = new QLineEdit();
  QLineEdit *line_edit_aggregated_value = new QLineEdit();
  QComboBox *combo_box = new QComboBox();

  QLineEdit *line_edit_array[] = {line_edit_interest_rate_ratio,
                                  line_edit_aggregated_value};
  combo_box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  line_edit_interest_rate_ratio->setMaxLength(3);

  line_edit_interest_rate_ratio->setFixedSize(35, 14);
  line_edit_aggregated_value->setFixedSize(55, 14);

  connect(line_edit_interest_rate_ratio, &QLineEdit::textChanged, [=]() {
    style_handler::SetDefaultLineEditWidget(line_edit_interest_rate_ratio);
  });

  connect(line_edit_aggregated_value, &QLineEdit::textChanged, [=]() {
    style_handler::SetDefaultLineEditWidget(line_edit_aggregated_value);
  });

  combo_box->setFixedSize(85, 14);

  for (int i = 0; i < 2; i++) {
    line_edit_array[i]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    style_handler::SetDefaultLineEditWidget(line_edit_array[i]);
  }

  combo_box->addItems({"Fix", "Depends on sum", "Depends on day"});

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  connect(combo_box, &QComboBox::currentIndexChanged, this, [=]() {
    style_handler::SetDefaultLineEditWidget(line_edit_aggregated_value);
  });
#endif

  style_handler::SetDefaultWidgetComboBox(combo_box);

  layout->addWidget(line_edit_interest_rate_ratio);
  layout->addWidget(line_edit_aggregated_value);
  layout->addWidget(combo_box);

  layouts_.append(layout);
  main_layout_->addLayout(layout);

  line_edit_interest_rate_ratio->setFocus();

  remove_button_->setEnabled(true);

  if (layouts_.length() > 2) {
    add_button_->setEnabled(false);
    button_layout_->setSizeConstraint(QLayout::SetDefaultConstraint);
  }
}

void InterestRateWidget::RemoveLayout() {
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

}  // namespace s21