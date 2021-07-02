#ifndef WIDGET_H
#define WIDGET_H

#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QGuiApplication>
#include <QImage>
#include <QImageReader>
#include <QMatrix>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QRect>
#include <QScreen>
#include <QUdpSocket>
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
  void video_receive_show();
  void on_left_clicked();
  void on_back_clicked();
  void on_go_clicked();
  void on_stop_clicked();
  void on_right_clicked();

 private:
  Ui::Widget *ui;
  QUdpSocket receiver;
  QHostAddress dstip;
  quint64 dstport;
};
#endif  // WIDGET_H
