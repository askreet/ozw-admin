
#include <QHeaderView>
#include <QMenu>
#include <qt-openzwave/qtopenzwave.h>
#include <qt-openzwave/qtozwmanager.h>

#include "ozwcore.h"
#include "util.h"
#include "value_delegate.h"
#include "valuetable.h"

ValueTable::ValueTable(QTOZW_ValueIds::ValueIdGenres genre, QWidget *parent)
    : QTableView(parent)
{
    Value_Delegate *delegate = new Value_Delegate(this);
    this->m_genre = genre;

    this->m_proxyModel = new QTOZW_proxyValueModel(this);
    this->m_proxyModel->setFilterGenre(this->m_genre);

    this->setItemDelegateForColumn(QTOZW_ValueIds::ValueIdColumns::Value,
                                   delegate);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSortingEnabled(true);
    this->horizontalHeader()->setSectionsMovable(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTableView::customContextMenuRequested,
            this, &ValueTable::rightClickMenu);
}

void ValueTable::setModel(QAbstractItemModel *model,
                          QItemSelectionModel *selectionModel)
{
    this->m_proxyModel->setSourceModel(model);
    this->m_proxyModel->setSelectionModel(selectionModel);

    //    connect(selectionModel, &QItemSelectionModel::currentRowChanged, this,
    //    &ValueTable::logChanges);
    QTableView::setModel(this->m_proxyModel);
    /* move the Instance Column to the first entry */
    this->horizontalHeader()->moveSection(
        QTOZW_ValueIds::ValueIdColumns::Instance, 0);

    for (int i = 0; i <= QTOZW_ValueIds::ValueIdColumns::ValueIdCount; i++) {
        switch (i) {
        case QTOZW_ValueIds::ValueIdColumns::Label:
        case QTOZW_ValueIds::ValueIdColumns::Value:
        case QTOZW_ValueIds::ValueIdColumns::Instance:
        case QTOZW_ValueIds::ValueIdColumns::Help:
            this->horizontalHeader()->setSectionResizeMode(
                i, QHeaderView::ResizeToContents);
            break;
        default:
            this->horizontalHeader()->hideSection(i);
            break;
        }
    }
}

void ValueTable::rightClickMenu(QPoint pos)
{
    QModelIndex index = this->indexAt(pos);

    if (index.isValid()) {
        quint64 valueIdKey = index.model()->index(index.row(), QTOZW_ValueIds::ValueIdColumns::ValueIDKey, index.parent()).data().toULongLong();

        QMenu *menu = new QMenu(this);
        auto mgr = OZWCore::get()->getQTOZWManager();

        if (mgr->isValuePolled(valueIdKey)) {
            menu->addAction("Disable Polling", this, [mgr, valueIdKey] {
                bool result = mgr->disablePoll(valueIdKey);
                qCDebug(ozwadmin) << "disablePoll" << result;
            });
        } else {
            menu->addAction("Enable Polling", this, [mgr, valueIdKey] {
                bool result = mgr->enablePoll(valueIdKey, 1);
                qCDebug(ozwadmin) << "enablePoll" << result;
            });
        }


        menu->popup(this->viewport()->mapToGlobal(pos));
    }
}

void forEach(QAbstractItemModel *model, QModelIndex parent = QModelIndex())
{
    for (int r = 0; r < model->rowCount(parent); ++r) {
        qCDebug(ozwadmin)
            << "\t\t"
            << model->data(model->index(r, QTOZW_ValueIds::Node, parent))
                   .toInt()
            << model->data(model->index(r, QTOZW_ValueIds::Genre, parent))
                   .toInt();
    }
}

void ValueTable::logChanges(const QModelIndex &current,
                            const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    qCDebug(ozwadmin) << "SelectionChanged UnFiltered Rows:"
                      << this->m_proxyModel->sourceModel()->rowCount();
    qCDebug(ozwadmin) << "\t Filter Node:"
                      << this->m_proxyModel->getCurrentFilteredNode();
    qCDebug(ozwadmin) << "\t Genre Filter:"
                      << (int)this->m_proxyModel->getFilterGenre();
    qCDebug(ozwadmin) << "\t Filtered Rows: " << this->m_proxyModel->rowCount();
    qCDebug(ozwadmin) << "\t TableView Rows:"
                      << QTableView::model()->rowCount();
    forEach(this->m_proxyModel->sourceModel());
}
