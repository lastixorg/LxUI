#include "Theme.hpp"
#include <qcontainerfwd.h>


// **** SIZE ****
Size::Size(QObject *parent) : QObject(parent) {
}
Size::Size(QString value) : m_value(std::move(value)) {
}

// Initialize static members
QString Size::m_xs = "xs";
QString Size::m_sm = "sm";
QString Size::m_md = "md";
QString Size::m_lg = "lg";
QString Size::m_xl = "xl";


// **** DEFAULTS ****
QString Defaults::defaultWhite = "#ffffff";
QString Defaults::defaultBlack = "#000000";
QString Defaults::defaultPrimaryColor = "blue";
PrimaryShade Defaults::defaultPrimaryShade = {.light = 8, .dark = 6};

QVariantMap Defaults::defaultColors = {
    {"dark",
     QStringList{"#C9C9C9", "#b8b8b8", "#828282", "#696969", "#424242",
                 "#3b3b3b", "#2e2e2e", "#242424", "#1f1f1f", "#141414"}},
    {"gray",
     QStringList{"#f8f9fa", "#f1f3f5", "#e9ecef", "#dee2e6", "#ced4da",
                 "#adb5bd", "#868e96", "#495057", "#343a40", "#212529"}},
    {"red", QStringList{"#fff5f5", "#ffe3e3", "#ffc9c9", "#ffa8a8", "#ff8787",
                        "#ff6b6b", "#fa5252", "#f03e3e", "#e03131", "#c92a2a"}},
    {"pink",
     QStringList{"#fff0f6", "#ffdeeb", "#fcc2d7", "#faa2c1", "#f783ac",
                 "#f06595", "#e64980", "#d6336c", "#c2255c", "#a61e4d"}},
    {"grape",
     QStringList{"#f8f0fc", "#f3d9fa", "#eebefa", "#e599f7", "#da77f2",
                 "#cc5de8", "#be4bdb", "#ae3ec9", "#9c36b5", "#862e9c"}},
    {"violet",
     QStringList{"#f3f0ff", "#e5dbff", "#d0bfff", "#b197fc", "#9775fa",
                 "#845ef7", "#7950f2", "#7048e8", "#6741d9", "#5f3dc4"}},
    {"indigo",
     QStringList{"#edf2ff", "#dbe4ff", "#bac8ff", "#91a7ff", "#748ffc",
                 "#5c7cfa", "#4c6ef5", "#4263eb", "#3b5bdb", "#364fc7"}},
    {"blue",
     QStringList{"#e7f5ff", "#d0ebff", "#a5d8ff", "#74c0fc", "#4dabf7",
                 "#339af0", "#228be6", "#1c7ed6", "#1971c2", "#1864ab"}},
    {"cyan",
     QStringList{"#e3fafc", "#c5f6fa", "#99e9f2", "#66d9e8", "#3bc9db",
                 "#22b8cf", "#15aabf", "#1098ad", "#0c8599", "#0b7285"}},
    {"teal",
     QStringList{"#e6fcf5", "#c3fae8", "#96f2d7", "#63e6be", "#38d9a9",
                 "#20c997", "#12b886", "#0ca678", "#099268", "#087f5b"}},
    {"green",
     QStringList{"#ebfbee", "#d3f9d8", "#b2f2bb", "#8ce99a", "#69db7c",
                 "#51cf66", "#40c057", "#37b24d", "#2f9e44", "#2b8a3e"}},
    {"lime",
     QStringList{"#f4fce3", "#e9fac8", "#d8f5a2", "#c0eb75", "#a9e34b",
                 "#94d82d", "#82c91e", "#74b816", "#66a80f", "#5c940d"}},
    {"yellow",
     QStringList{"#fff9db", "#fff3bf", "#ffec99", "#ffe066", "#ffd43b",
                 "#fcc419", "#fab005", "#f59f00", "#f08c00", "#e67700"}},
    {"orange",
     QStringList{"#fff4e6", "#ffe8cc", "#ffd8a8", "#ffc078", "#ffa94d",
                 "#ff922b", "#fd7e14", "#f76707", "#e8590c", "#d9480f"}}};

QVariantMap Defaults::defaultLineHeights = {{Size::xs(), 1.2},
                                            {Size::sm(), 1.3},
                                            {Size::md(), 1.4},
                                            {Size::lg(), 1.5},
                                            {Size::xl(), 1.6}};

QVariantMap Defaults::defaultRadiusValues = {{Size::xs(), 2},
                                             {Size::sm(), 4},
                                             {Size::md(), 8},
                                             {Size::lg(), 16},
                                             {Size::xl(), 32}};