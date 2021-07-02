#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QStack>
#include <QWidget>

#include "calculate.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  QLabel *label1, *label2;
  QLineEdit *edit1, *edit2;
  Calculate *cal;
  QString result;
 private slots:
  void on_edit_enter();
  void on_edit_display();
};
#endif  // WIDGET_H
