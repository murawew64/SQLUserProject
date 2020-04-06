#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //запрещаю редактирование
    ui->tableWidget->setEditTriggers(0);
    //запрос еще не был выполнен, отменять нечего
    ui->returnToQueryButton->setEnabled(false);

    datebase = new Datebase();
    datebase->openDatabase();
    autorization();
    returnToStandart();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete datebase;
    delete plotForm;
}

void MainWindow::autorization()
{
    this->setWindowTitle("Database of economic indicators (Client)");

    this->ui->groupBox->setEnabled(false);
    this->ui->groupBox_3->setEnabled(false);
    this->ui->groupBox_4->setEnabled(false);
    this->ui->groupBox_5->setEnabled(false);

    authForm = new AutorizationForm(this);
    authForm->setDatebase(datebase);
    this->setFocusProxy(authForm);
    connect(authForm, SIGNAL(autorizationOk(User)), this, SLOT(startClientWork(User)));
    authForm->show();
}

void MainWindow::startClientWork(User user)
{
    this->ui->userLabel->setText(user.getLogin());

    //делаю форму активной
    this->ui->groupBox->setEnabled(true);
    this->ui->groupBox_3->setEnabled(true);
    this->ui->groupBox_4->setEnabled(true);
    this->ui->groupBox_5->setEnabled(true);

    //создаю формы выбора
    QStringList list;

    yearsForm = new ChooseYearsForm(this);
    yearsForm->hide();
    datebase->querySelectAllYears(list);
    yearsForm->setYears(list);

    list.clear();
    companiesForm = new ChooseStringListForm(this, "Companies: ", "You have choosen:");
    companiesForm->hide();
    datebase->querySelectAllCompanies(list);
    companiesForm->setStringList(list);

    list.clear();
    countriesForm = new ChooseStringListForm(this, "Countries: ", "You have choosen:");
    countriesForm->hide();
    datebase->querySelectAllCountries(list);
    countriesForm->setStringList(list);

    list.clear();
    typesForm = new ChooseStringListForm(this, "Types: ", "You have choosen:");
    typesForm->hide();
    datebase->querySelectAllTypes(list);
    typesForm->setStringList(list);

    //Создаю график
    plotForm = new PlotFrom();
    plotForm->hide();
}

//слот обработки галочки для all sales
void MainWindow::on_checkAllSales_stateChanged(int arg1)
{
    if(arg1) {
        ui->salesMax->setEnabled(false);
        ui->salesMin->setEnabled(false);
    }
    else {
        ui->salesMax->setEnabled(true);
        ui->salesMin->setEnabled(true);
    }
}

//слот обработки галочки для all profits
void MainWindow::on_checkAllProfits_stateChanged(int arg1)
{
    if(arg1) {
        ui->profitsMax->setEnabled(false);
        ui->profitsMin->setEnabled(false);
    }
    else {
        ui->profitsMax->setEnabled(true);
        ui->profitsMin->setEnabled(true);
    }
}

//слот обработки галочки для all assets
void MainWindow::on_checkAllAssets_stateChanged(int arg1)
{
    if(arg1) {
        ui->assetsMax->setEnabled(false);
        ui->assetsMin->setEnabled(false);
    }
    else {
        ui->assetsMax->setEnabled(true);
        ui->assetsMin->setEnabled(true);
    }
}

//слот обработки галочки для all market value
void MainWindow::on_checkAllMarketValue_stateChanged(int arg1)
{
    if(arg1) {
        ui->marketvalueMax->setEnabled(false);
        ui->marketvalueMin->setEnabled(false);
    }
    else {
        ui->marketvalueMax->setEnabled(true);
        ui->marketvalueMin->setEnabled(true);
    }
}

//слот обработки галочки для all ranking
void MainWindow::on_checkAllRanking_stateChanged(int arg1)
{
    if(arg1) {
        ui->rankingMax->setEnabled(false);
        ui->rankingMin->setEnabled(false);
    }
    else {
        ui->rankingMax->setEnabled(true);
        ui->rankingMin->setEnabled(true);
    }
}

void MainWindow::on_checkAllCompanies_stateChanged(int arg1)
{
    if(arg1) {
        ui->chooseCompaniesButton->setEnabled(false);
    }
    else {
        ui->chooseCompaniesButton->setEnabled(true);
    }
}

