#ifndef CALCULATE_H
#define CALCULATE_H

#include <QDebug>
#include <QStack>
#include <QString>
#include <typeinfo>

class Calculate {
 public:
  Calculate();
  QString cal_value(int num);
};

#endif  // CALCULATE_H
