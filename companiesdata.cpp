#include "companiesdata.h"

CompaniesData::CompaniesData()
{

}

CompaniesData::CompaniesData(const QString &in_company, const QString &in_country,const QString &in_type) : company(in_company), country(in_country),
    type(in_type)
{

}

void CompaniesData::setCompany(const QString &in_company)
{
    company = in_company;
}

void CompaniesData::setCountry(const QString &in_country)
{
    country = in_country;
}

void CompaniesData::setType(const QString &in_type)
{
    type = in_type;
}

const QString& CompaniesData::getCompany() const
{
    return company;
}

const QString& CompaniesData::getCountry() const
{
    return country;
}

const QString& CompaniesData::getType() const
{
    return type;
}

QString CompaniesData::toString() const
{
    return company + " | " + country + " | " + type;
}
