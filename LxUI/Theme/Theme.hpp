#pragma once

// TODO: remove unnecessary includes
#include <QObject>
#include <QQmlEngine>
#include <qassert.h>
#include <qcontainerfwd.h>
#include <qjsengine.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qstylehints.h>
#include <qtmetamacros.h>
#include <QColor>
#include <QStyleHints>
#include <QGuiApplication>


class PrimaryShade {
        Q_GADGET

        Q_PROPERTY(int light READ light);
        Q_PROPERTY(int dark READ dark);
        QML_VALUE_TYPE(primaryShade)
    public:
        PrimaryShade() : m_light(6), m_dark(8){};
        explicit PrimaryShade(int l, int d) : m_light(l), m_dark(d){};

        int light() const {
            return m_light;
        }
        int dark() const {
            return m_dark;
        }

    private:
        int m_light;
        int m_dark;
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
        QString defaultRadius = Size::md();

        // Contrast
        bool autoContrast = true;
        float luminanceThreshold = 0.3;
        Qt::ColorScheme colorScheme =
            Qt::ColorScheme::Unknown; // Unknown for system theme
};

class ColorHelper;
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
        Q_PROPERTY(Qt::ColorScheme colorScheme READ colorScheme WRITE
                       setColorScheme NOTIFY colorSchemeChanged);

    public:
        explicit Theme(QObject *parent, const ThemeConfig &config);
        explicit Theme(QObject *parent);

        // Color palette
        QString white() const;
        QString black() const;
        QVariantMap colors() const;
        Q_INVOKABLE QColor getColorValue(const QString &colorKey) const;
        Q_INVOKABLE QColor getColorValue(const QString &colorKey,
                                         int shade) const;
        Q_INVOKABLE ColorHelper *getColorHelper(const QString &colorKey);
        QString primaryColor() const;
        PrimaryShade primaryShade() const;

        // Typography
        float fontSize() const;
        QVariantMap fontSizes() const;
        QVariantMap lineHeights() const;

        // Radius
        QVariantMap radius() const;
        QString defaultRadius() const;

        // Contrast
        bool autoContrast() const;
        float luminanceThreshold() const;
        Qt::ColorScheme colorScheme() const;

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
        void setColorScheme(Qt::ColorScheme colorScheme);

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
        void colorSchemeChanged();

    private:
        ThemeConfig m_config{};
        QMap<QString, ColorHelper *> m_colorHelpercache;
};

struct ThemeProvider {
        Q_GADGET
        QML_FOREIGN(Theme);
        QML_SINGLETON
        QML_NAMED_ELEMENT(Theme);

    public:
        static Theme *instance();
        static Theme *init(QObject *parent, const ThemeConfig &config);
        static Theme *init(QObject *parent);
        static Theme *create(QQmlEngine *, QJSEngine *engine);

    private:
        static Theme *creator(QObject *parent, const ThemeConfig *config);

        inline static Theme *s_instance = nullptr;
        inline static QJSEngine *s_engine = nullptr;
};

class ColorHelper : public QObject {
        Q_OBJECT
        QML_ELEMENT
        Q_PROPERTY(QString colorKey READ colorKey WRITE setColorKey NOTIFY
                       colorKeyChanged);
        Q_PROPERTY(QColor color READ color NOTIFY colorChanged);

    public:
        explicit ColorHelper(QObject *parent = nullptr);

        QString colorKey() const;
        void setColorKey(const QString &key);

        QColor color() const;

    signals:
        void colorKeyChanged();
        void colorChanged();

    private slots:
        void updateColor();

    private:
        QString m_colorKey;
        QColor m_color;
};