void MainWindow::on_checkAllCountries_stateChanged(int arg1)
{
    if(arg1) {
        ui->chooseCountriesButton->setEnabled(false);
    }
    else {
        ui->chooseCountriesButton->setEnabled(true);
    }
}

void MainWindow::on_checkAllYears_stateChanged(int arg1)
{
    if(arg1) {
        ui->chooseYearsButton->setEnabled(false);
    }
    else {
        ui->chooseYearsButton->setEnabled(true);
    }
}

void MainWindow::on_checkAllTypes_stateChanged(int arg1)
{
    if(arg1) {
        ui->chooseTypesButton->setEnabled(false);
    }
    else {
        ui->chooseTypesButton->setEnabled(true);
    }
}

void MainWindow::returnToStandart()
{
    on_returnToStandartButton_clicked();
}

void MainWindow::writeToList(const CompaniesList &comp)
{
    ui->listWidget->clear();
    for(const CompaniesData &cdata : comp) {
        ui->listWidget->addItem(cdata.toString());
    }

}

void MainWindow::writeToTable(const ForbesList &forb)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    for(const pair &p : forb){
        //вставляю строку в цикле, так как не знаю сколько строк изначально
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowCount = ui->tableWidget->rowCount();
        //вставляю значения в соотвествующие ячейки
        ui->tableWidget->setItem(rowCount - 1, 0, new QTableWidgetItem(p.first));
        ui->tableWidget->setItem(rowCount - 1, 1, new QTableWidgetItem( QString::number(p.second.getSales()) ));
        ui->tableWidget->setItem(rowCount - 1, 2, new QTableWidgetItem( QString::number(p.second.getProfits()) ));
        ui->tableWidget->setItem(rowCount - 1, 3, new QTableWidgetItem( QString::number(p.second.getAssets()) ));
        ui->tableWidget->setItem(rowCount - 1, 4, new QTableWidgetItem( QString::number(p.second.getMarketValue()) ));
        ui->tableWidget->setItem(rowCount - 1, 5, new QTableWidgetItem( QString::number(p.second.getYear()) ));
        ui->tableWidget->setItem(rowCount - 1, 6, new QTableWidgetItem( QString::number(p.second.getRanking()) ));

    }
}

//запись companies и forbes в QListWidget и QTableWidget
void MainWindow::writeToListTableWidgets()
{
    if(!companies.isEmpty()){
        ui->listWidget->clear();
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);

        //заполняю QListWidget
        for(const CompaniesData &cdata : companies) {
            ui->listWidget->addItem(cdata.toString());
        }

        //заполняю QTableWidget
        ui->tableWidget->setColumnCount(7);
        QStringList header_names;
        header_names << "Company" << "Sales" << "Profits" << "Assets" << "Market value" << "Year" << "Ranking";
        ui->tableWidget->setHorizontalHeaderLabels(header_names);

        //задаю количество строк
        ui->tableWidget->setRowCount(forbes_list.size());
        int index = 0;
        for(const pair &p : forbes_list){
            //вставляю значения в соотвествующие ячейки
            ui->tableWidget->setItem(index, 0, new QTableWidgetItem(p.first));
            ui->tableWidget->setItem(index, 1, new QTableWidgetItem( QString::number(p.second.getSales()) ));
            ui->tableWidget->setItem(index, 2, new QTableWidgetItem( QString::number(p.second.getProfits()) ));
            ui->tableWidget->setItem(index, 3, new QTableWidgetItem( QString::number(p.second.getAssets()) ));
            ui->tableWidget->setItem(index, 4, new QTableWidgetItem( QString::number(p.second.getMarketValue()) ));
            ui->tableWidget->setItem(index, 5, new QTableWidgetItem( QString::number(p.second.getYear()) ));
            ui->tableWidget->setItem(index, 6, new QTableWidgetItem( QString::number(p.second.getRanking()) ));
            ++index;
        }
    }
    else {
        QMessageBox::about(this, "Search result", "Empty");
    }
}

