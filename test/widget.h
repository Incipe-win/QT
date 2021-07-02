#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  double radius;
  double area;
  QLabel *label1, *label2;
  QLineEdit *edit1, *edit2;

 private slots:
  void on_edit_enter();
  void on_edit_display();
};
#endif  // WIDGET_H
