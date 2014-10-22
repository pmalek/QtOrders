#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QSortFilterProxyModel>
#include "tablerowmodel.h"

class OrderedItemsDialog;

namespace MainWindow_Constants{
    static const QString COMBOBOX_EMPTY_SORTING	= "---";
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TableRowModel *getModel();
    void updateComboboxCompany() const;
    void updateComboboxAddress() const;
    void updateComboboxOrderIDs() const;

signals:
    void inputFileRead(const QVector<QStringList> &qStringVector);

private slots:
    void on_actionLoad_data_triggered();

    void on_comboBoxCompany_currentIndexChanged(const QString &);

    void on_comboBoxAddress_currentIndexChanged(const QString &);

    void on_pushButtonRemoveOrder_clicked();

    void on_pushButtonOrderedItems_clicked();

private:
    Ui::MainWindow *ui;
    TableRowModel *model;
    QSortFilterProxyModel *proxy_model;
    OrderedItemsDialog *orderedItemsDialog;
};

#endif // MAINWINDOW_H
