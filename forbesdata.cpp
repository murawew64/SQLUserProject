#include "forbesdata.h"

ForbesData::ForbesData()
{

}

ForbesData::ForbesData(int in_sales, int in_profits, int in_assets, int in_market_value, short in_year, short in_ranking) :
    sales(in_sales), profits(in_profits), assets(in_assets), market_value(in_market_value), year(in_year), ranking(in_ranking)
{

}

void ForbesData::setSales(int in_sales)
{
    sales = in_sales;
}

void ForbesData::setProfits(int in_profits)
{
    profits = in_profits;
}

void ForbesData::setAssets(int in_assets)
{
    assets = in_assets;
}

void ForbesData::setMarketValue(int in_market_value)
{
    market_value = in_market_value;
}

void ForbesData::setYear(short in_year)
{
    year = in_year;
}

void ForbesData::setRanking(short in_ranking)
{
    ranking = in_ranking;
}

int ForbesData::getSales() const
{
    return sales;
}

int ForbesData::getProfits() const
{
    return profits;
}

int ForbesData::getAssets() const
{
    return assets;
}

int ForbesData::getMarketValue() const
{
    return market_value;
}

short ForbesData::getYear() const
{
    return year;
}

short ForbesData::getRanking() const
{
    return ranking;
}
