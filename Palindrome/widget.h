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
  QLabel *label1, *label2;
  QLineEdit *edit1, *edit2;
  QString str;
};
#endif  // WIDGET_H
