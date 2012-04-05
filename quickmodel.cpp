
#include "quickmodel.h"


QuickModel::QuickModel(QObject *parent)
    : QAbstractListModel(parent)
{
}



/*QuickModel::QuickModel(const QList<QVariantList> &items, QObject *parent )
    : QAbstractListModel(parent), lst(items)
{
}*/






int QuickModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_lst.count();
}



QVariant QuickModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_lst.size())
        return QVariant();

    const QVariantList& v = m_lst.at(index.row());
    return v[role];

    /*

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return

    return QVariant();
    */
}



Qt::ItemFlags QuickModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}



bool QuickModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < m_lst.size()
            && (role == Qt::EditRole || role == Qt::DisplayRole)) {
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
}


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

void QuickModel::setKeys(const QStringList &keys)
{
    m_roleNames.clear();

    QString role;
    //int i = Qt::UserRole + 1;
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
    beginInsertRows(QModelIndex(), rowCount(), rowCount()+variantList.count());
    m_lst.insert(pos, variantList);
    endInsertRows();
}

void QuickModel::append(const QVariantMap& item)
{
    insert(m_lst.size(), item);
}


/*int QuickModel::roleForKey(const QByteArray& key)
{
    QHashIterator<int, QByteArray> iter(m_roleNames);
    while(iter.hasNext())
    {
        iter.next();
        if(iter.value() == key)
        {
            return iter.key();
        }
    }
    qCritical("shite");
    return -1;
}*/

QVariantList QuickModel::flatten(const QVariantMap &map)
{
    QVariantList res;
    res.reserve(m_rolesForKeys.count());
    for (int i=0; i < m_rolesForKeys.count(); ++i) {
        res.append(QVariant());
    }

    //QVariantMap::Iterator i(map);
    QMapIterator<QString, QVariant> i(map);

    while (i.hasNext()) {
        i.next();
        QString r = i.key();
        QVariant v = i.value();
        int ndx = m_rolesForKeys[r];
        res[ndx] = v;
        //cout << i.key() << ": " << i.value() << endl;
    }
    return res;
}
