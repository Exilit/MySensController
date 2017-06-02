#include "Controller.h"
#include "BinarySensor.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("Exilit");
    app.setOrganizationDomain("exilit.de");
    app.setApplicationName("MySensors Controller");

    qmlRegisterType<Controller>("de.exilit.mysenscontroller", 1, 0, "Controller");
    qmlRegisterType<BinarySensor>("de.exilit.mysenscontroller", 1, 0, "Sensor");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
