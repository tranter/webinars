#include <iostream>
#include <QFile>
#include <QGuiApplication>
#include <QtQuick>

#include "trafficlightdevice.h"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Registers type information with QML
    qmlRegisterUncreatableType<TrafficLight>("HighwayDivision",
                                             1,
                                             0,
                                             "TrafficLight",
                                             "Cannot instantiate TrafficLight");

    // We are exporting a single instance of light to QML
    TrafficLight light;

    TrafficLightDevice state(light);

    QQuickView viewer;
    viewer.rootContext()->setContextProperty("lightBackend", &light);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.show();

    return QGuiApplication::exec();
}
