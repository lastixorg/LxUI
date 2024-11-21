#include "Theme.hpp"


Theme::Theme(QObject *parent, const ThemeConfig &config)
    : QObject(parent), m_config(ThemeConfig{}) {

    // Color palette
    setWhite(config.white);
    setBlack(config.black);

    // m_colors = Defaults::defaultColors;
    setColors(config.colors);
    setPrimaryColor(config.primaryColor);
    setPrimaryShade(config.primaryShade);

    // Typography
    setFontSize(config.fontSize);
    setFontSizes(config.fontSizes);
    setLineHeights(config.lineHeights);

    // Radius
    setRadius(config.radius);
    setDefaultRadius(config.defaultRadius);

    // Contrast
    setAutoContrast(config.autoContrast);
    setLuminanceThreshold(config.luminanceThreshold);
}


// Color palette
void Theme::setWhite(const QString &white) {

    if (m_config.white != white) {
        m_config.white = white;
        emit whiteChanged();
    }
}
void Theme::setBlack(const QString &black) {
    if (m_config.black != black) {
        m_config.black = black;
        emit blackChanged();
    }
}
void Theme::setColors(const QVariantMap &colors) {
    if (m_config.colors != colors) {
        m_config.colors.insert(colors);
        emit colorsChanged();
    }
}
void Theme::setPrimaryColor(const QString &primaryColor) {
    if (m_config.primaryColor != primaryColor) {
        m_config.primaryColor = primaryColor;
        emit primaryColorChanged();
    }
}
void Theme::setPrimaryShade(const PrimaryShade &primaryShade) {
    if (m_config.primaryShade.light != primaryShade.light ||
        m_config.primaryShade.dark != primaryShade.dark) {
        m_config.primaryShade = primaryShade;
        emit primaryShadeChanged();
    }
}


// Typography
void Theme::setFontSize(const float fontSize) {
    if (m_config.fontSize != fontSize) {
        m_config.fontSize = fontSize;
        emit fontSizeChanged();
    }
}
void Theme::setFontSizes(const QVariantMap &fontSizes) {
    if (m_config.fontSizes != fontSizes) {
        m_config.fontSizes = fontSizes;
        emit fontSizesChanged();
    }
}
void Theme::setLineHeights(const QVariantMap &lineHeights) {
    if (m_config.lineHeights != lineHeights) {
        m_config.lineHeights = lineHeights;
        emit lineHeightsChanged();
    }
}


// Radius
void Theme::setRadius(const QVariantMap &radius) {
    if (m_config.radius != radius) {
        m_config.radius = radius;
        emit radiusChanged();
    }
}
void Theme::setDefaultRadius(const Size &defaultRadius) {
    if (m_config.defaultRadius != defaultRadius) {
        m_config.defaultRadius = defaultRadius;
        emit defaultRadiusChanged();
    }
}


// Contrast
void Theme::setAutoContrast(bool autoContrast) {
    if (m_config.autoContrast != autoContrast) {
        m_config.autoContrast = autoContrast;
        emit autoContrastChanged();
    }
}
void Theme::setLuminanceThreshold(float luminanceThreshold) {
    if (m_config.luminanceThreshold != luminanceThreshold) {
        m_config.luminanceThreshold = luminanceThreshold;
        emit luminanceThresholdChanged();
    }
}

void Theme::setColorMode(ColorMode::Mode colorMode) {
    if (m_config.colorMode != colorMode) {
        m_config.colorMode = colorMode;
        emit colorModeChanged();
    }
}