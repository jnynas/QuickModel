
#include "quickmodel.h"
#include <QDebug>

QuickModel::QuickModel(QObject *parent)
    : QAbstractListModel(parent)
{
}



/*QuickModel::QuickModel(const QList<QVariantList> &items, QObject *parent )
    : QAbstractListModel(parent), lst(items)
{
}*/



/*Qt::ItemFlags QuickModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}*/


int QuickModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    int c = m_lst.count();
    return c;
}



QVariant QuickModel::data(const QModelIndex &index, int role) const
{    
    if (index.row() < 0 || index.row() >= m_lst.size())
           return QVariant();

   const QVariantList& v = m_lst.at(index.row());
   QVariant va = v[role];
   qDebug() << va;
   return va;
}



/*bool QuickModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < m_lst.size())
    {
        m_lst.replace(index.row(), value.toList());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


bool QuickModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        m_lst.insert(row, QVariantList());

    endInsertRows();

    return true;
}



bool QuickModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        m_lst.removeAt(row);

    endRemoveRows();

    return true;
}*/


void QuickModel::setItemList(const QList<QVariantList> &items)
{
    emit beginResetModel();
    m_lst = items;
    emit endResetModel();
}

QList<QVariantList> QuickModel::itemList() const
{
    return m_lst;
}

void QuickModel::setFields(const QStringList &keys)
{
    m_roleNames.clear();

    QString role;

    int i=0;
    foreach(role, keys)
    {
        m_roleNames[i] = role.toAscii();
        m_rolesForKeys[role] = i;
        ++i;
    }
    setRoleNames(m_roleNames);
}



void QuickModel::insert(int pos, const QVariantMap& item)
{
    QVariantList variantList;
    variantList = flatten(item);
    beginInsertRows(QModelIndex(), pos, pos);
    m_lst.insert(pos, variantList);
    endInsertRows();


}

void QuickModel::setItem(int pos, const QVariantMap &item)
{
    QVariantList variantList;
    variantList = flatten(item);    
    m_lst.replace(pos, variantList);
    QModelIndex idx = createIndex(pos,0);
    emit dataChanged(idx, idx);
}

void QuickModel::append(const QVariantMap& item)
{
    insert(m_lst.size(), item);



}




QVariantList QuickModel::flatten(const QVariantMap &map)
{
    QVariantList res;
    res.reserve(m_rolesForKeys.count());
    for (int i=0; i < m_rolesForKeys.count(); ++i) {
        res.append(QVariant());
    }

    //QVariantMap::Iterator i(map);
    QMapIterator<QString, QVariant> i(map);
    int ndx = 0;
    while (i.hasNext()) {
        i.next();
        QString r = i.key();
        QVariant v = i.value();
        //int ndx = m_rolesForKeys[r];
        res[ndx] = v;
        ndx++;
        qDebug() << i.key() << ": " << i.value() << endl;
    }
    return res;
}

void QuickModel::testInsert()
{
    QVariantMap tstData;

    tstData.insert( "key1", QVariant("firstInsert"));
    tstData.insert( "key2", QVariant("secondInsert"));

    insert(0, tstData);

}
