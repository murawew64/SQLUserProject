#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "autorizationform.h"
#include "datebase.h"
#include "companiesdata.h"
#include "forbesdata.h"
#include <QMap>
#include <QListWidgetItem>
#include <chooseyearsform.h>
#include <choosestringlistform.h>
#include "plotfrom.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startClientWork(User);

private slots:
    void on_checkAllSales_stateChanged(int arg1);

    void on_checkAllProfits_stateChanged(int arg1);

    void on_checkAllAssets_stateChanged(int arg1);

    void on_checkAllMarketValue_stateChanged(int arg1);

    void on_checkAllRanking_stateChanged(int arg1);

    void on_findButton_clicked();

    void on_checkAllCompanies_stateChanged(int arg1);

    void on_checkAllCountries_stateChanged(int arg1);

    void on_checkAllYears_stateChanged(int arg1);

    void on_checkAllTypes_stateChanged(int arg1);

    void on_returnToStandartButton_clicked();

    void returnToStandart();

    void on_modeButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_returnToQueryButton_clicked();

    void on_subfindButton_clicked();

    void on_chooseYearsButton_clicked();

    void on_chooseCompaniesButton_clicked();

    void on_chooseCountriesButton_clicked();

    void on_chooseTypesButton_clicked();

    void on_drawButton_clicked();

    void on_updateButton_clicked();

private:
    void autorization();
    void writeToListTableWidgets();
    void writeToList(const CompaniesList &comp);
    void writeToTable(const ForbesList &forb);

private:
    Ui::MainWindow *ui;
    AutorizationForm *authForm;
    Datebase *datebase;
    bool mode = false;
    CompaniesList companies;
    ForbesList forbes_list;
    ForbesMap forbes;
    ChooseYearsForm *yearsForm;
    ChooseStringListForm *companiesForm;
    ChooseStringListForm *countriesForm;
    ChooseStringListForm *typesForm;
    PlotFrom *plotForm;
};
#endif // MAINWINDOW_H
