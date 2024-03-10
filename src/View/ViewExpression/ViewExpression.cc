#include "ViewExpression.h"

#include "View/common/error_code.h"
#include "View/common/settings.h"
#include "View/style_handler/style_handler.h"

namespace s21 {

ViewExpression::ViewExpression(Controller *controller, Ui::View *ui,
                               QWidget *parent)
    : controller_(controller), ui_(ui), parent_(parent) {
  Setup();
}

ViewExpression::~ViewExpression() = default;

void ViewExpression::Setup() {
  SetupNumberOperatorVariableButtons();
  SetupFunctionsButtons();
  SetupLineEditExpression();
  SetupLineEditVariable();
  SetupClearButton();
  SetupEqualButton();
}

void ViewExpression::SetupClearButton() {
  connect(ui_->push_button_clear, &QPushButton::clicked, this,
          &ViewExpression::HandleButtonClearClick);
}

void ViewExpression::SetupEqualButton() {
  connect(ui_->push_button_equals, &QPushButton::clicked, this,
          &ViewExpression::HandleButtonEqualsClick);
}

void ViewExpression::HandleInsertButtonClick() {
  auto *button = qobject_cast<QPushButton *>(sender());

  if (!button) return;

  QString button_text = button->text();

  bool is_function = button->property("is_function").toBool();

  QLineEdit *current_line_edit = ui_->line_edit_expression;

  if (!current_line_edit) {
    return;
  }

  if (is_function) {
    button_text += "(";
  }

  int cursor_pos = current_line_edit->cursorPosition();

  QString current_text = current_line_edit->text();

  current_text.insert(cursor_pos, button_text);

  current_line_edit->setText(current_text);

  current_line_edit->setCursorPosition(static_cast<int>(cursor_pos) +
                                       button_text.length());
}

void ViewExpression::SetupNumberOperatorVariableButtons() {
  QPushButton *numberOperatorVariableButtons[] = {
      ui_->push_button_0,
      ui_->push_button_1,
      ui_->push_button_2,
      ui_->push_button_3,
      ui_->push_button_4,
      ui_->push_button_5,
      ui_->push_button_6,
      ui_->push_button_7,
      ui_->push_button_8,
      ui_->push_button_9,
      ui_->push_button_plus,
      ui_->push_button_minus,
      ui_->push_button_multiply,
      ui_->push_button_divide,
      ui_->push_button_power,
      ui_->push_button_mod,
      ui_->push_button_parentheses_opened,
      ui_->push_button_parentheses_closed,
      ui_->push_button_dot,
      ui_->push_button_variable};

  int buttonsCount = sizeof(numberOperatorVariableButtons) /
                     sizeof(numberOperatorVariableButtons[0]);

  for (int i = 0; i < buttonsCount; i++) {
    numberOperatorVariableButtons[i]->setProperty("is_function", 0);
    connect(numberOperatorVariableButtons[i], &QPushButton::clicked, this,
            &ViewExpression::HandleInsertButtonClick);
  }
}

void ViewExpression::SetupFunctionsButtons() {
  QPushButton *functionButtons[] = {
      ui_->push_button_cos,  ui_->push_button_sin,  ui_->push_button_tan,
      ui_->push_button_acos, ui_->push_button_asin, ui_->push_button_atan,
      ui_->push_button_sqrt, ui_->push_button_ln,   ui_->push_button_log};

  int buttonsCount = sizeof(functionButtons) / sizeof(functionButtons[0]);

  for (int i = 0; i < buttonsCount; i++) {
    functionButtons[i]->setProperty("is_function", 1);
    connect(functionButtons[i], &QPushButton::clicked, this,
            &ViewExpression::HandleInsertButtonClick);
  }
}

void ViewExpression::SetupLineEditExpression() {
  connect(ui_->line_edit_expression, &QLineEdit::returnPressed, this,
          &ViewExpression::HandleButtonEqualsClick);
  connect(ui_->line_edit_expression, &QLineEdit::textChanged, this,
          &ViewExpression::HandleTextChangedLineEdit);
}

void ViewExpression::SetupLineEditVariable() {
  connect(ui_->line_edit_variable, &QLineEdit::returnPressed, this,
          &ViewExpression::HandleButtonEqualsClick);
  connect(ui_->line_edit_variable, &QLineEdit::textChanged, this,
          &ViewExpression::HandleTextChangedVariable);
}

void ViewExpression::HandleButtonEqualsClick() {
  std::string expression_string{};
  expression_string = ui_->line_edit_expression->text().toStdString();

  int common_error_code = error_code::kNoError;
  int error_code = error_code::kNoError;
  double variable_value = 0;
  error_code = GetVariableValue(variable_value);

  if (error_code) {
    style_handler::SetIncorrectVariableLineEdit(ui_->line_edit_variable);
    settings::error_code_variable = error_code;
    common_error_code |= error_code;
  }

  controller_->ExpressionSetVariable(variable_value);
  error_code = controller_->ExpressionCalculate(expression_string);

  if (error_code) {
    style_handler::SetIncorrectExpressionLineEdit(ui_->line_edit_expression);
    settings::error_code_expression = error_code;
    common_error_code |= error_code;
  }
  if (!common_error_code) {
    double result = controller_->ExpressionGetResult();
    SwitchLastCalculationsResult(DoubleToSignificantString(result));
    style_handler::SetDefaultExpressionLineEdit(ui_->line_edit_expression);
  }
}

void ViewExpression::HandleButtonClearClick() {
  ui_->line_edit_expression->clear();
}

void ViewExpression::HandleTextChanged(QLineEdit *line_edit, int &error_code) {
  if (error_code) {
    if (line_edit == ui_->line_edit_expression) {
      style_handler::SetDefaultExpressionLineEdit(line_edit);
    } else if (line_edit == ui_->line_edit_variable) {
      style_handler::SetDefaultVariableLineEdit(line_edit);
    }
    error_code = error_code::kNoError;
  }
}

void ViewExpression::HandleTextChangedLineEdit(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_expression, settings::error_code_expression);
}

void ViewExpression::HandleTextChangedVariable(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_variable, settings::error_code_variable);
}

int ViewExpression::GetVariableValue(double &variable_value) {
  std::string expression_string{};
  expression_string = ui_->line_edit_variable->text().toStdString();

  int error_code = 0;

  if (expression_string.length() == 0) {
    error_code = error_code::kInvalidVariableFormat;
  }
  if (!error_code) {
    controller_->ExpressionSetVariable(0);
    error_code = controller_->ExpressionCalculate(expression_string);
  }
  if (!error_code) {
    variable_value = controller_->ExpressionGetResult();
  }

  return error_code;
}

QString ViewExpression::DoubleToSignificantString(const double &value) {
  QString string = QString::number(value, 'f', 15);
  bool is_dot_matched = false;

  if (string.contains('.')) {
    while ((string.endsWith('0') || string.endsWith('.')) && !is_dot_matched) {
      if (string.endsWith('.')) {
        string.chop(1);
        is_dot_matched = true;
      }
      if (!is_dot_matched) {
        string.chop(1);
      }
    }
  }

  return string;
}

void ViewExpression::SwitchLastCalculationsResult(
    const QString &current_result) {
  ui_->label_ante_penultimate_calculations->setText(
      ui_->label_penultimate_calculations->text());

  ui_->label_penultimate_calculations->setText(
      ui_->label_last_calculations->text());

  ui_->label_last_calculations->setText(current_result);
}
}  // namespace s21
