#include "quickmodel.h"
#include <QDebug>
#include <QFile>

QuickModel::QuickModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


/*!
internal
*/
int QuickModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    int c = m_lst.count();
    return c;
}


/*!
    Returns the item's data for the given \a role, or an invalid
    QVariant if there is no data for the role.
*/
QVariant QuickModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_lst.size())
        return QVariant();

    const QVariantList& v = m_lst.at(index.row());
    QVariant va = v[role];
    return va;
}

/*!
internal
*/
void QuickModel::setItemList(const QList<QVariantList> &items)
{
    emit beginResetModel();
    m_lst = items;
    emit endResetModel();
}

/*!
internal
*/
const QList<QVariantList>& QuickModel::items() const
{
    return m_lst;
}

/*!
  Set \a fields aka rolenames for items
*/
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

/*!
internal
*/
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

/*!
tbd
*/
void QuickModel::sort(const QString &field, Qt::SortOrder order)
{
    Q_UNUSED(field);
    Q_UNUSED(order);
}



/*!
  Insert \a an item at \a position.
*/
void QuickModel::insert(int pos, const QVariantMap& item)
{
    QVariantList variantList;
    variantList = flatten(item);
    beginInsertRows(QModelIndex(), pos, pos);
    m_lst.insert(pos, variantList);
    endInsertRows();


}

/*!
  Set \a item at \a position.
*/
void QuickModel::set(int pos, const QVariantMap &item)
{
    QVariantList variantList;
    variantList = flatten(item);
    m_lst.replace(pos, variantList);
    QModelIndex idx = createIndex(pos,0);
    emit dataChanged(idx, idx);
}

/*!
  Append \a an item.
*/
void QuickModel::append(const QVariantMap& item)
{
    insert(m_lst.size(), item);
}



/*!
internal
*/
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

/*!
Returns the item for the given \a position if one has been set; otherwise returns an invalid QVariantMap
*/
QVariantMap QuickModel::get(int pos)
{
    QVariantList resLst = m_lst.at(pos);

    QVariantMap res = QVariantMap();

    QHashIterator<QString, int> i(m_rolesForKeys);
    while(i.hasNext())
    {
        i.next();
        res[i.key()] = resLst.at(i.value());
    }
    return res;
}

/*!
    Return the number of rows.
*/
int QuickModel::count()
{
    return rowCount();
}

/*!
    Clear model.
*/
void QuickModel::clear()
{
    emit beginResetModel();
    m_lst.clear();
    emit endResetModel();
}

/*!
    Remove item at \a position.
*/
void QuickModel::remove(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    m_lst.removeAt(pos);
    endRemoveRows();
}


/*!
    Sets the item data at given \a position for the given \a field to the specified \a value.
*/
void QuickModel::setProperty(int pos, QString property, QVariant value)
{
    QVariantList resLst = m_lst.at(pos);

    int ndx = fieldIndex(property);

    resLst[ndx] = value;

    m_lst.replace(pos, resLst);
    QModelIndex idx = createIndex(pos,0);
    emit dataChanged(idx, idx);
}

/*!
internal
*/
void QuickModel::save(QIODevice *device)
{
    QDataStream out(device);
    out << m_lst;
}

/*!
internal
*/
void QuickModel::restore(QIODevice *device)
{
    QDataStream in(device);
    QList<QVariantList> tmp;
    in >> tmp;
    setItemList(tmp);
}

/*!
    serialize the model data to file. \a File name
*/
void QuickModel::saveToFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    save(&file);
}

/*!
    read serialized model data from file. \a File name
*/
void QuickModel::restoreFromFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    restore(&file);
}


