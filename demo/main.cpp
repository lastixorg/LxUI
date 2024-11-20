#include "LxUI/Theme/Theme.hpp"
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qjsengine.h>
#include <qobject.h>
#include <qqml.h>
#include <qqmlengine.h>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    ThemeConfig themeConfig{
        .white = "#FFFFFF", .black = "#000000", .primaryColor = "green"};

    auto theme = ThemeProvider::init(themeConfig, &app);

    engine.addImportPath("qrc:/lastix");

    engine.load(QUrl("qrc:/lastix/demoApp/main.qml"));

    return app.exec();
}