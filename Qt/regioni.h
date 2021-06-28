#ifndef REGIONI_H
#define REGIONI_H

#include <QMainWindow>
#include <QtCharts/QPieSeries>
#include <QtCharts>
using namespace QtCharts;

namespace Ui {
class Regioni;
}
struct regione {
    std::string nome;
    std::string eta;
    int maschi;
    int femmine;

    regione(): maschi(0),femmine(0) {}
    regione(const std::string &n,const std::string &e,const int m,const int f)
        : nome(n), eta(e), maschi(m), femmine(f){}
};
class Regioni : public QMainWindow
{
    Q_OBJECT

public:
    explicit Regioni(QWidget *parent = nullptr);
    ~Regioni();

private:
    Ui::Regioni *ui;
    int n_voci=0;
    std::vector<regione> regioni;
    QChart *chart,*chartf;
    QPieSeries *series,*seriesf;

    void leggi();
    void pie();
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
};

#endif
