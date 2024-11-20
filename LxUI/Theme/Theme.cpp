#include "Theme.hpp"

Theme::Theme(QObject *parent, const ThemeConfig &config) : QObject(parent) {
    // Color palette
    setWhite(config.white);
    setBlack(config.black);
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
void Theme::setColors(const QVariantMap &colors) {
    if (m_colors != colors) {
        m_colors = colors;
        emit colorsChanged();
    }
}
void Theme::setPrimaryColor(const QString &primaryColor) {
    if (m_primaryColor != primaryColor) {
        m_primaryColor = primaryColor;
        emit primaryColorChanged();
    }
}
void Theme::setPrimaryShade(const PrimaryShade &primaryShade) {
    if (m_primaryShade.light != primaryShade.light ||
        m_primaryShade.dark != primaryShade.dark) {
        m_primaryShade = primaryShade;
        emit primaryShadeChanged();
    }
}


// Typography
void Theme::setFontSize(const float fontSize) {
    if (m_fontSize != fontSize) {
        m_fontSize = fontSize;
        emit fontSizeChanged();
    }
}
void Theme::setFontSizes(const QVariantMap &fontSizes) {
    if (m_fontSizes != fontSizes) {
        m_fontSizes = fontSizes;
        emit fontSizesChanged();
    }
}
void Theme::setLineHeights(const QVariantMap &lineHeights) {
    if (m_lineHeights != lineHeights) {
        m_lineHeights = lineHeights;
        emit lineHeightsChanged();
    }
}


// Radius
void Theme::setRadius(const QVariantMap &radius) {
    if (m_radius != radius) {
        m_radius = radius;
        emit radiusChanged();
    }
}
void Theme::setDefaultRadius(const Size &defaultRadius) {
    if (m_defaultRadius != defaultRadius) {
        m_defaultRadius = defaultRadius;
        emit defaultRadiusChanged();
    }
}


// Contrast
void Theme::setAutoContrast(bool autoContrast) {
    if (m_autoContrast != autoContrast) {
        m_autoContrast = autoContrast;
        emit autoContrastChanged();
    }
}
void Theme::setLuminanceThreshold(float luminanceThreshold) {
    if (m_luminanceThreshold != luminanceThreshold) {
        m_luminanceThreshold = luminanceThreshold;
        emit luminanceThresholdChanged();
    }
}

void Theme::setColorMode(ColorMode::Mode colorMode) {
    if (m_colorMode != colorMode) {
        m_colorMode = colorMode;
        emit colorModeChanged();
    }
}