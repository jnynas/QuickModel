
#ifndef QUICKMODEL_H
#define QUICKMODEL_H

#include <QAbstractListModel>
#include <QVariantMap>


class QuickModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QuickModel(QObject *parent = 0);
    QuickModel(const QList<QVariantMap> &items, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    QList<QVariantMap> itemList() const;
    void setItemList(const QList<QVariantMap> &items);

private:
    Q_DISABLE_COPY(QuickModel)
    QList<QVariantMap> lst;
};


#endif // QUICKMODEL_H
