#include "widget.h"

#include <QDebug>
#include <QPushButton>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, [=]() {
    ui->textEdit3->clear();
    str.clear();
    // 数字
    QString str1 = ui->textEdit1->toPlainText();
    nums = str1.toInt();
    // 进制
    QString str2 = ui->textEdit2->toPlainText();
    convert = str2.toInt();
    // 结果
    bool flag = false;
    if (nums < 0) {
      flag = true;
      nums = -nums;
    }
    while (nums) {
      int tmp = nums % convert;
      if (tmp >= 10) {
        str = QString::fromStdString(ump[tmp]) + str;
      } else {
        str = QString::number(tmp) + str;
      }
      qDebug() << str;
      nums /= convert;
    }
    if (flag) {
      str = "-" + str;
    }
    ui->textEdit3->setText(str);
  });
}

Widget::~Widget() { delete ui; }
