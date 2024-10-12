#ifndef TESTCOMPONENT_HPP
#define TESTCOMPONENT_HPP

#include <QPainter>
#include <QQuickPaintedItem>
#include <QtQml/qqmlregistration.h>

class TestComponent : public QQuickPaintedItem {
  Q_OBJECT
  QML_ELEMENT

public:
  explicit TestComponent(QQuickPaintedItem *parent = nullptr);

  void paint(QPainter *painter) override;
};

#endif // TESTCOMPONENT_HPP
