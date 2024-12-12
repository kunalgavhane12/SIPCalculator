#ifndef SIPCALCULATOR_H
#define SIPCALCULATOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QChart>
#include <QPieSeries>

class SIPCalculator : public QWidget
{
    Q_OBJECT
public:
    explicit SIPCalculator(QWidget *parent = nullptr);
    ~ SIPCalculator();

signals:

private slots:
    void calculateSip();
    // void changeLabelName(QPushButton *);
    void changeLabelName();
    void clearAll();

private:
    QLabel *Investmentlbl;
    QLabel *TotalInvestmentlbl;
    QLabel *ExpectedReturnlbl;
    QLabel *TimePeriodlbl;
    QLabel *Statuslbl;

    QLineEdit *InvestmentEdit;
    QLineEdit *ExpectedReturnEdit;
    QLineEdit *TimePeriodEdit;
    QPushButton *CalculateBtn;
    QPushButton *MonthlyBtn;
    QPushButton *LumpsumBtn;

    QPieSeries *series;
    QChart *chart;   
};

#endif // SIPCALCULATOR_H
