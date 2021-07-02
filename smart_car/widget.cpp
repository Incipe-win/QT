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

  //
  quint64 port = 8888;
  receiver = new QUdpSocket(this);
  receiver->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  dstip = QHostAddress("192.168.43.133");
  dstport = 6666;

  connect(ui->go, SIGNAL(clicked()), this, SLOT(on_go_clicked()));
  connect(ui->back, SIGNAL(clicked()), this, SLOT(on_back_clicked()));
  connect(ui->left, SIGNAL(clicked()), this, SLOT(on_left_clicked()));
  connect(ui->right, SIGNAL(clicked()), this, SLOT(on_right_clicked()));
  connect(ui->stop, SIGNAL(clicked()), this, SLOT(on_stop_clicked()));

  // 每次有新的数据可以从设备的当前读通道中读取时，就发出这个信号。
  // 只有当新的数据可用时，它才会再次发出，比如当新的网络数据有效负载到达网络套接字上，或者当一个新的数据块被附加到设备上。
  connect(receiver, SIGNAL(readyRead()), this, SLOT(video_receive_show()));
}

void Widget::video_receive_show() {
  // 返回第一个UDP数据报的大小。
  quint64 size = receiver->pendingDatagramSize();
  QByteArray buff;
  buff.resize(size);
  receiver->readDatagram(buff.data(), buff.size());
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
  receiver->writeDatagram(cmd, dstip, dstport);
}

void Widget::on_back_clicked() {
  QByteArray cmd = "back";
  receiver->writeDatagram(cmd, dstip, dstport);
}

void Widget::on_go_clicked() {
  QByteArray cmd = "go";
  qDebug() << cmd;
  receiver->writeDatagram(cmd, dstip, dstport);
}

void Widget::on_stop_clicked() {
  QByteArray cmd = "stop";
  receiver->writeDatagram(cmd, dstip, dstport);
}

void Widget::on_right_clicked() {
  QByteArray cmd = "right";
  receiver->writeDatagram(cmd, dstip, dstport);
}
