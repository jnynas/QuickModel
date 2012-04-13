
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


    const QList<QVariantList>& items() const;
    void setItemList(const QList<QVariantList> &items);
    void setFields(const QStringList &keys);


    // useful with QVariantList
    int fieldIndex(const QString& fieldname);
    //void sortBy(const QString& field);
    void sort (const QString& field, Qt::SortOrder order = Qt::AscendingOrder );

    // needed since we have items() anyway?
    QList<QVariantList> findItems (const QString& text, Qt::MatchFlags flags = Qt::MatchExactly, int column = 0 ) const;

    Q_INVOKABLE void append(const QVariantMap& item);
    Q_INVOKABLE void insert(int pos, const QVariantMap& item);
    Q_INVOKABLE void set(int pos, const QVariantMap& item);
    Q_INVOKABLE QVariantMap get(int pos);
    Q_INVOKABLE int count();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void remove(int pos);
    Q_INVOKABLE void setProperty(int pos, QString& property, QVariant value);

    // for testing


    Q_INVOKABLE void testInsert();

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;


   /* bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex &index) const;*/

    QVariant data(const QModelIndex &index, int role) const;

private:
    //int roleForKey(const QByteArray& key);
    QVariantList flatten(const QVariantMap& map);

private:
    Q_DISABLE_COPY(QuickModel)
    QList<QVariantList> m_lst;
    QHash<int, QByteArray> m_roleNames;
    QHash<QString, int> m_rolesForKeys;
};


#endif // QUICKMODEL_H
