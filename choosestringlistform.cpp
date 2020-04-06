#include "choosestringlistform.h"
#include "ui_choosestringlistform.h"

ChooseStringListForm::ChooseStringListForm(QWidget *parent, QString labelname1, QString labelname2) :
    QWidget(parent),
    ui(new Ui::ChooseStringListForm)
{
    ui->setupUi(this);
    ui->label1->setText(labelname1);
    ui->label2->setText(labelname2);
}

ChooseStringListForm::~ChooseStringListForm()
{
    delete ui;
}

void ChooseStringListForm::setStringList(const QStringList &list)
{
    allStrs = list;
    ui->allListWidget->addItems(list);
}

const QStringList &ChooseStringListForm::getStringList() const
{
    return resChoosenStrs;
}

//добавляю
void ChooseStringListForm::on_allListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(!choosenStrs.contains(item->text())){
        choosenStrs.append(item->text());
        ui->choosenListWidget->addItem(item->text());
    }
}

//удаляю
void ChooseStringListForm::on_choosenListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    choosenStrs.removeOne(item->text());
    ui->choosenListWidget->clear();
    ui->choosenListWidget->addItems(choosenStrs);
}

void ChooseStringListForm::on_clearButton_clicked()
{
    ui->choosenListWidget->clear();
}

void ChooseStringListForm::on_findButton_clicked()
{
    ui->allListWidget->clear();
    QString findStr = ui->lineEdit->text().trimmed();
    if(!findStr.isEmpty()) {
         for(auto str : allStrs) {
            if(str.toLower().indexOf(findStr.toLower()) == 0)
                ui->allListWidget->addItem(str);
         }
    }
}

void ChooseStringListForm::on_toAllButton_clicked()
{
    ui->allListWidget->clear();
    ui->allListWidget->addItems(allStrs);
}

void ChooseStringListForm::on_closeButton_clicked()
{
    //не применять изменения и закрыть
    choosenStrs = resChoosenStrs;
    ui->choosenListWidget->clear();
    ui->choosenListWidget->addItems(resChoosenStrs);
    close();
}

void ChooseStringListForm::on_okButton_clicked()
{
    resChoosenStrs = choosenStrs;
    close();
}
