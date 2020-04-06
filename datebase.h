#ifndef DATEBASE_H
#define DATEBASE_H

#include <QSqlDatabase>
#include "companiesdata.h"
#include "forbesdata.h"

using CompaniesList = QList<CompaniesData>;
using pair = std::pair<QString, ForbesData>;
using ForbesList = QList<pair>;
using ForbesMap = QMap<QString, QList<int>>;

class Datebase
{
public:
    Datebase();
    bool openDatabase();
    void querySelectCompaniesWithYears(const QString &company_list_str, const QString &year_list_str, CompaniesList &companies, ForbesList &forbes_list,
                                       ForbesMap &forbes);
    void querySelectCompaniesAndFrobesWithAllParametrs(const QString &company_list_str, const QString &year_list_str, const QString &country_list_str,
                                                       const QString &type_list_str, const ForbesData &min_data, const ForbesData &max_data,
                                                       CompaniesList &companies, ForbesList &forbes_list, ForbesMap &forbes);
    void querySelectAllYears(QStringList &yearsList);
    void querySelectAllCompanies(QStringList &yearsList);
    void querySelectAllCountries(QStringList &yearsList);
    void querySelectAllTypes(QStringList &yearsList);
    int querySelectUser(const QString &login, const QString &password);
    void queryInsertUser(const QString &login, const QString &password, int access);

private:
    QSqlDatabase mDatabase;
};

#endif // DATEBASE_H
