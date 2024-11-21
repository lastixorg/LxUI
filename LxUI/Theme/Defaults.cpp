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
     QVariantList{QColor("#C9C9C9"), QColor("#b8b8b8"), QColor("#828282"),
                  QColor("#696969"), QColor("#424242"), QColor("#3b3b3b"),
                  QColor("#2e2e2e"), QColor("#242424"), QColor("#1f1f1f"),
                  QColor("#141414")}},
    {"gray",
     QVariantList{QColor("#f8f9fa"), QColor("#f1f3f5"), QColor("#e9ecef"),
                  QColor("#dee2e6"), QColor("#ced4da"), QColor("#adb5bd"),
                  QColor("#868e96"), QColor("#495057"), QColor("#343a40"),
                  QColor("#212529")}},
    {"red",
     QVariantList{QColor("#fff5f5"), QColor("#ffe3e3"), QColor("#ffc9c9"),
                  QColor("#ffa8a8"), QColor("#ff8787"), QColor("#ff6b6b"),
                  QColor("#fa5252"), QColor("#f03e3e"), QColor("#e03131"),
                  QColor("#c92a2a")}},
    {"pink",
     QVariantList{QColor("#fff0f6"), QColor("#ffdeeb"), QColor("#fcc2d7"),
                  QColor("#faa2c1"), QColor("#f783ac"), QColor("#f06595"),
                  QColor("#e64980"), QColor("#d6336c"), QColor("#c2255c"),
                  QColor("#a61e4d")}},
    {"grape",
     QVariantList{QColor("#f8f0fc"), QColor("#f3d9fa"), QColor("#eebefa"),
                  QColor("#e599f7"), QColor("#da77f2"), QColor("#cc5de8"),
                  QColor("#be4bdb"), QColor("#ae3ec9"), QColor("#9c36b5"),
                  QColor("#862e9c")}},
    {"violet",
     QVariantList{QColor("#f3f0ff"), QColor("#e5dbff"), QColor("#d0bfff"),
                  QColor("#b197fc"), QColor("#9775fa"), QColor("#845ef7"),
                  QColor("#7950f2"), QColor("#7048e8"), QColor("#6741d9"),
                  QColor("#5f3dc4")}},
    {"indigo",
     QVariantList{QColor("#edf2ff"), QColor("#dbe4ff"), QColor("#bac8ff"),
                  QColor("#91a7ff"), QColor("#748ffc"), QColor("#5c7cfa"),
                  QColor("#4c6ef5"), QColor("#4263eb"), QColor("#3b5bdb"),
                  QColor("#364fc7")}},
    {"blue",
     QVariantList{QColor("#e7f5ff"), QColor("#d0ebff"), QColor("#a5d8ff"),
                  QColor("#74c0fc"), QColor("#4dabf7"), QColor("#339af0"),
                  QColor("#228be6"), QColor("#1c7ed6"), QColor("#1971c2"),
                  QColor("#1864ab")}},
    {"cyan",
     QVariantList{QColor("#e3fafc"), QColor("#c5f6fa"), QColor("#99e9f2"),
                  QColor("#66d9e8"), QColor("#3bc9db"), QColor("#22b8cf"),
                  QColor("#15aabf"), QColor("#1098ad"), QColor("#0c8599"),
                  QColor("#0b7285")}},
    {"teal",
     QVariantList{QColor("#e6fcf5"), QColor("#c3fae8"), QColor("#96f2d7"),
                  QColor("#63e6be"), QColor("#38d9a9"), QColor("#20c997"),
                  QColor("#12b886"), QColor("#0ca678"), QColor("#099268"),
                  QColor("#087f5b")}},
    {"green",
     QVariantList{QColor("#ebfbee"), QColor("#d3f9d8"), QColor("#b2f2bb"),
                  QColor("#8ce99a"), QColor("#69db7c"), QColor("#51cf66"),
                  QColor("#40c057"), QColor("#37b24d"), QColor("#2f9e44"),
                  QColor("#2b8a3e")}},
    {"lime",
     QVariantList{QColor("#f4fce3"), QColor("#e9fac8"), QColor("#d8f5a2"),
                  QColor("#c0eb75"), QColor("#a9e34b"), QColor("#94d82d"),
                  QColor("#82c91e"), QColor("#74b816"), QColor("#66a80f"),
                  QColor("#5c940d")}},
    {"yellow",
     QVariantList{QColor("#fff9db"), QColor("#fff3bf"), QColor("#ffec99"),
                  QColor("#ffe066"), QColor("#ffd43b"), QColor("#fcc419"),
                  QColor("#fab005"), QColor("#f59f00"), QColor("#f08c00"),
                  QColor("#e67700")}},
    {"orange",
     QVariantList{QColor("#fff4e6"), QColor("#ffe8cc"), QColor("#ffd8a8"),
                  QColor("#ffc078"), QColor("#ffa94d"), QColor("#ff922b"),
                  QColor("#fd7e14"), QColor("#f76707"), QColor("#e8590c"),
                  QColor("#d9480f")}}};


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