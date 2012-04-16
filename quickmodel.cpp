
#include "quickmodel.h"
#include <QDebug>

QuickModel::QuickModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


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

void QuickModel::setItemList(const QList<QVariantList> &items)
{
    emit beginResetModel();
    m_lst = items;
    emit endResetModel();
}

const QList<QVariantList>& QuickModel::items() const
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

int QuickModel::fieldIndex(const QString &fieldname)
{
    int ndx = -1;
    QByteArray roleName = fieldname.toAscii();
    QHashIterator<int, QByteArray> i(m_roleNames);
    while(i.findNext(roleName))
    {
        ndx = i.key();
    }
    return ndx;
}



void QuickModel::insert(int pos, const QVariantMap& item)
{
    QVariantList variantList;
    variantList = flatten(item);
    beginInsertRows(QModelIndex(), pos, pos);
    m_lst.insert(pos, variantList);
    endInsertRows();


}

void QuickModel::set(int pos, const QVariantMap &item)
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

    QMapIterator<QString, QVariant> i(map);

    while (i.hasNext()) {
        i.next();
        QString r = i.key();
        QVariant v = i.value();
        int ndx = m_rolesForKeys[r];
        res[ndx] = v;
        //qDebug() << i.key() << ": " << i.value() << endl;
    }
    return res;
}

QVariantMap QuickModel::get(int pos)
{
    QVariantList resLst = m_lst.at(pos);

    QVariantMap res;

    QHashIterator<QString, int> i(m_rolesForKeys);
    while(i.hasNext())
    {
        i.next();
        //QDebug() << "key: " << i.key() << " val"
        res[i.key()] = resLst.at(i.value());        
    }
    return res;
}

int QuickModel::count()
{
    return rowCount();
}

void QuickModel::clear()
{
    emit beginResetModel();
    m_lst.clear();
    emit endResetModel();
}

void QuickModel::remove(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    m_lst.removeAt(pos);
    endRemoveRows();
}

void QuickModel::setProperty(int pos, QString& property, QVariant value)
{
    QVariantList resLst = m_lst.at(pos);

    int ndx = fieldIndex(property);

    resLst[ndx] = value;

    m_lst.replace(pos, resLst);
    QModelIndex idx = createIndex(pos,0);
    emit dataChanged(idx, idx);
}


