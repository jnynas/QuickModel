
#ifndef QUICKMODEL_H
#define QUICKMODEL_H

#include <QAbstractListModel>
#include <QVariantMap>
#include <QStringList>


class QuickModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QuickModel(QObject *parent = 0);
    //QuickModel(const QList<QVariantMap> &items, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    QList<QVariantList> itemList() const;
    void setItemList(const QList<QVariantList> &items);

    void setKeys(const QStringList &keys);
    void insert(int pos, const QVariantMap& item);
    void append(const QVariantMap& item);

private:
    int roleForKey(const QByteArray& key);
    QVariantList flatten(const QVariantMap& map);

private:
    Q_DISABLE_COPY(QuickModel)
    QList<QVariantList> m_lst;
    QHash<int, QByteArray> roleNames;
    QHash<QString, int> m_rolesForKeys;
};


#endif // QUICKMODEL_H
