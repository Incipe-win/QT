#include "calculate.h"

Calculate::Calculate() {}

QString Calculate::cal_value(int num) {
  QStack<int> st;
  while (num) {
    st.push(num % 2);
    num /= 2;
  }
  QString str;
  while (!st.empty()) {
    str += QString::number(st.top());
    st.pop();
  }
  qDebug() << str;
  return str;
}
