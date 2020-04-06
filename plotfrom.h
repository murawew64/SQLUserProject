#ifndef PLOTFROM_H
#define PLOTFROM_H

#include <QWidget>
#include "qcustomplot.h"
#include "datebase.h"

namespace Ui {
class PlotFrom;
}

class PlotFrom : public QWidget
{
    Q_OBJECT

public:
    explicit PlotFrom(QWidget *parent = nullptr);
    ~PlotFrom();
    void setData(const QString& company_name, const ForbesList &forbes_list,
            const ForbesMap& forbes);

private:
    Ui::PlotFrom *ui;
    QCustomPlot *plot;
};

#endif // PLOTFROM_H
