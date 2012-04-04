
#include "quickmodel.h"


QuickModel::QuickModel(QObject *parent)
    : QAbstractListModel(parent)
{
}



QuickModel::QuickModel(const QList<QVariantMap> &items, QObject *parent )
    : QAbstractListModel(parent), lst(items)
{
}



int QuickModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return lst.count();
}



QVariant QuickModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= lst.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return lst.at(index.row());

    return QVariant();
}



Qt::ItemFlags QuickModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}



bool QuickModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < lst.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole)) {
        lst.replace(index.row(), value.toMap());
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
        lst.insert(row, QVariantMap());

    endInsertRows();

    return true;
}



bool QuickModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        lst.removeAt(row);

    endRemoveRows();

    return true;
}


void QuickModel::setItemList(const QList<QVariantMap> &items)
{
    emit beginResetModel();
    lst = items;
    emit endResetModel();
}

QList<QVariantMap> QuickModel::itemList() const
{
    return lst;
}

