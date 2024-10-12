#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  engine.addImportPath("qrc:/lastix");

  engine.load(QUrl(u"qrc:/lastix/demoApp/main.qml"_qs));

  return app.exec();
}