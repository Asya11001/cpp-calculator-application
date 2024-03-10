#include "ViewGraph.h"

#include "../common/constants.h"
#include "../common/error_code.h"
#include "../common/settings.h"
#include "../style_handler/style_handler.h"

namespace s21 {
ViewGraph::ViewGraph(Controller *controller, Ui::View *ui, QWidget *parent)
    : controller_(controller), ui_(ui), parent_(parent) {
  Setup();
};

ViewGraph::~ViewGraph() = default;

void ViewGraph::Setup() {
  SetupDomains();
  SetupGraphLineEdit();
  SetupButtons();
  SetupGraph();
}

void ViewGraph::SetupDomains() {
  SetupDomain();
  SetupCodomain();
}

void ViewGraph::SetupDomain() {
  connect(ui_->line_edit_domain, &QLineEdit::returnPressed, this,
          &ViewGraph::HandleDrawPlot);
  connect(ui_->line_edit_domain, &QLineEdit::textChanged, this,
          &ViewGraph::HandleTextChangedDomain);
}

void ViewGraph::SetupCodomain() {
  connect(ui_->line_edit_codomain, &QLineEdit::returnPressed, this,
          &ViewGraph::HandleDrawPlot);
  connect(ui_->line_edit_codomain, &QLineEdit::textChanged, this,
          &ViewGraph::HandleTextChangedCodomain);
}

void ViewGraph::SetupGraphLineEdit() {
  connect(ui_->line_edit_graph_expression, &QLineEdit::returnPressed, this,
          &ViewGraph::HandleDrawPlot);
  connect(ui_->line_edit_graph_expression, &QLineEdit::textChanged, this,
          &ViewGraph::HandleTextChangedGraph);
}

void ViewGraph::SetupButtons() {
  SetupClearButton();
  SetupDrawButton();
}

void ViewGraph::SetupClearButton() {
  connect(ui_->push_button_graph_clear, &QPushButton::clicked, this,
          &ViewGraph::HandleClearButtonClick);
}

void ViewGraph::SetupDrawButton() {
  connect(ui_->push_button_graph_draw, &QPushButton::clicked, this,
          &ViewGraph::HandleDrawPlot);
}

void ViewGraph::HandleClearButtonClick() { ClearPlot(); }

void ViewGraph::HandleTextChanged(QLineEdit *line_edit, int &error_code) {
  if (error_code) {
    if (line_edit == ui_->line_edit_domain ||
        line_edit == ui_->line_edit_codomain) {
      style_handler::SetDefaultDomainLineEdit(line_edit);
    } else if (line_edit == ui_->line_edit_graph_expression) {
      style_handler::SetDefaultExpressionLineEdit(line_edit);
    }
    error_code = 0;
  }
}

void ViewGraph::HandleTextChangedGraph(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_graph_expression,
                    settings::error_code_expression);
}

void ViewGraph::HandleTextChangedDomain(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_domain, settings::error_code_domain);
}

void ViewGraph::HandleTextChangedCodomain(
    [[maybe_unused]] const QString &input_string) {
  HandleTextChanged(ui_->line_edit_codomain, settings::error_code_codomain);
}

void ViewGraph::HandleDrawPlot() {
  std::string expression_string{};
  expression_string = ui_->line_edit_graph_expression->text().toStdString();

  int error_code = 0;

  ClearPlot();
  error_code = DrawPlot(expression_string);

  if (error_code) {
    settings::error_code_graph = error_code;
    style_handler::SetIncorrectExpressionLineEdit(
        ui_->line_edit_graph_expression);
  } else {
    settings::error_code_graph = error_code::kNoError;
    style_handler::SetDefaultExpressionLineEdit(
        ui_->line_edit_graph_expression);
  }
}

int ViewGraph::DrawPlot(const std::string &expression_string) {
  int error_code = error_code::kNoError;

  QVector<double> x(constants::kPlotPointCount);
  QVector<double> y(constants::kPlotPointCount);

  double domains[2]{};
  QLineEdit *line_edit_domains[2]{ui_->line_edit_domain,
                                  ui_->line_edit_codomain};
  for (int i = 0; i < 2; ++i) {
    error_code = HandleCalculationDomain(domains[i], line_edit_domains[i]);
    if (error_code) {
      style_handler::SetIncorrectDomainLineEdit(line_edit_domains[i]);
      SetErrorCodeForDomains(i, error_code);
    }
  }
  if (IsNoErrorsInThePlot()) {
    error_code = CalculatePlot(x, y, constants::kPlotPointCount, domains[0],
                               expression_string);
  }
  if (error_code) {
    style_handler::SetIncorrectExpressionLineEdit(
        ui_->line_edit_graph_expression);
    settings::error_code_graph = error_code;
  }
  if (!error_code) {
    NormalizeCodomainValues(y, domains[1]);
    SetValuesAndReplot(x, y, domains);
    style_handler::SetDefaultExpressionLineEdit(
        ui_->line_edit_graph_expression);
  }
  return error_code;
}

int ViewGraph::IsNoErrorsInThePlot() {
  return IsNoErrorsInExpression() && IsNoErrorsInDomain() &&
         IsNoErrorsInCodomain();
}

int ViewGraph::IsNoErrorsInExpression() { return !settings::error_code_graph; }

int ViewGraph::IsNoErrorsInDomain() { return !settings::error_code_domain; }

