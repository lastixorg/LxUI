#include "LxUI/Theme/Theme.hpp"
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ThemeConfig themeConfig{
        .white = "#FFFFFF",
        .black = "#000000",
        .primaryColor = "blue",

        .primaryShade = {.light = 8, .dark = 6},
        .fontSize = 14.0,
        .headings = QVariantMap{{"h1", 26},
                                {"h2", 22},
                                {"h3", 18},
                                {"h4", 16},
                                {"h5", 14},
                                {"h6", 12}},
        .fontSizes =
            QVariantMap{
                {"xs", 12}, {"sm", 14}, {"md", 16}, {"lg", 18}, {"xl", 20}},
        .lineHeights = QVariantMap{{"xs", 1.2},
                                   {"sm", 1.4},
                                   {"md", 1.6},
                                   {"lg", 1.8},
                                   {"xl", 2.0}},
        .radius =
            QVariantMap{
                {"xs", 2}, {"sm", 4}, {"md", 8}, {"lg", 16}, {"xl", 32}},
        .autoContrast = true,
        .luminanceThreshold = 0.179,
        .colorMode = ColorMode::Light};

    auto theme = Theme::createTheme(engine, themeConfig);

    engine.addImportPath("qrc:/lastix");

    engine.load(QUrl("qrc:/lastix/demoApp/main.qml"));

    return app.exec();
}