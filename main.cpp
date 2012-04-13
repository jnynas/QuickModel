#include <QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include "quickmodel.h"
#include "/modeltest/modeltest.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));


    QmlApplicationViewer viewer;
    QuickModel tstModel;
    //new ModelTest(tstModel, parent);

    tstModel.setFields(QStringList() << "key1" << "key2");
    QVariantMap tstData;
    QVariantMap tstData2;
    tstData.insert( "key1", QVariant("first"));
    tstData.insert( "key2", QVariant("second"));
    tstModel.append(tstData);

    tstData2.insert( "key1", QVariant("third"));
    tstData2.insert( "key2", QVariant("fourth"));
    tstModel.append(tstData2);
    tstData.clear();
    tstData.insert( "key1", QVariant("fifth"));
    tstData.insert( "key2", QVariant("sixth"));
    tstModel.append(tstData);



    viewer.engine()->rootContext()->setContextProperty("quickmdl", &tstModel);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QuickModelDemo/main.qml"));


    viewer.showExpanded();

    return app->exec();
}
