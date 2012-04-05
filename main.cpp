#include <QtCore/QCoreApplication>
#include <QDebug>
#include "quickmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QuickModel tstModel;

    QStringList roles;
    roles << "key1" << "key2";

    tstModel.setKeys(roles);

    QVariantMap tstData;
    tstData.insert( "key1", QVariant("first"));
    tstData.insert( "key2", QVariant("second"));
    tstModel.append(tstData);

    return a.exec();
}
