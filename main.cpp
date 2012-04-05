#include <QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include "quickmodel.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    QuickModel tstModel;

    tstModel.setKeys(QStringList() << "key1" << "key2");
    QVariantMap tstData;
    tstData.insert( "key1", QVariant("first"));
    tstData.insert( "key2", QVariant("second"));
    tstModel.append(tstData);
    tstData.clear();
    tstData.insert( "key1", QVariant("third"));
    tstData.insert( "key2", QVariant("fourth"));
    tstModel.append(tstData);

    viewer.engine()->rootContext()->setContextProperty("quickmdl", &tstModel);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QuickModelDemo/main.qml"));


    viewer.showExpanded();

    return app->exec();
}
