#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  QStringList serialNamePort;
  this->setWindowTitle("serial");
  serialPort = new QSerialPort(this);
  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    serialNamePort << info.portName();
  }
  ui->serialBox->addItems(serialNamePort);

  connect(ui->openPort, &QPushButton::clicked, [=]() {
    // serial port settings
    serialPort->setPortName(ui->serialBox->currentText());
    serialPort->setBaudRate(ui->baudBox->currentText().toInt());
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);

    // open serial port messagebox
    if (true == serialPort->open(QIODevice::ReadWrite)) {
      QMessageBox::information(this, "tips", "open serial port success");
    } else {
      QMessageBox::critical(this, "tips", "open serial port failure");
    }
  });

  connect(ui->closePort, &QPushButton::clicked, [=]() { serialPort->close(); });

  connect(ui->openLed, &QPushButton::clicked, [=]() {
    serialPort->write("ON\n");
    qDebug() << "ON";
  });

  connect(ui->closeLed, &QPushButton::clicked, [=]() {
    serialPort->write("OFF\n");
    qDebug() << "OFF";
  });
}

Widget::~Widget() { delete ui; }
