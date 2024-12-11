#ifndef SIPCALCULATOR_H
#define SIPCALCULATOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class SIPCalculator : public QWidget
{
    Q_OBJECT
public:
    explicit SIPCalculator(QWidget *parent = nullptr);
    ~ SIPCalculator();

signals:

public slots:
    void calculateSip();

private:
    QLabel *TotalInvestmentlbl;
    QLabel *ExpectedReturnlbl;
    QLabel *TimePeriodlbl;

    QLineEdit *TotalInvestmentedit;
    QLineEdit *ExpectedReturnedit;
    QLineEdit *TimePeriodedit;
    QPushButton *CalculateBtn;
};

#endif // SIPCALCULATOR_H
