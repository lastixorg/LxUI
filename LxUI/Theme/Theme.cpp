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
    QVariantMap newColors = m_config.colors;
    bool isValid = true;

    for (auto it = colors.constBegin(); it != colors.constEnd(); ++it) {
        const QString &key = it.key();
        const QVariant &value = it.value();

        if (!value.canConvert<QStringList>()) {
            qWarning() << "Colors: Value for key" << key
                       << "is not a QStringList.";
            isValid = false;
            continue;
        }

        QStringList colorList = value.toStringList();
        int numColors = colorList.size();


        if (numColors < 1 || numColors > 10) {
            qWarning() << "Colors: QStringList for key" << key
                       << "must contain between 1 and 10 colors (found"
                       << numColors << ").";
            isValid = false;
            continue;
        }


        bool colorListValid = true;
        for (const QString &colorString : colorList) {
            QColor color(colorString);
            if (!color.isValid()) {
                qWarning() << "Colors: Invalid color" << colorString
                           << "for key" << key << ".";
                colorListValid = false;
                break;
            }
        }

        if (!colorListValid) {
            isValid = false;
            continue;
        }

        newColors.insert(key, colorList);
    }

    if (isValid) {
        if (m_config.colors != newColors) {
            m_config.colors = newColors;
            emit colorsChanged();
        }
    } else {
        qWarning() << "Colors were not set due to validation errors.";
    }
}

void Theme::setPrimaryColor(const QString &primaryColor) {
    if (m_config.primaryColor != primaryColor) {
        if (!m_config.colors.contains(primaryColor)) {
            qWarning() << "Invalid primaryColor:" << primaryColor
                       << "- it is not a key in the colors map.";
            return;
        }
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