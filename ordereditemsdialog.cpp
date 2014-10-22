#include "ordereditemsdialog.h"
#include "ui_ordereditemsdialog.h"

OrderedItemsDialog::OrderedItemsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderedItemsDialog)
{
    ui->setupUi(this);
}

OrderedItemsDialog::~OrderedItemsDialog()
{
    delete ui;
}

Ui::OrderedItemsDialog *OrderedItemsDialog::getUI()
{
    return this->ui;
}

void OrderedItemsDialog::setTableData(QVector<QPair<QString, u_int16_t> > *data)
{
    ui->tableOrderedItems->setColumnCount(OrderedItemsDialog_Constants::TABLEHEADERS.size());
    ui->tableOrderedItems->setHorizontalHeaderLabels(OrderedItemsDialog_Constants::TABLEHEADERS);
    ui->tableOrderedItems->verticalHeader()->setVisible(false);
    ui->tableOrderedItems->setRowCount(data->size());
    ui->tableOrderedItems->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableOrderedItems->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    u_int16_t i = 0;
    for (QVector<QPair<QString, u_int16_t> >::iterator it = data->begin(); it < data->end(); ++it) {
        ui->tableOrderedItems->setItem(i, 0, new QTableWidgetItem(it->first));
        ui->tableOrderedItems->setItem(i, 1, new QTableWidgetItem(QString::number(it->second)));
        ++i;
    }

}
