#include "TestComponent.hpp"

TestComponent::TestComponent(QQuickPaintedItem *parent)
    : QQuickPaintedItem(parent) {}

void TestComponent::paint(QPainter *painter) {

  painter->setBrush(QBrush(Qt::blue));
  painter->drawRect(boundingRect());
}
