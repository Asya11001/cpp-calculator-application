#ifndef CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_GRAPH_VIEW_GRAPH_H_
#define CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_GRAPH_VIEW_GRAPH_H_

#include <QMainWindow>

#include "../../Controller/Controller.h"
#include "../QCustomPlot/QCustomPlot.h"
#include "../ui_View.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class ViewGraph : public QMainWindow {
  Q_OBJECT

 public:
  ViewGraph(Controller *controller, Ui::View *ui, QWidget *parent = nullptr);

  void Setup();

  void SetupDomains();

  void SetupDomain();

  void SetupCodomain();

  void SetupGraphLineEdit();

  void SetupButtons();

  void SetupClearButton();

  void SetupDrawButton();

  void HandleClearButtonClick();

  void HandleTextChanged(QLineEdit *line_edit, int &error_code);

  void HandleTextChangedGraph([[maybe_unused]] const QString &input_string);

  void HandleTextChangedDomain([[maybe_unused]] const QString &input_string);

  void HandleTextChangedCodomain([[maybe_unused]] const QString &input_string);

  void HandleDrawPlot();

  void NormalizeCodomainValues(QVector<double> &, const double &);

  int DrawPlot(const std::string &expression_string);

  int IsNoErrorsInThePlot();

  int IsNoErrorsInExpression();

  int IsNoErrorsInDomain();

  int IsNoErrorsInCodomain();

  int HandleCalculationDomain(double &domain_value, QLineEdit *line_edit);

  void SetErrorCodeForDomains(int index, int error_code);

  double CalculateValue(int index, int point_count, double domain_interval);

  int CalculatePlot(QVector<double> &x, QVector<double> &y, int point_count,
                    double domain_interval,
                    const std::string &expression_string);

  void SetValuesAndReplot(QVector<double> &x, QVector<double> &y,
                          double domains_interval[2]);

  void SetupGraph();

  void ClearPlot();

  ~ViewGraph();

 protected:
  Ui::View *ui_;
  QWidget *parent_;
  Controller *controller_;
};
}  // namespace s21

#endif  // CPP3_SMART_CALC_V_2_0_1_VIEW_VIEW_GRAPH_VIEW_GRAPH_H_
