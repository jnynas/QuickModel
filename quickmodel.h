/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

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


    int fieldIndex(const QString& fieldname);
    void sort (const QString& field, Qt::SortOrder order = Qt::AscendingOrder );

    QList<QVariantList> findItems (const QString& text, Qt::MatchFlags flags = Qt::MatchExactly, int column = 0 ) const;

    Q_INVOKABLE void setFields(const QStringList &keys);
    Q_INVOKABLE void append(const QVariantMap& item);
    Q_INVOKABLE void insert(int pos, const QVariantMap& item);
    Q_INVOKABLE void set(int pos, const QVariantMap& item);
    Q_INVOKABLE QVariantMap get(int pos);
    Q_INVOKABLE int count();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void remove(int pos);


    Q_INVOKABLE void setProperty(int pos, QString property, QVariant value);

    Q_INVOKABLE void saveToFile(QString fileName);
    Q_INVOKABLE void restoreFromFile(QString fileName);



protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QVariantList flatten(const QVariantMap& map);
    void save(QIODevice *device);
    void restore(QIODevice *device);

private:
    Q_DISABLE_COPY(QuickModel)
    QList<QVariantList> m_lst;
    QHash<int, QByteArray> m_roleNames;
    QHash<QString, int> m_rolesForKeys;
};



#endif // QUICKMODEL_H
