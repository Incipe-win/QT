#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QWidget>
#include <string>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  Ui::Widget *ui;
  int nums;
  int convert;
  QString str;
  std::unordered_map<int, std::string> ump{{10, "A"}, {11, "B"}, {12, "C"},
                                           {13, "D"}, {14, "E"}, {15, "F"}};
};
#endif  // WIDGET_H
