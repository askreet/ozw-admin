#ifndef VALUETABLE_H
#define VALUETABLE_H

#include <QTableView>
#include <qt-openzwave/qtozwproxymodels.h>

class ValueTable : public QTableView
{
public:
    ValueTable(QTOZW_ValueIds::ValueIdGenres genre, QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model, QItemSelectionModel *selectionModel);

signals:
    void customContextMenuRequested(QPoint);

public slots:
    void rightClickMenu(QPoint pos);

private slots:
    void logChanges(const QModelIndex &current, const QModelIndex &previous);

private:
    QTOZW_proxyValueModel *m_proxyModel;
    QTOZW_ValueIds::ValueIdGenres m_genre;
};

#endif // VALUETABLE_H
