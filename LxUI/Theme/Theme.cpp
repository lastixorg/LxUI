#include "Theme.hpp"

Theme::Theme(QObject *parent, const ThemeConfig &config) : Theme(parent) {
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
    setColorScheme(config.colorScheme);
}

Theme::Theme(QObject *parent) : QObject(parent) {
    // System scheme listener
    connect(qApp->styleHints(), &QStyleHints::colorSchemeChanged, this,
            [this]() {
                // Only emit if mode is set to Auto (unknown)
                if (m_config.colorScheme == Qt::ColorScheme::Unknown) {

                    emit colorSchemeChanged();
                }
            });
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
        if (!it.value().canConvert<QVariantList>()) {
            qWarning() << "Colors: Value for key" << it.key()
                       << "is not a QVariantList.";
            isValid = false;
            continue;
        }

        const auto colorList = it.value().toList();
        const auto numColors = colorList.size();

        if (numColors < 1 || numColors > 10) {
            qWarning() << "Colors: QVariantList for key" << it.key()
                       << "must contain between 1 and 10 colors (found"
                       << numColors << ").";
            isValid = false;
            continue;
        }

        QVariantList validatedColors;
        bool colorListValid = true;

        for (const auto &colorVariant : colorList) {
            QColor color;

            if (colorVariant.canConvert<QColor>()) {
                color = colorVariant.value<QColor>();
            } else if (colorVariant.canConvert<QString>()) {
                color = QColor(colorVariant.toString());
            }

            if (!color.isValid()) {
                qWarning() << "Colors: Invalid color in list for key"
                           << it.key();
                colorListValid = false;
                break;
            }
            validatedColors.append(QVariant::fromValue(color));
        }

        if (!colorListValid) {
            isValid = false;
            continue;
        }

        newColors.insert(it.key(), validatedColors);
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
    if (m_config.primaryShade.light() != primaryShade.light() ||
        m_config.primaryShade.dark() != primaryShade.dark()) {
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
void Theme::setColorScheme(Qt::ColorScheme colorScheme) {
    if (m_config.colorScheme != colorScheme) {
        m_config.colorScheme = colorScheme;
        emit colorSchemeChanged();
    }
}

ColorHelper::ColorHelper(QObject *parent) : QObject(parent) {

    if (auto theme = ThemeProvider::instance()) {
        connect(theme, &Theme::colorSchemeChanged, this,
                &ColorHelper::updateColor);

        connect(theme, &Theme::primaryShadeChanged, this,
                &ColorHelper::updateColor);
    }
}
