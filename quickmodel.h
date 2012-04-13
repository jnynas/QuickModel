
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

    const QList<QVariantList>& items() const;
    void setItemList(const QList<QVariantList> &items);

    // useful with QVariantList
    int fieldIndex(const QString& fieldname);
    //void sortBy(const QString& field);
    void sort (const QString& field, Qt::SortOrder order = Qt::AscendingOrder );

    // needed since we have items() anyway?
    QList<QVariantList> findItems (const QString& text, Qt::MatchFlags flags = Qt::MatchExactly, int column = 0 ) const;

    Q_INVOKABLE void setFields(const QStringList &keys);
    Q_INVOKABLE void append(const QVariantMap& item);
    Q_INVOKABLE void insert(int pos, const QVariantMap& item);
    Q_INVOKABLE void set(int pos, const QVariantMap& item);
    Q_INVOKABLE QVariantMap get(int pos);
    Q_INVOKABLE int count();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void remove(int pos);
    Q_INVOKABLE void setProperty(int pos, QString& property, QVariant value);


protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

private:   
    QVariantList flatten(const QVariantMap& map);

private:
    Q_DISABLE_COPY(QuickModel)
    QList<QVariantList> m_lst;
    QHash<int, QByteArray> m_roleNames;
    QHash<QString, int> m_rolesForKeys;
};


#endif // QUICKMODEL_H
