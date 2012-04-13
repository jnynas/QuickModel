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

    viewer.engine()->rootContext()->setContextProperty("quickmdl", &tstModel);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QuickModelDemo/main.qml"));


    viewer.showExpanded();

    return app->exec();
}
