#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
  label1 = new QLabel("Please input a Palindrome:", this);
  label1->move(50, 50);
  edit1 = new QLineEdit(this);
  edit1->move(300, 50);
  edit1->resize(280, 20);
  label2 = new QLabel("Is a Palindrome?", this);
  label2->move(50, 100);
  edit2 = new QLineEdit(this);
  edit2->move(300, 100);
  edit2->resize(280, 20);

  connect(edit1, &QLineEdit::returnPressed, [=]() {
    str = edit1->text();
    int left = 0, right = str.size() - 1;
    bool flag = false;
    while (left <= right) {
      if (str[left] != str[right]) {
        edit2->setText("It isn't a Palindrome!");
        flag = true;
        break;
      }
      ++left;
      --right;
    }
    if (!flag) {
      edit2->setText("It is a Palindrome!");
    }
  });
}

Widget::~Widget() {
  delete label1;
  delete label2;
  delete edit1;
  delete edit2;
}