//---------------!!!!!!!!!!!!!!!!!!!!------------
//слот поиска по указанных характеристикам
void MainWindow::on_findButton_clicked()
{
    qDebug() << "Find";

    //очищаю от данных прошлого запроса
    companies.clear();
    forbes.clear();
    forbes_list.clear();

    QString company_list_str = "";
    QString year_list_str = "";

    //собрать все компании
    if(!ui->checkAllCompanies->isChecked()) {
        QStringList list = companiesForm->getStringList();
        for(auto str : list){
            company_list_str += str + ",";
        }
        if(company_list_str.isEmpty()){//-----------------------------сделать лучше
            QMessageBox::about(this, "Choose items", "Choose any comapanies");
            return;
        }
    }
    //собрать все года
    if(!ui->checkAllYears->isChecked()) {
        QStringList list = yearsForm->getChoosenYears();
        for(auto year : list){
            year_list_str += year + ",";
        }
        qDebug() << year_list_str;
        if(year_list_str.isEmpty()){//-----------------------------сделать лучше
            QMessageBox::about(this, "Choose items", "Choose any years");
            return;
        }
    }

    //определенный поиск
    if(mode) {
        //вызвать процедуру dbo.SelectCompaniesWithYears
        datebase->querySelectCompaniesWithYears(company_list_str, year_list_str, companies, forbes_list, forbes);
    }
    //общий поиск
    else {
        int min_sales, max_sales, min_profits, max_profits, min_assets,
                max_assets, min_market_value, max_market_value, min_ranking, max_ranking;

        if(ui->checkAllSales->isChecked()) {
            min_sales = -10000000;
            max_sales = 10000000;
        }
        else {
            min_sales = ui->salesMin->value();
            max_sales = ui->salesMax->value();
        }

        if(ui->checkAllProfits->isChecked()) {
            min_profits = -10000000;
            max_profits = 10000000;
        }
        else {
            min_profits = ui->profitsMin->value();
            max_profits = ui->profitsMax->value();
        }

        if(ui->checkAllAssets->isChecked()) {
            min_assets = -10000000;
            max_assets = 10000000;
        }
        else {
            min_assets = ui->assetsMin->value();
            max_assets = ui->assetsMax->value();
        }

        if(ui->checkAllMarketValue->isChecked()) {
            min_market_value = -10000000;
            max_market_value = 10000000;
        }
        else {
            min_market_value = ui->marketvalueMin->value();
            max_market_value = ui->marketvalueMax->value();
        }

        if(ui->checkAllRanking->isChecked()) {
            min_ranking = 1;
            max_ranking = 2000;
        }
        else {
            min_ranking = ui->rankingMin->value();
            max_ranking = ui->rankingMax->value();
        }

        QString country_list_str = "";
        QString type_list_str = "";

        //собрать все страны
        if(!ui->checkAllCountries->isChecked()) {
            QStringList list = countriesForm->getStringList();
            for(auto str : list){
                country_list_str += str + ",";
            }
            qDebug() << country_list_str;
            if(country_list_str.isEmpty()){//-----------------------------сделать лучше
                QMessageBox::about(this, "Choose items", "Choose any countries");
                return;
            }
        }

        //собрать все типы
        if(!ui->checkAllTypes->isChecked()) {
            QStringList list = typesForm->getStringList();
            for(auto str : list){
                type_list_str += str + ",";
            }
            qDebug() << type_list_str;
            if(type_list_str.isEmpty()){//-----------------------------сделать лучше
                QMessageBox::about(this, "Choose items", "Choose any types");
                return;
            }
        }
        //нижний порог по каждому из данных
        ForbesData min_data(min_sales, min_profits, min_assets, min_market_value, 0, min_ranking);

        //верхний порог по каждому из данных
        ForbesData max_data(max_sales, max_profits, max_assets, max_market_value, 0, max_ranking);

        //вызвать процедуру dbo.SelectCompaniesAndFrobesWithAllParametrs
        datebase->querySelectCompaniesAndFrobesWithAllParametrs(company_list_str, year_list_str, country_list_str, type_list_str,
                                                                min_data, max_data, companies, forbes_list, forbes);
    }

    //Обрабатываю данные, полученные в результате запроса
    writeToListTableWidgets();
}

void MainWindow::on_returnToStandartButton_clicked()
{
    /*
    if(!ui->checkAllCompanies->isChecked())
        ui->checkAllCompanies->click();

    if(!ui->checkAllCountries->isChecked())
        ui->checkAllCountries->click();

    if(!ui->checkAllTypes->isChecked())
        ui->checkAllTypes->click();

    if(!ui->checkAllYears->isChecked())
        ui->checkAllYears->click();
    */
}

