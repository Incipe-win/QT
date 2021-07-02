#ifndef WIDGET_H
#define WIDGET_H

#include <QtBluetooth/qbluetoothsocket.h>
#include <QtBluetooth/qtbluetoothglobal.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>

#include <QListWidgetItem>
#include <QMessageBox>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void on_send_clicked();

  void on_disconnect_clicked();

  void on_scan_clicked();

  void on_clear_clicked();

  void on_open_clicked();

  void on_close_clicked();

  void addBlueToothDevicesToList(const QBluetoothDeviceInfo &);

  void itemActivated(QListWidgetItem *item);

  void readBluetoothDataEvent();

  void bluetoothConnectedEvent();

  void bluetoothDisconnectedEvent();

 private:
  Ui::Widget *ui;
  QBluetoothDeviceDiscoveryAgent *discoveryAgent;
  QBluetoothLocalDevice *localDevice;
  QBluetoothSocket *socket;
  QString comStr;
  QFont font;
};
#endif  // WIDGET_H
