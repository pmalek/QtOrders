#ifndef ORDEREDITEMSDIALOG_H
#define ORDEREDITEMSDIALOG_H

#include <QDialog>
#include <QStringList>

namespace OrderedItemsDialog_Constants{
    static const QStringList TABLEHEADERS = QStringList() << "Item name" << "Ordered x times";
}

namespace Ui {
class OrderedItemsDialog;
}

class OrderedItemsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderedItemsDialog(QWidget *parent = 0);
    ~OrderedItemsDialog();
    Ui::OrderedItemsDialog* getUI();
    void setTableData(QVector<QPair<QString, u_int16_t> >* data);

private:
    Ui::OrderedItemsDialog *ui;
};

#endif // ORDEREDITEMSDIALOG_H
