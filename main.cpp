#include <QtCore/QCoreApplication>
#include <QDebug>
#include "quickmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QuickModel tstModel;

    QVariantMap tstData;
    tstData.insert( "key1", QVariant("first"));
    tstData.insert( "key2", QVariant("second"));


    return a.exec();
}
