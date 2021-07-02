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

  quint64 port = 8888;
  receiver = new QUdpSocket(this);
  /* QUdpSocket::ShareAddress
  1、允许其他服务绑定同样的地址和端口
  2、当多进程通过监听同一地址和端口，进而共享单个服务的负载时，将十分有用(例如：一个拥有几个预先建立的监听者的WEB服务器能够改善响应时间)。不过，由于任何服务都允许重新绑定(rebind)，该选项应该引起某些安全上的考虑
  3、需要注意的是，把该选项和ReuseAddressHint结合，也会允许你的服务重新绑定一个已存在的共享地址
  4、在Unix上，该选项等同于SO_REUSEADDR；在Windows上，该选项被忽略
  QUdpSocket::ReuseAddressHint
  1、为QUdpSocke提供提示，即在地址和端口已经被其他套接字绑定的情况下，也应该试着重新绑定
  2、在Unix上，该选项被忽略；在Windows上等同于SO_REUSEADDR 套接字选项
  */
  receiver->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  dstip = QHostAddress("192.168.251.169");
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
  // 把一帧数据展示到label标签上
  ui->label->setPixmap(QPixmap::fromImage(image));
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
