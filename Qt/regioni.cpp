#include "regioni.h"
#include "ui_regioni.h"
#include <fstream>
#include <set>
#include <QString>
#include <QtCharts/QPieSeries>
#include <QtCharts>
using namespace QtCharts;
Regioni::Regioni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Regioni)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->gridLayout_2);
    ui->tableWidget_2->setColumnCount(3);
    ui->tableWidget_2->setRowCount(22);
    QTableWidgetItem *hHeader1 = new QTableWidgetItem("Età");
    ui->tableWidget_2->setHorizontalHeaderItem(0,hHeader1);
    QTableWidgetItem *hHeader2 = new QTableWidgetItem("Maschi");
    ui->tableWidget_2->setHorizontalHeaderItem(1,hHeader2);
    QTableWidgetItem *hHeader3 = new QTableWidgetItem("Femmine");
    ui->tableWidget_2->setHorizontalHeaderItem(2,hHeader3);
    leggi();
    pie();
    std::set<QString> nomir;//uso un set per salvarmi i nomi delle regioni e uso proprio un set perchè i nomi sono duplicati così vengono salvati una volta
    for(unsigned int i=0;i<this->regioni.size();i++)
    {
        regione r=regioni[i];
        nomir.insert(QString::fromStdString(r.nome));
    }

    for (std::set<QString>::iterator it=nomir.begin(); it!=nomir.end(); ++it)
    {
        QString s=*it;
        ui->comboBox->addItem(s);
    }
}

Regioni::~Regioni()
{
    delete chart;
    delete chartf;

    delete series;
    delete seriesf;

    delete ui;
}
void Regioni::leggi()
{
    std::ifstream is;

    is.open("./data.txt");

    if(is.is_open())
    {
        std::string s,e;
        regione r;
       for(int j=0;j<4;j++)
       {
           int tf=0,tm=0;
            for(int i=0;i<21;i++)
            {
                is>>r.nome>>r.eta>>r.femmine>>r.maschi;
                this->regioni.push_back(r);
                tf=r.femmine+tf;
                tm=r.maschi+tm;
                n_voci++;
            }
            regioni.push_back(regione(r.nome,"totale",tm,tf));
            n_voci++;
        }
    }

    is.close();

}
void Regioni::pie()
{
    series = new QPieSeries();
    for(unsigned int i=0;i<21;i++)
    {
        *series << new QPieSlice(QString::fromStdString(regioni[i].eta), regioni[i].maschi);
    }

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Maschi");
    chart->legend()->setAlignment(Qt::AlignLeft);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_3->addWidget(chartView);

    seriesf = new QPieSeries();
    for(unsigned int i=0;i<21;i++)
    {
        *seriesf << new QPieSlice(QString::fromStdString(regioni[i].eta), regioni[i].femmine);
    }

    chartf = new QChart();
    chartf->addSeries(seriesf);
    chartf->setTitle("Femmine");
    chartf->legend()->setAlignment(Qt::AlignLeft);
    QChartView *chartViewf = new QChartView(chartf);
    chartViewf->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_4->addWidget(chartViewf);
}
void Regioni::on_comboBox_currentIndexChanged(const QString&)
{
    QString labelText = "<P><b><i><FONT COLOR='#1c137a' FONT SIZE = 4>";
    labelText .append(ui->comboBox->currentText());
    labelText .append("</i></b></P></br>");
    ui->label_2->setText(labelText);
    std::vector<regione> r;

     for(unsigned int i=0;i<n_voci;i++)
     {
         if(QString::fromStdString(regioni[i].nome)==(ui->comboBox->currentText()))
         {
             r.push_back(regioni[i]);
         }
     }

    for(unsigned int i=0;i<r.size();i++)
    {
        QTableWidgetItem *i1=new QTableWidgetItem(QString::fromStdString(r[i].eta));
        ui->tableWidget_2->setItem(i,0,i1);
        QTableWidgetItem *i2=new QTableWidgetItem(QString::number(r[i].maschi));
        ui->tableWidget_2->setItem(i,1,i2);
        QTableWidgetItem *i3=new QTableWidgetItem(QString::number(r[i].femmine));
        ui->tableWidget_2->setItem(i,2,i3);
    }

    series->clear();
    seriesf->clear();
    for(unsigned int i=0;i<r.size()-1;i++)
    {
        *series << new QPieSlice(QString::fromStdString(r[i].eta), r[i].maschi);
    }
    for(unsigned int i=0;i<r.size()-1;i++)
    {
        *seriesf << new QPieSlice(QString::fromStdString(r[i].eta), r[i].femmine);
    }


}
