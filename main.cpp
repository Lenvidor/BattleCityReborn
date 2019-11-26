#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "src/registrar.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Registrar::registerQMLTypes();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    return app.exec();
}