void MainWindow::on_modeButton_clicked()
{
    if(mode){
        ui->modeLabel->setText("mode 2");
        ui->groupBox->setEnabled(true);
    }
    else {
        ui->modeLabel->setText("mode 1");
        ui->groupBox->setEnabled(false);
    }
    mode = !mode;
}
//выбор компании
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //чтобы можно было вернуться к результату запроса
    ui->returnToQueryButton->setEnabled(true);

    QString item_str = item->text();
    //беру только компанию(формат: компания | страна | тип)
    QString company_name = item_str.split("|")[0].trimmed();
    ui->tableWidget->setRowCount(0);

    ui->drawLabel->setText(company_name);

    for(int elem : forbes[company_name]){
        //вставляю строку в цикле, так как не знаю сколько строк изначально
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowCount = ui->tableWidget->rowCount();
        //pair - first: компания, second:экономические показатели
        const pair &p = forbes_list[elem];

        //вставляю значения в соотвествующие ячейки
        ui->tableWidget->setItem(rowCount - 1, 0, new QTableWidgetItem(p.first));
        ui->tableWidget->setItem(rowCount - 1, 1, new QTableWidgetItem( QString::number(p.second.getSales()) ));
        ui->tableWidget->setItem(rowCount - 1, 2, new QTableWidgetItem( QString::number(p.second.getProfits()) ));
        ui->tableWidget->setItem(rowCount - 1, 3, new QTableWidgetItem( QString::number(p.second.getAssets()) ));
        ui->tableWidget->setItem(rowCount - 1, 4, new QTableWidgetItem( QString::number(p.second.getMarketValue()) ));
        ui->tableWidget->setItem(rowCount - 1, 5, new QTableWidgetItem( QString::number(p.second.getYear()) ));
        ui->tableWidget->setItem(rowCount - 1, 6, new QTableWidgetItem( QString::number(p.second.getRanking()) ));
    }
}

void MainWindow::on_returnToQueryButton_clicked()
{
    ui->returnToQueryButton->setEnabled(false);
    ui->drawLabel->clear();
    writeToListTableWidgets();
}

void MainWindow::on_subfindButton_clicked()
{
    QString text =ui->subfindLine->text().trimmed();
    if(!text.isEmpty()) {
        ui->returnToQueryButton->setEnabled(true);

        QList<CompaniesData> comp_data;

        //смотрю что выбрано: поиск по компаниям, странам или типам

        if(ui->companiesRadio->isChecked()){
            for(auto data : companies) {
                if(data.getCompany().toLower().indexOf(text.toLower()) == 0)
                    comp_data.append(data);
            }
        }

        if(ui->countriesRadio->isChecked()){
            for(auto data : companies) {
                if(data.getCountry().toLower().indexOf(text.toLower()) == 0)
                    comp_data.append(data);
            }
        }

        if(ui->typesRadio->isChecked()){
            for(auto data : companies) {
                if(data.getType().toLower().indexOf(text.toLower()) == 0)
                    comp_data.append(data);
            }
        }

        writeToList(comp_data);
    }
}

void MainWindow::on_chooseYearsButton_clicked()
{
    //yearsForm->move(ui->chooseYearsButton->x() + 50, ui->chooseYearsButton->y() + 200);
    yearsForm->move(mapTo(this, ui->chooseYearsButton->pos()));
    yearsForm->show();
}

void MainWindow::on_chooseCompaniesButton_clicked()
{
    companiesForm->move(mapTo(this, ui->chooseCompaniesButton->pos()));
    companiesForm->show();
}

void MainWindow::on_chooseCountriesButton_clicked()
{
    countriesForm->move(mapTo(this, ui->chooseCountriesButton->pos()));
    countriesForm->show();
}

void MainWindow::on_chooseTypesButton_clicked()
{
    typesForm->move(mapTo(this, ui->chooseTypesButton->pos()));
    typesForm->show();
}

void MainWindow::on_drawButton_clicked()
{
    QString company_name = ui->drawLabel->text();
    plotForm->setData(company_name, forbes_list, forbes);
    plotForm->show();
}

void MainWindow::on_updateButton_clicked()
{
    QStringList list;

    datebase->querySelectAllYears(list);
    yearsForm->setYears(list);

    list.clear();
    datebase->querySelectAllCompanies(list);
    companiesForm->setStringList(list);

    list.clear();
    datebase->querySelectAllCountries(list);
    countriesForm->setStringList(list);

    list.clear();
    datebase->querySelectAllTypes(list);
    typesForm->setStringList(list);
}
