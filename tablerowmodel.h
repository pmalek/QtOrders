#ifndef TABLEROWMODEL_H
#define TABLEROWMODEL_H

#include <QAbstractTableModel>

namespace TableRowModel_Constants{
    static const int TABLE_ORDERID_HEADER_ID 	= 0;
    static const int TABLE_COMPANY_HEADER_ID	= 1;
    static const int TABLE_ADDRESS_HEADER_ID	= 2;
    static const int TABLE_ORDER_ITEM_HEADER_ID	= 3;

    static const QString TABLE_ORDERID_HEADER		= "orderID";
    static const QString TABLE_COMPANY_HEADER		= "company";
    static const QString TABLE_ADDRESS_HEADER		= "address";
    static const QString TABLE_ORDER_ITEM_HEADER	= "item";
}

class TableRowModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableRowModel(QObject *parent = 0);
    TableRowModel(QVector<QStringList> _data, QObject *parent = 0);

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRow(int arow, const QModelIndex &aparent = QModelIndex());

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QStringList getUniqueCompanyNames() const;
    QStringList getUniqueAddresses() const;
    QStringList getUniqueOrderIds() const;
    QVector<QPair<QString, u_int16_t> > getOrderedItemsDescending() const;

    operator QVariant() const;

signals:

public slots:

private:
    QVector<QStringList> dataVector;
};

#endif // TABLEROWMODEL_H
