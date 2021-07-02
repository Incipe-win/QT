#include "widget.h"

#include "ui_widget.h"

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  font.setPointSize(10);
  font.setBold(true);
  font.setWeight(66);

  discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
  localDevice = new QBluetoothLocalDevice();
  socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
          this, &Widget::addBlueToothDevicesToList);
  connect(ui->listWidget, &QListWidget::itemActivated, this,
          &Widget::itemActivated);
  connect(socket, &QIODevice::readyRead, this, &Widget::readBluetoothDataEvent);
  connect(socket, SIGNAL(connected()), this, SLOT(bluetoothConnectedEvent()));
  connect(socket, &QBluetoothSocket::disconnected, this,
          &Widget::bluetoothDisconnectedEvent);

  if (localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff) {
    ui->open->setEnabled(true);
    ui->close->setEnabled(false);
  } else {
    ui->open->setEnabled(false);
    ui->close->setEnabled(true);
  }

  if (localDevice->hostMode() == QBluetoothLocalDevice::HostDiscoverable) {
    ui->checkBox->setChecked(true);
  } else {
    ui->checkBox->setChecked(false);
  }
}

Widget::~Widget() { delete ui; }

void Widget::addBlueToothDevicesToList(const QBluetoothDeviceInfo &info) {
  QString label =
      QString("%1 %2").arg(info.address().toString()).arg(info.name());

  QList<QListWidgetItem *> items =
      ui->listWidget->findItems(label, Qt::MatchExactly);

  if (items.empty()) {
    QListWidgetItem *item = new QListWidgetItem(label);
    QBluetoothLocalDevice::Pairing pairingStatus =
        localDevice->pairingStatus(info.address());
    if (pairingStatus == QBluetoothLocalDevice::Paired ||
        pairingStatus == QBluetoothLocalDevice::AuthorizedPaired) {
      item->setTextColor(QColor(Qt::green));
    } else {
      item->setTextColor(QColor(Qt::black));
    }
    ui->listWidget->setFont(font);
    ui->listWidget->addItem(item);
  }
}

void Widget::itemActivated(QListWidgetItem *item) {
  QString text = item->text();

  int index = text.indexOf(' ');

  if (index == -1) return;

  QBluetoothAddress address(text.left(index));
  QString name(text.mid(index + 1));
  QMessageBox::information(this, tr("Info"), tr("The device is connecting..."));
  socket->connectToService(address, QBluetoothUuid(serviceUuid),
                           QIODevice::ReadWrite);
}

void Widget::readBluetoothDataEvent() {
  QByteArray line = socket->readAll();
  QString strData = line;
  comStr.append(strData);
  qDebug() << comStr;
  if (comStr.endsWith("\r\n")) {
    comStr = comStr.simplified();
    ui->textBrowser->setFont(font);
    ui->textBrowser->append(comStr);
    comStr.clear();
  }
}

void Widget::bluetoothConnectedEvent() {
  QMessageBox::information(this, tr("Info"), tr("successful connection!"));
}

void Widget::bluetoothDisconnectedEvent() {
  QMessageBox::information(this, tr("Info"), tr("successful disconnection!"));
}

void Widget::on_send_clicked() {
  QString context = ui->textEdit->toPlainText();
  ui->textEdit->setFont(font);
  QByteArray sendData = context.toUtf8();
  socket->write(sendData);
}

void Widget::on_disconnect_clicked() { socket->disconnectFromService(); }

void Widget::on_scan_clicked() {
  discoveryAgent->start();
  ui->scan->setEnabled(false);
}

void Widget::on_clear_clicked() { ui->textBrowser->clear(); }

void Widget::on_open_clicked() {
  localDevice->powerOn();
  ui->close->setEnabled(true);
  ui->open->setEnabled(false);
  ui->scan->setEnabled(true);
}

void Widget::on_close_clicked() {
  localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
  ui->close->setEnabled(false);
  ui->open->setEnabled(true);
  ui->scan->setEnabled(false);
}
