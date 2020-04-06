#include "chooseyearsform.h"
#include "ui_chooseyearsform.h"

ChooseYearsForm::ChooseYearsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseYearsForm)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ChooseYearsForm::~ChooseYearsForm()
{
    delete ui;
}

void ChooseYearsForm::setYears(const QStringList &yearsList)
{
    //добавляю все года
    ui->allYearsList->addItems(yearsList);

}

const QStringList &ChooseYearsForm::getChoosenYears() const
{
    return resChoosenYears;
}

void ChooseYearsForm::on_closeButton_clicked()
{
    //не применять изменения и закрыть
    choosenYears = resChoosenYears;
    ui->choosenYearsList->clear();
    ui->choosenYearsList->addItems(resChoosenYears);
    close();
}

void ChooseYearsForm::on_okButton_clicked()
{
    resChoosenYears = choosenYears;
    close();
}

void ChooseYearsForm::on_choosenYearsList_itemDoubleClicked(QListWidgetItem *item)
{
    choosenYears.removeOne(item->text());
    ui->choosenYearsList->clear();
    addItemsToChoosenList(choosenYears);
}

void ChooseYearsForm::on_allYearsList_itemDoubleClicked(QListWidgetItem *item)
{
    if(!choosenYears.contains(item->text())){
        choosenYears.append(item->text());
        ui->choosenYearsList->addItem(item->text());
    }
}

void ChooseYearsForm::addItemsToChoosenList(const QStringList &list)
{
    for(auto year : list){
        ui->choosenYearsList->addItem(year);
    }
}
