#ifndef FORBESDATA_H
#define FORBESDATA_H


class ForbesData
{
public:
    ForbesData();
    ForbesData(int in_sales, int in_profits, int in_assets, int in_market_value, short in_year, short in_ranking);
    void setSales(int in_sales);
    void setProfits(int in_profits);
    void setAssets(int in_assets);
    void setMarketValue(int in_market_value);
    void setYear(short in_year);
    void setRanking(short in_ranking);
    int getSales() const;
    int getProfits() const;
    int getAssets() const;
    int getMarketValue() const;
    short getYear() const;
    short getRanking() const;

private:
    int sales;
    int profits;
    int assets;
    int market_value;
    short year;
    short ranking;
};

#endif // FORBESDATA_H
