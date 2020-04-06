#include "datebase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Datebase::Datebase()
{

}

bool Datebase::openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=DESKTOP-D3C3R5R\\SQLEXPRESS;DATABASE=Forbes;Trusted_Connection=yes;");
    db.setUserName("");
    db.setPassword("");

    bool err = false;
    if(!db.open()) {
        qDebug()<<"ERROR: "<<QSqlError(db.lastError()).text();
        err = true;
    } else {
        qDebug()<<"Ok";
    }
    return err;
}

void Datebase::querySelectCompaniesWithYears(const QString &company_list_str, const QString &year_list_str, CompaniesList &companies, ForbesList &forbes_list,
                                             ForbesMap &forbes)
{
    try{
        qDebug() << year_list_str;
        QSqlQuery query(mDatabase);

        query.prepare("EXEC dbo.SelectCompaniesWithYears ?, ?");
        query.bindValue(0, company_list_str);
        query.bindValue(1, year_list_str);
        query.exec();
        qDebug() << query.executedQuery();

        while(query.next()){
            companies.append(CompaniesData(query.value(0).toString(), query.value(1).toString(), query.value(2).toString()));
            QString company = query.value(0).toString();
            pair p(company, ForbesData(query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(),
                                   query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt()));
            forbes_list.append(p);
            forbes[query.value(0).toString()].append(forbes_list.size() - 1);
        }
    }
    catch(...){
        qDebug() << "Error in querySelectCompaniesWithYears";
    }
}

void Datebase::querySelectCompaniesAndFrobesWithAllParametrs(const QString &company_list_str, const QString &year_list_str, const QString &country_list_str,
                                                             const QString &type_list_str, const ForbesData &min_data, const ForbesData &max_data,
                                                             CompaniesList &companies, ForbesList &forbes_list, ForbesMap &forbes)
{
    QSqlQuery query(mDatabase);

    query.prepare("EXEC dbo.SelectCompaniesAndFrobesWithAllParametrs ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?");
    query.bindValue(0, company_list_str);
    query.bindValue(1, year_list_str);
    query.bindValue(2, country_list_str);
    query.bindValue(3, type_list_str);
    query.bindValue(4, min_data.getSales());
    query.bindValue(5, max_data.getSales());
    query.bindValue(6, min_data.getProfits());
    query.bindValue(7, max_data.getProfits());
    query.bindValue(8, min_data.getAssets());
    query.bindValue(9, max_data.getAssets());
    query.bindValue(10, min_data.getMarketValue());
    query.bindValue(11, max_data.getMarketValue());
    query.bindValue(12, min_data.getRanking());
    query.bindValue(13, max_data.getRanking());
    query.exec();
    qDebug() << query.executedQuery();

    while(query.next()){
        companies.append(CompaniesData(query.value(0).toString(), query.value(1).toString(), query.value(2).toString()));
        QString company = query.value(0).toString();
        pair p(company, ForbesData(query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(),
                                   query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt()));
        forbes_list.append(p);
        forbes[query.value(0).toString()].append(forbes_list.size() - 1);
    }
}

void Datebase::querySelectAllYears(QStringList &yearsList)
{
    QSqlQuery query;
    query.exec("EXEC dbo.SelectAllYears");

    while(query.next()){
        yearsList.append(query.value(0).toString());
    }
}

void Datebase::querySelectAllCompanies(QStringList &yearsList)
{
    QSqlQuery query;
    query.exec("EXEC dbo.SelectAllCompaniesNames");

    while(query.next()){
        yearsList.append(query.value(0).toString());
    }
}

void Datebase::querySelectAllCountries(QStringList &yearsList)
{
    QSqlQuery query;
    query.exec("EXEC dbo.SelectAllCountriesNames");

    while(query.next()){
        yearsList.append(query.value(0).toString());
    }
}

void Datebase::querySelectAllTypes(QStringList &yearsList)
{
    QSqlQuery query;
    query.exec("EXEC dbo.SelectAllTypesNames");

    while(query.next()){
        yearsList.append(query.value(0).toString());
    }
}

int Datebase::querySelectUser(const QString &login, const QString &password)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.SelectUser ?, ?");
        query.bindValue(0, login);
        query.bindValue(1, password);
        query.exec();

        query.next();
        return query.value(0).toInt();
    } catch (...) {
        qDebug() << "Error in querySelectUser";
    }
}

void Datebase::queryInsertUser(const QString &login, const QString &password, int access)
{
    try {
        QSqlQuery query;
        query.prepare("EXEC dbo.InsertUser ?, ?, ?");
        query.bindValue(0, login);
        query.bindValue(1, password);
        query.bindValue(2, access);
        query.exec();
    } catch (...) {
        qDebug() << "Error in queryInsertUser";
    }
}



