#include "sipcalculator.h"

#include <QVBoxLayout>

SIPCalculator::SIPCalculator(QWidget *parent)
    : QWidget{parent}
    , TotalInvestmentlbl(new QLabel("Total investment"))
    , ExpectedReturnlbl(new QLabel("Expected return rate (p.a)"))
    , TimePeriodlbl(new QLabel("Time period"))
    , TotalInvestmentedit(new QLineEdit)
    , ExpectedReturnedit(new QLineEdit)
    , TimePeriodedit(new QLineEdit)
    , CalculateBtn(new QPushButton("Calculate"))
{

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(TotalInvestmentlbl);
    vlayout->addWidget(TotalInvestmentedit);
    vlayout->addWidget(ExpectedReturnlbl);
    vlayout->addWidget(ExpectedReturnedit);
    vlayout->addWidget(TimePeriodlbl);
    vlayout->addWidget(TimePeriodedit);
    vlayout->addWidget(CalculateBtn);
    vlayout->addStretch();

    connect(CalculateBtn,&QPushButton::clicked,this, &SIPCalculator::calculateSip);
}

SIPCalculator::~SIPCalculator()
{
    delete TotalInvestmentlbl;
    delete ExpectedReturnlbl;
    delete TimePeriodlbl;
    delete TotalInvestmentedit;
    delete ExpectedReturnedit;
    delete TimePeriodedit;
}

void SIPCalculator::calculateSip()
{
    double monthlyInvestment = TotalInvestmentedit->text().toDouble();
    double ReturnAmt = ExpectedReturnedit->text().toDouble();
    double TimePeriod = TimePeriodedit->text().toDouble();

    double maturity = 0;

    // Calculate SIP maturity
    double totalAmt = monthlyInvestment * 12;
    double ratePerMonth = (ReturnAmt / 100) / 12; // Monthly return rate
    int months = TimePeriod * 12; // Total number of months

    // Maturity formula: M = P * [(1 + r)^n - 1] / r * (1 + r)

    if (ratePerMonth != 0) // Avoid division by zero
    {
        maturity = monthlyInvestment * (pow(1 + ratePerMonth, months) - 1) / ratePerMonth * (1 + ratePerMonth);
    }
    else
    {
        maturity = monthlyInvestment * months; // If return rate is 0, maturity is simply total investment
    }

    qDebug() << "Total investment: " << totalAmt
             << "\nExpected return rate (p.a): " << ReturnAmt
             << "\nTime period: " << TimePeriod
             << "\nMaturity Amount: " << maturity;
}
