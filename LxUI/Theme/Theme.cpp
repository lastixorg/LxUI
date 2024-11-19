#include "Theme.hpp"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <qcontainerfwd.h>

Theme::Theme(QObject *parent) : QObject(parent) {
}


Theme *Theme::createTheme(QQmlApplicationEngine &engine,
                          const ThemeConfig &config) {
    Theme *themeSingleton = engine.singletonInstance<Theme *>("LxUI.Theme",
                                                              "Theme");

    // TODO: make config override defaults
    // themeSingleton->setWhite(config.white);

    return themeSingleton;
}


void Theme::setWhite(const QString &white) {
    if (m_white != white) {
        m_white = white;
        emit whiteChanged();
    }
}

void Theme::setBlack(const QString &black) {
    if (m_black != black) {
        m_black = black;
        emit blackChanged();
    }
}

void Theme::setPrimaryColor(const QString &color) {
    if (!m_colors.contains(color)) {
        qWarning() << "Invalid color:" << color;
        return;
    }

    if (m_primaryColor != color) {
        m_primaryColor = color;
        emit primaryColorChanged();
    }
}

void Theme::setPrimaryShade(const PrimaryShade &shade) {
    // if (m_primaryShade != shade) {
    //     m_primaryShade = shade;
    //     emit primaryShadeChanged();
    // }
}

// QString Theme::setColor(const QString &color, int shade) {
//     if (!m_colors.contains(color)) {
//         qWarning() << "Invalid color:" << color;
//         return {};
//     }

//     if (shade < 0 || shade > 9) {
//         qWarning() << "Shade must be between 0 and 9";
//         return {};
//     }

//     return m_colors[color][shade];
// }

void Theme::setColors(const QVariantMap &colors) {
}
void Theme::setAutoContrast(bool contrast) {
    if (m_autoContrast != contrast) {
        m_autoContrast = contrast;
        emit autoContrastChanged();
    }
}

void Theme::setLuminanceThreshold(float threshold) {
    if (!qFuzzyCompare(m_luminanceThreshold, threshold)) {
        m_luminanceThreshold = threshold;
        emit luminanceThresholdChanged();
    }
}

void Theme::setLineHeights(const QVariantMap &heights) {
    if (m_lineHeights == heights) { return; }
    m_lineHeights = heights;
    emit lineHeightsChanged();
}

void Theme::setFontSizes(const QVariantMap &sizes) {
    if (m_fontSizes == sizes) { return; }
    m_fontSizes = sizes;
    emit fontSizesChanged();
}

void Theme::setRadius(const QVariantMap &radius) {
    if (m_radius == radius) { return; }
    m_radius = radius;
    emit radiusChanged();
}
