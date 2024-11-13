#pragma once

#include <QFont>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <qcontainerfwd.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#include <unordered_map>


using ColorPalette = std::array<QString, 10>;
using Colors = std::unordered_map<QString, ColorPalette>;


namespace ColorMode {
    Q_NAMESPACE
    QML_ELEMENT
    enum Mode { Light, Dark };
    Q_ENUM_NS(Mode)
} // namespace ColorMode

namespace Radius {
    Q_NAMESPACE
    QML_ELEMENT
    enum Size { XS, SM, MD, LG, XL };
    Q_ENUM_NS(Size)
} // namespace Radius

struct PrimaryShade {
        int light;
        int dark;
};

struct ThemeConfig {
        QString white;
        QString black;
        // Colors colors;
        QString primaryColor;
        PrimaryShade primaryShade;

        double fontSize;
        QVariantMap headings;
        QVariantMap fontSizes;
        QVariantMap lineHeights;
        QVariantMap radius;


        bool autoContrast;
        double luminanceThreshold;
        ColorMode::Mode colorMode;
};

class Theme : public QObject {
        Q_OBJECT
        QML_SINGLETON
        QML_ELEMENT

        // Basic colors
        Q_PROPERTY(QString white READ white WRITE setWhite NOTIFY whiteChanged);
        Q_PROPERTY(QString black READ black WRITE setBlack NOTIFY blackChanged);

        // Q_PROPERTY(
        // Colors colors READ colors WRITE setColors NOTIFY colorsChanged);

        // Primary color
        Q_PROPERTY(QString primaryColor READ primaryColor WRITE setPrimaryColor
                       NOTIFY primaryColorChanged);
        Q_PROPERTY(PrimaryShade primaryShade READ primaryShade WRITE
                       setPrimaryShade NOTIFY primaryShadeChanged);

        // Fonts
        Q_PROPERTY(int defaultFontSize READ defaultFontSize CONSTANT);

        // Typography
        Q_PROPERTY(QVariantMap headings READ headings WRITE setHeadings NOTIFY
                       headingsChanged);
        Q_PROPERTY(QVariantMap fontSizes READ fontSizes WRITE setFontSizes
                       NOTIFY fontSizesChanged);
        Q_PROPERTY(QVariantMap lineHeights READ lineHeights WRITE setLineHeights
                       NOTIFY lineHeightsChanged);
        Q_PROPERTY(QVariantMap radius READ radius WRITE setRadius NOTIFY
                       radiusChanged);

        // Contrast
        Q_PROPERTY(bool autoContrast READ autoContrast WRITE setAutoContrast
                       NOTIFY autoContrastChanged);
        Q_PROPERTY(double luminanceThreshold READ luminanceThreshold WRITE
                       setLuminanceThreshold NOTIFY luminanceThresholdChanged);

    public:
        explicit Theme(QObject *parent = nullptr);

        QString white() const {
            return m_white;
        }
        QString black() const {
            return m_black;
        }
        QString primaryColor() const {
            return m_primaryColor;
        }
        PrimaryShade primaryShade() const {
            return m_primaryShade;
        }
        int defaultFontSize() const {
            return m_defaultFontSize;
        }
        QVariantMap headings() const {
            return m_headings;
        }
        QVariantMap fontSizes() const {
            return m_fontSizes;
        }
        QVariantMap lineHeights() const {
            return m_lineHeights;
        }
        QVariantMap radius() const {
            return m_radius;
        }
        bool autoContrast() const {
            return m_autoContrast;
        }
        double luminanceThreshold() const {
            return m_luminanceThreshold;
        }

        static Theme *createTheme(QQmlApplicationEngine &engine,
                                  const ThemeConfig &config);

    public slots:
        void setWhite(const QString &white);
        void setBlack(const QString &black);
        void setPrimaryColor(const QString &color);
        void setPrimaryShade(const PrimaryShade &shade);
        void setHeadings(const QVariantMap &headings);
        void setFontSizes(const QVariantMap &sizes);
        void setLineHeights(const QVariantMap &heights);
        void setRadius(const QVariantMap &radius);
        void setAutoContrast(bool contrast);
        void setLuminanceThreshold(double threshold);
        QString setColor(const QString &color, int shade);

    signals:
        void whiteChanged();
        void blackChanged();
        void primaryColorChanged();
        void primaryShadeChanged();
        void headingsChanged();
        void fontSizesChanged();
        void lineHeightsChanged();
        void radiusChanged();
        void autoContrastChanged();
        void luminanceThresholdChanged();

    private:
        Colors m_colors;

        QString m_white{"#ffffff"};
        QString m_black{"#000000"};
        QString m_primaryColor{"blue"};
        PrimaryShade m_primaryShade;
        int m_defaultFontSize{14};
        QVariantMap m_headings;
        QVariantMap m_fontSizes;
        QVariantMap m_lineHeights;
        QVariantMap m_radius;
        bool m_autoContrast{false};
        double m_luminanceThreshold{0.3};

        void initializeColors();
        void initializeDefaults();
};
