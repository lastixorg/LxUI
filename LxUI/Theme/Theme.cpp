#include "Theme.hpp"

// THEME
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

// **** THEME GETTERS ****
// Color palette
QString Theme::white() const {
    return m_config.white;
}

QString Theme::black() const {
    return m_config.black;
}

QVariantMap Theme::colors() const {
    return m_config.colors;
}

QColor Theme::getColorValue(const QString &colorKey) const {
    if (!m_config.colors.contains(colorKey)) return QColor();

    QVariantList colors = m_config.colors[colorKey].toList();
    if (colors.isEmpty()) return QColor();

    int shadeIndex = (this->colorScheme() == Qt::ColorScheme::Dark) ?
                         m_config.primaryShade.dark() :
                         m_config.primaryShade.light();
    // cyclic indexing
    shadeIndex = ((shadeIndex % colors.size()) + colors.size()) % colors.size();

    return colors[shadeIndex].value<QColor>();
}

QColor Theme::getColorValue(const QString &colorKey, int shade) const {
    if (!m_config.colors.contains(colorKey)) return QColor();

    QVariantList colors = m_config.colors[colorKey].toList();
    if (colors.isEmpty()) return QColor();

    int shadeIndex = shade;
    // cyclic indexing
    shadeIndex = ((shadeIndex % colors.size()) + colors.size()) % colors.size();

    return colors[shadeIndex].value<QColor>();
}

ColorHelper *Theme::getColorHelper(const QString &colorKey) {
    if (!m_colorHelpercache.contains(colorKey)) {
        auto helper = new ColorHelper(this);
        helper->setColorKey(colorKey);
        m_colorHelpercache[colorKey] = helper;
    }
    return m_colorHelpercache[colorKey];
}

QString Theme::primaryColor() const {
    return m_config.primaryColor;
}

PrimaryShade Theme::primaryShade() const {
    return m_config.primaryShade;
}

// Typographu
float Theme::fontSize() const {
    return m_config.fontSize;
}

QVariantMap Theme::fontSizes() const {
    return m_config.fontSizes;
}

QVariantMap Theme::lineHeights() const {
    return m_config.lineHeights;
}

// Radius
QVariantMap Theme::radius() const {
    return m_config.radius;
}

QString Theme::defaultRadius() const {
    return m_config.defaultRadius;
}

// Contrast
bool Theme::autoContrast() const {
    return m_config.autoContrast;
}

float Theme::luminanceThreshold() const {
    return m_config.luminanceThreshold;
}

Qt::ColorScheme Theme::colorScheme() const {
    if (m_config.colorScheme != Qt::ColorScheme::Unknown) {
        return m_config.colorScheme;
    } else {
        // Use system color scheme or default to Light if unknown
        if (auto systemScheme = qApp->styleHints()->colorScheme();
            systemScheme != Qt::ColorScheme::Unknown)
            return systemScheme;
        return Qt::ColorScheme::Light;
    }
}

// **** THEME SETTERS ****
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


// THEME PROVIDER
Theme *ThemeProvider::instance() {
    if (!s_instance) qFatal("Theme not initialized!");

    return s_instance;
}

Theme *ThemeProvider::init(QObject *parent, const ThemeConfig &config) {
    return creator(parent, &config);
}

Theme *ThemeProvider::init(QObject *parent) {
    return creator(parent, nullptr);
}

Theme *ThemeProvider::create(QQmlEngine *, QJSEngine *engine) {
    auto instance = ThemeProvider::instance();

    Q_ASSERT(engine->thread() == s_instance->thread());

    if (s_engine) Q_ASSERT(engine == s_engine);
    else s_engine = engine;

    QJSEngine::setObjectOwnership(s_instance, QJSEngine::CppOwnership);
    return instance;
}

Theme *ThemeProvider::creator(QObject *parent, const ThemeConfig *config) {
    if (s_instance) qFatal("Theme already initialized!");
    s_instance = config ? new Theme(parent, *config) : new Theme(parent);
    return s_instance;
}


// COLOR HELPER
ColorHelper::ColorHelper(QObject *parent) : QObject(parent) {
    if (auto theme = ThemeProvider::instance()) {
        connect(theme, &Theme::colorSchemeChanged, this,
                &ColorHelper::updateColor);
        connect(theme, &Theme::primaryShadeChanged, this,
                &ColorHelper::updateColor);
    }
}

// **** COLOR HELPER GETTERS ****
QString ColorHelper::colorKey() const {
    return m_colorKey;
}

QColor ColorHelper::color() const {
    return m_color;
}

// **** COLOR HELPER SETTERS ****
void ColorHelper::setColorKey(const QString &key) {
    if (m_colorKey != key) {
        m_colorKey = key;
        emit colorKeyChanged();
        updateColor();
    }
}

void ColorHelper::updateColor() {
    if (!ThemeProvider::instance()) return;

    auto theme = ThemeProvider::instance();

    m_color = theme->getColorValue(m_colorKey);
    emit colorChanged();
}