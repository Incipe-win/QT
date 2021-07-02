#include "widget.h"

#include "ui_widget.h"

/* step1
 * 分析：数据结构、算法
 * 用名词提炼法把所有名词提炼出来、考虑数据容器
 * step2
 * 画出流程图
 * step3
 *
 * step4
 *
 * */

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  //  connect(ui->edit1, &QLineEdit::returnPressed, [=]() {
  //    double radius = ui->edit1->text().toDouble();
  //    double area = 3.14 * radius * radius;
  //    ui->edit2->setText(QString::number(area));
  //  });
  auto func = [=]() {
    double radius = ui->edit1->text().toDouble();
    double area = 3.14 * radius * radius;
    ui->edit2->setText(QString::number(area));
  };
  //  void (QLineEdit::myslot)() = QLine
  connect(ui->edit1, &QLineEdit::returnPressed, func);
}

Widget::~Widget() { delete ui; }
