#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
  label1 = new QLabel("Please input the circle radius:", this);
  label1->move(50, 50);
  edit1 = new QLineEdit(this);
  edit1->move(300, 50);
  label2 = new QLabel("The of circle radius is:", this);
  label2->move(50, 100);
  edit2 = new QLineEdit(this);
  edit2->move(300, 100);

  connect(edit1, SIGNAL(returnPressed()), this, SLOT(on_edit_enter()));
  connect(edit1, SIGNAL(returnPressed()), this, SLOT(on_edit_display()));
}

void Widget::on_edit_enter() { radius = edit1->text().toInt(); }

void Widget::on_edit_display() {
  area = 3.14 * radius * radius;
  edit2->setText(QString::number(area));
}

Widget::~Widget() {}
