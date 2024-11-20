#pragma once

#include <QObject>
#include <QQmlEngine>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <qjsengine.h>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>


namespace ColorMode {
    Q_NAMESPACE
    QML_ELEMENT
    enum Mode { Light, Dark, Auto };
    Q_ENUM_NS(Mode)
} // namespace ColorMode


struct PrimaryShade {
        int light;
        int dark;
};


class Size : public QObject {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON

        Q_PROPERTY(QString xs READ xs CONSTANT);
        Q_PROPERTY(QString sm READ sm CONSTANT);
        Q_PROPERTY(QString md READ md CONSTANT);
        Q_PROPERTY(QString lg READ lg CONSTANT);
        Q_PROPERTY(QString xl READ xl CONSTANT);


    public:
        explicit Size(QObject *parent = nullptr);
        // Bidirectional conversion between QString and Size
        Size(QString value);
        operator QString() const {
            return m_value;
        }

        static QString xs() {
            return m_xs;
        }

        static QString sm() {
            return m_sm;
        }

        static QString md() {
            return m_md;
        }

        static QString lg() {
            return m_lg;
        }

        static QString xl() {
            return m_xl;
        }

    private:
        QString m_value;
        static QString m_xs;
        static QString m_sm;
        static QString m_md;
        static QString m_lg;
        static QString m_xl;
};


struct Defaults {
        static QString defaultWhite;
        static QString defaultBlack;
        static QString defaultPrimaryColor;
        static PrimaryShade defaultPrimaryShade;
        static QVariantMap defaultColors;
        static QVariantMap defaultLineHeights;
        static QVariantMap defaultRadiusValues;
};


struct ThemeConfig {

        // Color palette
        QString white = Defaults::defaultWhite;
        QString black = Defaults::defaultBlack;
        QVariantMap colors = Defaults::defaultColors;
        QString primaryColor = Defaults::defaultPrimaryColor;
        PrimaryShade primaryShade = Defaults::defaultPrimaryShade;

        // Typography
        float fontSize = 14.0;
        QVariantMap fontSizes = {{Size::xs(), fontSize * 0.857},
                                 {Size::sm(), fontSize},
                                 {Size::md(), fontSize * 1.143},
                                 {Size::lg(), fontSize * 1.286},
                                 {Size::xl(), fontSize * 1.571}};

        QVariantMap lineHeights = Defaults::defaultLineHeights;

        // Radius
        QVariantMap radius = Defaults::defaultRadiusValues;
        Size defaultRadius = Size::md();

        // Contrast
        bool autoContrast = true;
        float luminanceThreshold = 0.3;
        ColorMode::Mode colorMode = ColorMode::Auto;
};

class Theme : public QObject {
        Q_OBJECT

        // Color palette
        Q_PROPERTY(QString white READ white WRITE setWhite NOTIFY whiteChanged);
        Q_PROPERTY(QString black READ black WRITE setBlack NOTIFY blackChanged);
        Q_PROPERTY(QVariantMap colors READ colors WRITE setColors NOTIFY
                       colorsChanged);
        Q_PROPERTY(QString primaryColor READ primaryColor WRITE setPrimaryColor
                       NOTIFY primaryColorChanged);
        Q_PROPERTY(PrimaryShade primaryShade READ primaryShade WRITE
                       setPrimaryShade NOTIFY primaryShadeChanged);

        // Typography
        Q_PROPERTY(float fontSize READ fontSize WRITE setFontSize NOTIFY
                       fontSizeChanged);
        Q_PROPERTY(QVariantMap fontSizes READ fontSizes WRITE setFontSizes
                       NOTIFY fontSizesChanged);
        Q_PROPERTY(QVariantMap lineHeights READ lineHeights WRITE setLineHeights
                       NOTIFY lineHeightsChanged);

        // Radius
        Q_PROPERTY(QVariantMap radius READ radius WRITE setRadius NOTIFY
                       radiusChanged);
        Q_PROPERTY(QString defaultRadius READ defaultRadius WRITE
                       setDefaultRadius NOTIFY defaultRadiusChanged);

