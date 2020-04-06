#ifndef CHOOSESTRINGLISTFORM_H
#define CHOOSESTRINGLISTFORM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ChooseStringListForm;
}

class ChooseStringListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseStringListForm(QWidget *parent = nullptr, QString labelname1 = "", QString labelname2 = "");
    ~ChooseStringListForm();
    void setStringList(const QStringList &yearsList);
    const QStringList& getStringList() const;

private slots:
    void on_allListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_choosenListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_clearButton_clicked();

    void on_findButton_clicked();

    void on_toAllButton_clicked();

    void on_closeButton_clicked();

    void on_okButton_clicked();

private:
    Ui::ChooseStringListForm *ui;
    QStringList allStrs; //все строки
    QStringList resChoosenStrs; //выбранные и сохраненные строки
    QStringList choosenStrs; //выбранные строки
};

#endif // CHOOSESTRINGLISTFORM_H
