#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablerowmodel.h"
#include "ordereditemsdialog.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(NULL),
    proxy_model(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (model != NULL)
        delete model;
    if (proxy_model!= NULL)
        delete proxy_model;
    if (orderedItemsDialog!= NULL)
        delete orderedItemsDialog;
}

TableRowModel *MainWindow::getModel()
{
   return model;
}

void MainWindow::on_actionLoad_data_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString());

    uint numberOfRows = 0;
    // text data in QStringList per order
    QVector<QStringList> qStringVector;

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Couldn't open the file: %1").arg(fileName));
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            ++numberOfRows;
            QString thisLine = in.readLine();
            QStringList splitLine = thisLine.split(",");
            qStringVector.append(splitLine);
        }

        if (model != NULL)
            delete model;
        model = new TableRowModel(qStringVector);
        proxy_model = new QSortFilterProxyModel(this);
        proxy_model->setSourceModel(model);
        //ui->tableView->setModel(model);
        ui->tableView->setModel(proxy_model);
        ui->tableView->verticalHeader()->setVisible(false);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->setSectionResizeMode(
                    TableRowModel_Constants::TABLE_ORDERID_HEADER_ID,
                    QHeaderView::Interactive);
        ui->tableView->resizeColumnToContents(TableRowModel_Constants::TABLE_ORDERID_HEADER_ID);


        emit(inputFileRead(qStringVector));

        file.close();
    }else{
        return;
    }

    updateComboboxCompany();
    updateComboboxAddress();
    updateComboboxOrderIDs();
    ui->pushButtonOrderedItems->setEnabled(true);
    ui->pushButtonRemoveOrder->setEnabled(true);
}

void MainWindow::updateComboboxCompany() const {
    ui->comboBoxCompany->clear();
    ui->comboBoxCompany->addItem(MainWindow_Constants::COMBOBOX_EMPTY_SORTING);
    ui->comboBoxCompany->addItems( model->getUniqueCompanyNames() );
}

void MainWindow::updateComboboxAddress() const {
    ui->comboBoxAddress->clear();
    ui->comboBoxAddress->addItem(MainWindow_Constants::COMBOBOX_EMPTY_SORTING);
    ui->comboBoxAddress->addItems( model->getUniqueAddresses() );
}

void MainWindow::updateComboboxOrderIDs() const {
    ui->comboBoxOrderIDs->clear();
    ui->comboBoxOrderIDs->addItems( model->getUniqueOrderIds() );
    ui->comboBoxOrderIDs->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

void MainWindow::on_comboBoxCompany_currentIndexChanged(const QString &currentString)
{
    QString sortString = "";
    if ( 0 != currentString.compare(MainWindow_Constants::COMBOBOX_EMPTY_SORTING) ){
        sortString = currentString;
        int emptySortingIndex =
                        ui->comboBoxAddress->findText(MainWindow_Constants::COMBOBOX_EMPTY_SORTING);
        ui->comboBoxAddress->setCurrentIndex(emptySortingIndex);
    }
    proxy_model->setFilterRegExp(QRegExp(sortString, Qt::CaseSensitive, QRegExp::FixedString));
    proxy_model->setFilterKeyColumn(TableRowModel_Constants::TABLE_COMPANY_HEADER_ID);
}

void MainWindow::on_comboBoxAddress_currentIndexChanged(const QString &currentString)
{
    QString sortString = "";
    if ( 0 != currentString.compare(MainWindow_Constants::COMBOBOX_EMPTY_SORTING) ){
        sortString = currentString;
        int emptySortingIndex =
                        ui->comboBoxCompany->findText(MainWindow_Constants::COMBOBOX_EMPTY_SORTING);
        ui->comboBoxCompany->setCurrentIndex(emptySortingIndex);
    }
    proxy_model->setFilterRegExp(QRegExp(sortString, Qt::CaseSensitive, QRegExp::FixedString));
    proxy_model->setFilterKeyColumn(TableRowModel_Constants::TABLE_ADDRESS_HEADER_ID);
}

void MainWindow::on_pushButtonRemoveOrder_clicked()
{
    int rowID = ui->comboBoxOrderIDs->currentIndex();
    if ( rowID != -1) {
        model->removeRow(rowID);
        updateComboboxOrderIDs();
        updateComboboxAddress();
        updateComboboxCompany();
    }else {
        ui->pushButtonOrderedItems->setEnabled(false);
    }
}

void MainWindow::on_pushButtonOrderedItems_clicked()
{
    if( model == NULL || model->rowCount() < 1){
        return;
    }
    QVector<QPair<QString, u_int16_t> > list = model->getOrderedItemsDescending();
    orderedItemsDialog = new OrderedItemsDialog();
    orderedItemsDialog->show();
    orderedItemsDialog->setTableData(&list);
}

