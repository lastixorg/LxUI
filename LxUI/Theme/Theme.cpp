#include "Theme.hpp"
#include <QDebug>
#include <QQmlApplicationEngine>

Theme::Theme(QObject *parent) : QObject(parent) {
    initializeColors();
    initializeDefaults();
}


void Theme::initializeColors() {

    // Colors from https://yeun.github.io/open-color/
    m_colors["dark"] = {"#C9C9C9", "#b8b8b8", "#828282", "#696969", "#424242",
                        "#3b3b3b", "#2e2e2e", "#242424", "#1f1f1f", "#141414"};

    m_colors["gray"] = {"#f8f9fa", "#f1f3f5", "#e9ecef", "#dee2e6", "#ced4da",
                        "#adb5bd", "#868e96", "#495057", "#343a40", "#212529"};

    m_colors["red"] = {"#fff5f5", "#ffe3e3", "#ffc9c9", "#ffa8a8", "#ff8787",
                       "#ff6b6b", "#fa5252", "#f03e3e", "#e03131", "#c92a2a"};

    m_colors["pink"] = {"#fff0f6", "#ffdeeb", "#fcc2d7", "#faa2c1", "#f783ac",
                        "#f06595", "#e64980", "#d6336c", "#c2255c", "#a61e4d"};

    m_colors["grape"] = {"#f8f0fc", "#f3d9fa", "#eebefa", "#e599f7", "#da77f2",
                         "#cc5de8", "#be4bdb", "#ae3ec9", "#9c36b5", "#862e9c"};

    m_colors["violet"] = {"#f3f0ff", "#e5dbff", "#d0bfff", "#b197fc",
                          "#9775fa", "#845ef7", "#7950f2", "#7048e8",
                          "#6741d9", "#5f3dc4"};

    m_colors["indigo"] = {"#edf2ff", "#dbe4ff", "#bac8ff", "#91a7ff",
                          "#748ffc", "#5c7cfa", "#4c6ef5", "#4263eb",
                          "#3b5bdb", "#364fc7"};

    m_colors["blue"] = {"#e7f5ff", "#d0ebff", "#a5d8ff", "#74c0fc", "#4dabf7",
                        "#339af0", "#228be6", "#1c7ed6", "#1971c2", "#1864ab"};

    m_colors["cyan"] = {"#e3fafc", "#c5f6fa", "#99e9f2", "#66d9e8", "#3bc9db",
                        "#22b8cf", "#15aabf", "#1098ad", "#0c8599", "#0b7285"};

    m_colors["teal"] = {"#e6fcf5", "#c3fae8", "#96f2d7", "#63e6be", "#38d9a9",
                        "#20c997", "#12b886", "#0ca678", "#099268", "#087f5b"};

    m_colors["green"] = {"#ebfbee", "#d3f9d8", "#b2f2bb", "#8ce99a", "#69db7c",
                         "#51cf66", "#40c057", "#37b24d", "#2f9e44", "#2b8a3e"};

    m_colors["lime"] = {"#f4fce3", "#e9fac8", "#d8f5a2", "#c0eb75", "#a9e34b",
                        "#94d82d", "#82c91e", "#74b816", "#66a80f", "#5c940d"};

    m_colors["yellow"] = {"#fff9db", "#fff3bf", "#ffec99", "#ffe066",
                          "#ffd43b", "#fcc419", "#fab005", "#f59f00",
                          "#f08c00", "#e67700"};

    m_colors["orange"] = {"#fff4e6", "#ffe8cc", "#ffd8a8", "#ffc078",
                          "#ffa94d", "#ff922b", "#fd7e14", "#f76707",
                          "#e8590c", "#d9480f"};
}

Theme *Theme::createTheme(QQmlApplicationEngine &engine,
                          const ThemeConfig &config) {
    Theme *themeSingleton = engine.singletonInstance<Theme *>("LxUI.Theme",
                                                              "Theme");

    return themeSingleton;
}

void Theme::initializeDefaults() {
    m_primaryShade = {.light = 6, .dark = 7};

    // Headings
    QVariantMap sizes;
    sizes["h1"] = QVariantMap{{"pointSize", m_defaultFontSize * 2.857},
                              {"lineHeight", 1.3}};
    sizes["h2"] = QVariantMap{{"pointSize", m_defaultFontSize * 2.286},
                              {"lineHeight", 1.35}};
    sizes["h3"] = QVariantMap{{"pointSize", m_defaultFontSize * 1.714},
                              {"lineHeight", 1.4}};
    sizes["h4"] = QVariantMap{{"pointSize", m_defaultFontSize * 1.286},
                              {"lineHeight", 1.45}};
    sizes["h5"] = QVariantMap{{"pointSize", m_defaultFontSize * 1.143},
                              {"lineHeight", 1.5}};
    sizes["h6"] = QVariantMap{{"pointSize", m_defaultFontSize},
                              {"lineHeight", 1.5}};

    //   m_headings["fontFamily"] = QVariant::fromValue(m_fontFamily);

    m_headings["fontFamily"] = "Arial";
    // Font sizes
    m_fontSizes = {{"xs", m_defaultFontSize * 0.857},
                   {"sm", m_defaultFontSize},
                   {"md", m_defaultFontSize * 1.143},
                   {"lg", m_defaultFontSize * 1.286},
                   {"xl", m_defaultFontSize * 1.571}};

    // Line heights
    m_lineHeights = {
        {"xs", 1.2}, {"sm", 1.3}, {"md", 1.4}, {"lg", 1.5}, {"xl", 1.6}};

    // Radius
    m_radius = {{"xs", 2}, {"sm", 4}, {"md", 8}, {"lg", 16}, {"xl", 32}};
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

QString Theme::setColor(const QString &color, int shade) {
    if (!m_colors.contains(color)) {
        qWarning() << "Invalid color:" << color;
        return {};
    }

    if (shade < 0 || shade > 9) {
        qWarning() << "Shade must be between 0 and 9";
        return {};
    }

    return m_colors[color][shade];
}

void Theme::setAutoContrast(bool contrast) {
    if (m_autoContrast != contrast) {
        m_autoContrast = contrast;
        emit autoContrastChanged();
    }
}

void Theme::setLuminanceThreshold(double threshold) {
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

void Theme::setHeadings(const QVariantMap &headings) {
    if (m_headings == headings) { return; }
    m_headings = headings;
    emit headingsChanged();
}
