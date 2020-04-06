#ifndef CHOOSEYEARSFORM_H
#define CHOOSEYEARSFORM_H

#include <QDialog>
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ChooseYearsForm;
}

class ChooseYearsForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseYearsForm(QWidget *parent = nullptr);
    ~ChooseYearsForm();
    void setYears(const QStringList &yearsList);
    const QStringList& getChoosenYears() const;

private slots:
    void on_closeButton_clicked();

    void on_okButton_clicked();

    void on_choosenYearsList_itemDoubleClicked(QListWidgetItem *item);

    void on_allYearsList_itemDoubleClicked(QListWidgetItem *item);

private:
    void addItemsToChoosenList(const QStringList &list);

private:
    Ui::ChooseYearsForm *ui;
    QStringList resChoosenYears; //выбранные и сохраненные года
    QStringList choosenYears; //выбранные года
};

#endif // CHOOSEYEARSFORM_H
