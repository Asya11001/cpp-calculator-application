#include <QApplication>

#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/View.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "C");
  QApplication application(argc, argv);
  s21::Model model{};
  s21::Controller controller{&model};
  s21::View view{&controller};
  view.show();
  return application.exec();
}
