#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  QPalette palette = this->palette();
  QImage background(":/bg.jpg");
  QImage fit =
      background.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);
  palette.setBrush(QPalette::Window, QBrush(fit));
  this->setPalette(palette);
  QHostAddress ip = QHostAddress::Any;
  quint64 port = 8888;
  receiver.bind(ip, port);
  dstip = QHostAddress("113.223.116.208");
  dstport = 6666;
  connect(ui->go, SIGNAL(clicked()), this, SLOT(on_go_clicked()));
  connect(ui->back, SIGNAL(clicked()), this, SLOT(on_back_clicked()));
  connect(ui->left, SIGNAL(clicked()), this, SLOT(on_left_clicked()));
  connect(ui->right, SIGNAL(clicked()), this, SLOT(on_right_clicked()));
  connect(ui->stop, SIGNAL(clicked()), this, SLOT(on_stop_clicked()));
  connect(&receiver, SIGNAL(readyRead()), this, SLOT(video_receive_show()));
}

void Widget::video_receive_show() {
  quint64 size = receiver.pendingDatagramSize();
  QByteArray buff;
  buff.resize(size);
  receiver.readDatagram(buff.data(), buff.size());
  QByteArray rc = QByteArray::fromBase64(buff);
  QByteArray rdc = qUncompress(rc);
  QImage image;
  image.loadFromData(rdc);
  QMatrix matrix;
  matrix.rotate(90);
  ui->label->setPixmap(
      QPixmap::fromImage(image).transformed(matrix, Qt::SmoothTransformation));
  ui->label->autoFillBackground();
  update();
}

Widget::~Widget() { delete ui; }

void Widget::on_left_clicked() {
  QByteArray cmd = "left";
  receiver.writeDatagram(cmd, dstip, dstport);
}

void Widget::on_back_clicked() {
  QByteArray cmd = "back";
  receiver.writeDatagram(cmd, dstip, dstport);
}

void Widget::on_go_clicked() {
  QByteArray cmd = "go";
  receiver.writeDatagram(cmd, dstip, dstport);
}

void Widget::on_stop_clicked() {
  QByteArray cmd = "stop";
  receiver.writeDatagram(cmd, dstip, dstport);
}

void Widget::on_right_clicked() {
  QByteArray cmd = "right";
  receiver.writeDatagram(cmd, dstip, dstport);
}
