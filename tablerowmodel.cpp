#include "tablerowmodel.h"
#include <QDebug>

TableRowModel::TableRowModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

TableRowModel::TableRowModel(QVector<QStringList> _data, QObject *parent)
{
   dataVector = _data;
}

int TableRowModel::columnCount(const QModelIndex &parent) const
{
    //TODO change for flexibility
    return 4;
}

int TableRowModel::rowCount(const QModelIndex &parent) const
{
    return dataVector.size();
}

bool TableRowModel::removeRow(int arow, const QModelIndex &aparent)
{
    beginRemoveRows(QModelIndex(), arow, arow);
    dataVector.removeAt(arow);
    endRemoveRows();
    return true;
}

QVariant TableRowModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignLeft;
    }

    if (role == Qt::DisplayRole){
        if (index.isValid()){
                QStringList row = dataVector.at(index.row());
                return row.at(index.column());
        }
    }

    return QVariant();
}

QVariant TableRowModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
        case TableRowModel_Constants::TABLE_ORDERID_HEADER_ID:
            return TableRowModel_Constants::TABLE_ORDERID_HEADER;
        case TableRowModel_Constants::TABLE_COMPANY_HEADER_ID:
            return TableRowModel_Constants::TABLE_COMPANY_HEADER;
        case TableRowModel_Constants::TABLE_ADDRESS_HEADER_ID:
            return TableRowModel_Constants::TABLE_ADDRESS_HEADER;
        case TableRowModel_Constants::TABLE_ORDER_ITEM_HEADER_ID:
            return TableRowModel_Constants::TABLE_ORDER_ITEM_HEADER;
        default:
            return QVariant();
    }
    return QVariant();
}

QStringList TableRowModel::getUniqueCompanyNames() const
{
    QStringList companiesList;
    for( QVector<QStringList>::const_iterator it = dataVector.begin();
         it < dataVector.end(); ++it){
        QString thisCompany = it->at(TableRowModel_Constants::TABLE_COMPANY_HEADER_ID);
        if ( ! companiesList.contains(thisCompany) ){
            companiesList.append(thisCompany);
        }
    }
    return companiesList;
}

QStringList TableRowModel::getUniqueAddresses() const
{
    QStringList addressList;
    for( QVector<QStringList>::const_iterator it = dataVector.begin();
         it < dataVector.end(); ++it){
        QString thisAddress = it->at(TableRowModel_Constants::TABLE_ADDRESS_HEADER_ID);
        if ( ! addressList.contains(thisAddress) ){
            addressList.append(thisAddress);
        }
    }
    return addressList;
}

QStringList TableRowModel::getUniqueOrderIds() const
{
    QStringList orderIDList;
    for( QVector<QStringList>::const_iterator it = dataVector.begin();
         it < dataVector.end(); ++it){
        QString thisOrderID = it->at(TableRowModel_Constants::TABLE_ORDERID_HEADER_ID);
        if ( ! orderIDList.contains(thisOrderID) ){
            orderIDList.append(thisOrderID);
        }
    }
    return orderIDList;
}

QVector<QPair<QString, u_int16_t> > TableRowModel::getOrderedItemsDescending() const
{
    QHash<QString, u_int16_t> hashItems;
    for( QVector<QStringList>::const_iterator it = dataVector.begin();
         it < dataVector.end(); ++it){
        QString thisItemName = it->at(TableRowModel_Constants::TABLE_ORDER_ITEM_HEADER_ID);
        QHash<QString, u_int16_t>::iterator itHash = hashItems.find(thisItemName);
        if ( itHash != hashItems.end()){
            ++itHash.value();
        } else {
           hashItems.insert(thisItemName, 1);
        }
    }

    QVector<QPair<QString, u_int16_t> > itemsOrderedDescending;
    u_int16_t tempMax = 0;
    QString tempMaxString = "";
    u_int16_t hashItemsSize = hashItems.size();
    for( int i = 0; i < hashItemsSize; ++i){
        QHash<QString, u_int16_t>::iterator it = hashItems.begin(),
                                            toRemove;
        while (it != hashItems.end()) {
            if(it.value() > tempMax){
                tempMax = it.value();
                tempMaxString = it.key();
                toRemove = it;
            }
            ++it;
        }
        hashItems.erase(toRemove);
        QPair<QString, u_int16_t> pair(tempMaxString, tempMax);
        itemsOrderedDescending.append(pair);
        tempMax = 0;
        tempMaxString = "";
    }

    //for (QVector<QPair<QString, u_int16_t> >::const_iterator i = itemsOrderedDescending.begin();
    //     i < itemsOrderedDescending.end(); ++i) {
    //    qDebug() <<  i->first << " " << i->second ;
    //}
    return itemsOrderedDescending;
}