int ViewGraph::IsNoErrorsInCodomain() { return !settings::error_code_codomain; }

int ViewGraph::HandleCalculationDomain(double &domain_value,
                                       QLineEdit *line_edit) {
  std::string expression_string{};
  expression_string = line_edit->text().toStdString();

  double result = 0;
  int error_code = error_code::kNoError;

  controller_->ExpressionSetVariable(0);
  error_code = controller_->ExpressionCalculate(expression_string);
  result = controller_->ExpressionGetResult();

  if (fabs(result) < constants::kDomainBoundValue && !error_code) {
    domain_value = result;
  } else {
    error_code |= error_code::kInvalidExpressionFormat;
  }
  return error_code;
}

void ViewGraph::SetErrorCodeForDomains(int index, int error_code) {
  if (index == 0) {
    settings::error_code_domain = error_code;
  } else if (index == 1) {
    settings::error_code_codomain = error_code;
  }
}

double ViewGraph::CalculateValue(int index, int point_count,
                                 double domain_interval) {
  double result = (index / ((double)(point_count / (domain_interval * 2)) - 1) -
                   domain_interval);
  return result;
}

int ViewGraph::CalculatePlot(QVector<double> &x, QVector<double> &y,
                             int point_count, double domain_interval,
                             const std::string &expression_string) {
  int error_code = error_code::kNoError;
  int error_count = 0;
  for (int i = 0; i < point_count; ++i) {
    double y_value = 0;
    double x_value = CalculateValue(i, point_count, domain_interval);

    controller_->ExpressionSetVariable(x_value);
    error_code = controller_->ExpressionCalculate(expression_string);
    y_value = controller_->ExpressionGetResult();

    if (!error_code) {
      x[i] = x_value;
      y[i] = y_value;
    } else {
      y[i] = 0;
      error_count++;
    }
  }

  error_code = error_code::kNoError;

  if (error_count == point_count) {
    error_code = error_code::kUnableToBuildGraph;
  }

  std::cerr << "Graph. error_count: " << error_count << "\n";

  return error_code;
}

void ViewGraph::NormalizeCodomainValues(QVector<double> &y,
                                        const double &codomain_value) {
  for (auto &item : y) {
    if (fabs(item) > codomain_value) {
      if (item > 0) {
        item = codomain_value * 2;
      } else {
        item = codomain_value * (-2);
      }
    }
  }
}

void ViewGraph::SetValuesAndReplot(QVector<double> &x, QVector<double> &y,
                                   double domains_interval[2]) {
  ui_->custom_plot->addGraph();
  ui_->custom_plot->graph(0)->setData(x, y);
  ui_->custom_plot->xAxis->setLabel("x");
  ui_->custom_plot->yAxis->setLabel("y");
  ui_->custom_plot->xAxis->setRange(-domains_interval[0], domains_interval[0]);
  ui_->custom_plot->yAxis->setRange(-domains_interval[1], domains_interval[1]);
  ui_->custom_plot->replot();
}

void ViewGraph::ClearPlot() {
  int point_count = 1;
  QVector<double> x(point_count);
  QVector<double> y(point_count);

  ui_->custom_plot->addGraph();
  ui_->custom_plot->graph(0)->setData(x, y);
  ui_->custom_plot->xAxis->setLabel("x");
  ui_->custom_plot->yAxis->setLabel("y");
  auto brush = new QBrush({255, 136, 0, 255});
  QBrush &link_brush = *brush;
  ui_->custom_plot->graph(0)->setPen(QPen(link_brush, 1.6));
  ui_->custom_plot->replot();
  delete brush;
}

void ViewGraph::SetupGraph() {
  ui_->custom_plot->addGraph();
  ui_->custom_plot->xAxis->setRange((-2) * M_PI, (2) * M_PI);
  ui_->custom_plot->yAxis->setRange((-2) * M_PI, (2) * M_PI);
  ui_->custom_plot->xAxis->setBasePen(QPen(Qt::white, 2));
  ui_->custom_plot->xAxis->setTickPen(QPen(Qt::gray, 1));
  ui_->custom_plot->xAxis->setTickLabelColor(Qt::white);
  ui_->custom_plot->xAxis->setLabelColor(Qt::white);
  ui_->custom_plot->xAxis->setTickLengthOut(1);
  ui_->custom_plot->xAxis->setTickLengthIn(0);
  ui_->custom_plot->yAxis->setBasePen(QPen(Qt::white, 2));
  ui_->custom_plot->yAxis->setTickPen(QPen(Qt::gray, 1));
  ui_->custom_plot->yAxis->setTickLabelColor(Qt::white);
  ui_->custom_plot->yAxis->setLabelColor(Qt::white);
  ui_->custom_plot->yAxis->setTickLengthOut(1);
  ui_->custom_plot->yAxis->setTickLengthIn(0);
  ui_->custom_plot->xAxis->setLabel("x");
  ui_->custom_plot->yAxis->setLabel("y");
  ui_->custom_plot->xAxis->grid()->setPen(QPen(Qt::gray));
  ui_->custom_plot->yAxis->grid()->setPen(QPen(Qt::gray));

  auto brush = new QBrush({10, 10, 10, 10});
  QBrush &link_brush = *brush;
  ui_->custom_plot->setBackground(QBrush((link_brush)));
  delete brush;
  ClearPlot();
}

}  // namespace s21