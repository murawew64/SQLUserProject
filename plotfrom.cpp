#include "plotfrom.h"
#include "ui_plotfrom.h"
#include <QBoxLayout>
#include <QVector>
#include <algorithm>

PlotFrom::PlotFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotFrom)
{
    ui->setupUi(this);
    this->setWindowTitle("Graph");

    QVBoxLayout *main_lay = new QVBoxLayout(this);
    plot = new QCustomPlot(this);
    plot->xAxis->setLabel("X");
    plot->yAxis->setLabel("Y");

    main_lay->addWidget(plot);
    this->setLayout(main_lay);
    this->resize(800, 800);
}

void PlotFrom::setData(const QString& company_name, const ForbesList &forbes_list,
             const ForbesMap& forbes)
{
    QVector<double> g1_y;
    QVector<double> g2_y;
    QVector<double> g3_y;
    QVector<double> g4_y;
    QVector<double> g5_y;

    QVector<double> g_x;

    for(int elem : forbes[company_name]){
        const pair &p = forbes_list[elem];
        g_x.append(p.second.getYear());
        g1_y.append(p.second.getSales());
        g2_y.append(p.second.getProfits());
        g3_y.append(p.second.getAssets());
        g4_y.append(p.second.getMarketValue());
        g5_y.append(p.second.getRanking());
    }

    QVector<double> min;
    QVector<double> max;

    auto min_max_1 = std::minmax_element(g1_y.begin(), g1_y.end());
    auto min_max_2 = std::minmax_element(g2_y.begin(), g2_y.end());
    auto min_max_3 = std::minmax_element(g3_y.begin(), g3_y.end());
    auto min_max_4 = std::minmax_element(g4_y.begin(), g4_y.end());
    auto min_max_5 = std::minmax_element(g5_y.begin(), g5_y.end());

    min.append(*min_max_1.first);
    min.append(*min_max_2.first);
    min.append(*min_max_3.first);
    min.append(*min_max_4.first);
    min.append(*min_max_5.first);

    max.append(*min_max_1.second);
    max.append(*min_max_2.second);
    max.append(*min_max_3.second);
    max.append(*min_max_4.second);
    max.append(*min_max_5.second);

    auto main_min_max_1 = std::minmax_element(min.begin(), min.end());
    auto main_min_max_2 = std::minmax_element(max.begin(), max.end());

    plot->addGraph();
    plot->graph(0)->setData(g_x, g1_y);
    plot->graph(0)->setName("Sales");
    plot->graph(0)->setPen(QColor(Qt::red));
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    plot->addGraph();
    plot->graph(1)->setData(g_x, g2_y);
    plot->graph(1)->setName("Profits");
    plot->graph(1)->setPen(QColor(Qt::green));
    plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    plot->addGraph();
    plot->graph(2)->setData(g_x, g3_y);
    plot->graph(2)->setName("Assets");
    plot->graph(2)->setPen(QColor(Qt::yellow));
    plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    plot->addGraph();
    plot->graph(3)->setData(g_x, g4_y);
    plot->graph(3)->setName("Market Value");
    plot->graph(3)->setPen(QColor(Qt::blue));
    plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    plot->addGraph();
    plot->graph(4)->setData(g_x, g5_y);
    plot->graph(4)->setName("Ranking");
    plot->graph(4)->setPen(QColor(Qt::black));
    plot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    double delta = (*main_min_max_1.first + *main_min_max_2.second) / 100;

    plot->xAxis->setRange(2000, 2020);
    plot->yAxis->setRange(*main_min_max_1.first - delta, *main_min_max_2.second + delta);

    plot->replot();
}


PlotFrom::~PlotFrom()
{
    delete ui;
}
