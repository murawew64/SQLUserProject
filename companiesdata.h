#ifndef COMPANIESDATA_H
#define COMPANIESDATA_H
#include <QString>

class CompaniesData
{
public:
    CompaniesData();
    CompaniesData(const QString &in_company, const QString &in_country, const QString &in_type);
    void setCompany(const QString &in_company);
    void setCountry(const QString &in_country);
    void setType(const QString &in_type);
    const QString& getCompany() const;
    const QString& getCountry() const;
    const QString& getType() const;
    QString toString() const;

private:
    QString company;
    QString country;
    QString type;
};

#endif // COMPANIESDATA_H