        // Contrast
        Q_PROPERTY(bool autoContrast READ autoContrast WRITE setAutoContrast
                       NOTIFY autoContrastChanged);
        Q_PROPERTY(float luminanceThreshold READ luminanceThreshold WRITE
                       setLuminanceThreshold NOTIFY luminanceThresholdChanged);
        Q_PROPERTY(ColorMode::Mode colorMode READ colorMode WRITE setColorMode
                       NOTIFY colorModeChanged);

    public:
        explicit Theme(QObject *parent = nullptr,
                       const ThemeConfig &config = ThemeConfig{});

        // Color palette
        QString white() const {
            return m_white;
        }
        QString black() const {
            return m_black;
        }
        QVariantMap colors() const {
            return m_colors;
        }
        QString primaryColor() const {
            return m_primaryColor;
        }
        PrimaryShade primaryShade() const {
            return m_primaryShade;
        }

        // Typography
        float fontSize() const {
            return m_fontSize;
        }
        QVariantMap fontSizes() const {
            return m_fontSizes;
        }
        QVariantMap lineHeights() const {
            return m_lineHeights;
        }

        // Radius
        QVariantMap radius() const {
            return m_radius;
        }
        const QString defaultRadius() const {
            return m_defaultRadius;
        }

        // Contrast
        bool autoContrast() const {
            return m_autoContrast;
        }
        float luminanceThreshold() const {
            return m_luminanceThreshold;
        }
        ColorMode::Mode colorMode() const {
            return m_colorMode;
        }

    public slots:

        // Color Palette
        void setWhite(const QString &white);
        void setBlack(const QString &black);
        void setColors(const QVariantMap &colors);
        void setPrimaryColor(const QString &primaryColor);
        void setPrimaryShade(const PrimaryShade &primaryShade);

        // Typography
        void setFontSize(const float fontSize);
        void setFontSizes(const QVariantMap &fontSizes);
        void setLineHeights(const QVariantMap &lineHeights);

        // Radius
        void setRadius(const QVariantMap &radius);
        void setDefaultRadius(const Size &defaultRadius);

        // Contrast
        void setAutoContrast(bool autoContrast);
        void setLuminanceThreshold(float luminanceThreshold);
        void setColorMode(ColorMode::Mode colorMode);

    signals:

        // Color palette
        void whiteChanged();
        void blackChanged();
        void colorsChanged();
        void primaryColorChanged();
        void primaryShadeChanged();

        // Typography
        void fontSizeChanged();
        void fontSizesChanged();
        void lineHeightsChanged();

        // Radius
        void radiusChanged();
        void defaultRadiusChanged();

        // Contrast
        void autoContrastChanged();
        void luminanceThresholdChanged();
        void colorModeChanged();

    private:
        // Color palette
        QString m_white;
        QString m_black;
        QVariantMap m_colors;
        QString m_primaryColor;
        PrimaryShade m_primaryShade;

        // Typography
        float m_fontSize;
        QVariantMap m_fontSizes;
        QVariantMap m_lineHeights;

        // Radius
        QVariantMap m_radius;
        QString m_defaultRadius;

        // Contrast
        bool m_autoContrast;
        float m_luminanceThreshold;
        ColorMode::Mode m_colorMode;
};

struct ThemeProvider {
        Q_GADGET
        QML_FOREIGN(Theme)
        QML_SINGLETON
        QML_NAMED_ELEMENT(Theme)
    public:
        static Theme *instance() {
            if (!s_instance) qFatal("Theme not initialized!");

            return s_instance;
        }

        static Theme *init(const ThemeConfig &config,
                           QObject *parent = nullptr) {
            if (s_instance) qFatal("Theme already initialized!");
            s_instance = new Theme(parent, config);

            return s_instance;
        }

        static Theme *create(QQmlEngine *, QJSEngine *engine) {
            auto instance = ThemeProvider::instance();

            Q_ASSERT(engine->thread() == s_instance->thread());

            if (s_engine) Q_ASSERT(engine == s_engine);
            else s_engine = engine;

            QJSEngine::setObjectOwnership(s_instance, QJSEngine::CppOwnership);
            return instance;
        }

    private:
        inline static Theme *s_instance = nullptr;
        inline static QJSEngine *s_engine = nullptr;
};