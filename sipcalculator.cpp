#include "sipcalculator.h"
#include <QChartView>
#include <QGroupBox>
#include <QIntValidator>
#include <QPieSeries>
#include <QVBoxLayout>

SIPCalculator::SIPCalculator(QWidget *parent)
    : QWidget{parent}
    , Investmentlbl(new QLabel("Monthly investment"))
    , ExpectedReturnlbl(new QLabel("Expected return rate (p.a)"))
    , TimePeriodlbl(new QLabel("Time period (Yr)"))
    , Statuslbl(new QLabel(""))
    , InvestmentEdit(new QLineEdit)
    , ExpectedReturnEdit(new QLineEdit)
    , TimePeriodEdit(new QLineEdit)
    , CalculateBtn(new QPushButton("Calculate"))
    , MonthlyBtn(new QPushButton("SIP"))
    , LumpsumBtn(new QPushButton("Lumpsum"))
    , series(new QPieSeries())
{
    QHBoxLayout *hlayout = new QHBoxLayout();
    QPushButton *clearBtn = new QPushButton("Clear");

    // Ensure buttons are checkable
    MonthlyBtn->setCheckable(true);
    LumpsumBtn->setCheckable(true);

    hlayout->addWidget(MonthlyBtn);
    hlayout->addWidget(LumpsumBtn);
    hlayout->addWidget(clearBtn);
    hlayout->addStretch();

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(Investmentlbl);
    vlayout->addWidget(InvestmentEdit);
    vlayout->addWidget(ExpectedReturnlbl);
    vlayout->addWidget(ExpectedReturnEdit);
    vlayout->addWidget(TimePeriodlbl);
    vlayout->addWidget(TimePeriodEdit);
    vlayout->addWidget(CalculateBtn);
    vlayout->addWidget(Statuslbl);

    QGroupBox *box = new QGroupBox(this);
    QVBoxLayout *vlayout1 = new QVBoxLayout(box);
    vlayout->addWidget(box);

    chart = new QChart();
    // chart->setTitle("SIP");
    chart->addSeries(series);
    chart->setVisible(true);
    chart->legend()->hide();

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setVisible(true);

    vlayout1->addWidget(view);

    //Connect Signal and slots
    connect(CalculateBtn, &QPushButton::clicked, this, &SIPCalculator::calculateSip);
    // connect(MonthlyBtn, &QPushButton::clicked, this, [this]() { changeLabelName(MonthlyBtn); });
    // connect(LumpsumBtn, &QPushButton::clicked, this, [this]() { changeLabelName(LumpsumBtn); });

    connect(MonthlyBtn, &QPushButton::clicked, this, &SIPCalculator::changeLabelName);
    connect(LumpsumBtn, &QPushButton::clicked, this, &SIPCalculator::changeLabelName);
    connect(clearBtn, &QPushButton::clicked, this, &SIPCalculator::clearAll);

    //Set Validation for lineedits
    InvestmentEdit->setValidator(new QIntValidator(0, 999999999, InvestmentEdit));
    ExpectedReturnEdit->setValidator(new QDoubleValidator(0, 100, 2, ExpectedReturnEdit));
    TimePeriodEdit->setValidator(new QIntValidator(0, 100, TimePeriodEdit));
}

SIPCalculator::~SIPCalculator()
{
    delete Investmentlbl;
    delete ExpectedReturnlbl;
    delete TimePeriodlbl;
    delete InvestmentEdit;
    delete ExpectedReturnEdit;
    delete TimePeriodEdit;
}

void SIPCalculator::calculateSip()
{
    double InvestmentAmount = InvestmentEdit->text().toDouble();
    double ReturnRate = ExpectedReturnEdit->text().toDouble();
    double TimePeriodYr = TimePeriodEdit->text().toDouble();

    // Validate input
    if (InvestmentAmount <= 0 || ReturnRate < 0 || TimePeriodYr <= 0) {
        Statuslbl->setText("Error: All inputs must be positive numbers.");
        return;
    }

    double ratePerMonth = (ReturnRate / 100) / 12; // Monthly return rate
    int months = static_cast<int>(TimePeriodYr * 12); // Total number of months
    double compoundFactor = pow(1 + ratePerMonth, months);

    double totalAmt = 0.0; // Total investment
    double maturity = 0.0; // Maturity amount
    double EstReturnAmt = 0.0; // Estimated returns

    QString investmentMode = Investmentlbl->text();
    if (investmentMode == "Monthly investment") {
        totalAmt = InvestmentAmount * months;

        if (ratePerMonth != 0) {
            maturity = InvestmentAmount * (compoundFactor - 1) / ratePerMonth * (1 + ratePerMonth);
        } else {
            maturity = totalAmt; // No return rate
        }
    } else if (investmentMode == "Total investment") {
        totalAmt = InvestmentAmount;

        if (ReturnRate != 0) {
            // For lump sum, use the compound interest formula
            maturity = totalAmt * pow(1 + (ReturnRate / 100), TimePeriodYr); // Compound interest for lump sum
        } else {
            maturity = totalAmt; // No return rate
        }
    }

    else {
        Statuslbl->setText("Error: Invalid investment mode.");
        return;
    }

    EstReturnAmt = maturity - totalAmt;

    // Update the status label
    Statuslbl->setText("Investment Amount: " + QString::number(totalAmt, 'f', 2) +
                       "\nEst. returns: " + QString::number(EstReturnAmt, 'f', 2) +
                       "\nTotal value: " + QString::number(maturity, 'f', 2));

    qDebug() << "Investment Amount: " + QString::number(totalAmt, 'f', 2) +
                       "\nEst. returns: " + QString::number(EstReturnAmt, 'f', 2) +
                       "\nTotal value: " + QString::number(maturity, 'f', 2);

    // Update the chart
    series->clear();
    series->append("Investment Amount", totalAmt);
    series->append("Est. returns", EstReturnAmt);
    series->append("Total value", maturity);


    QPieSlice *slice_1 = nullptr;
    QPieSlice *slice_2 = nullptr;

    if (series->slices().size() >= 2) {
        slice_1 = series->slices().at(0);
        slice_2 = series->slices().at(1);

        slice_1->setExploded(true);
        slice_1->setLabelVisible(true);
        slice_1->setPen(QPen(Qt::red, 1));
        slice_1->setColor(Qt::red);

        slice_2->setExploded(true);
        slice_2->setLabelVisible(true);
        slice_2->setPen(QPen(Qt::green, 1));
        slice_2->setColor(Qt::green);
    }

    if (series->slices().size() >= 3) {
        QPieSlice *slice_3 = series->slices().at(2);
        slice_3->setExploded(true);
        slice_3->setLabelVisible(true);
        slice_3->setPen(QPen(Qt::blue, 1));
        slice_3->setColor(Qt::blue);
    }

    chart->update();
}

// void SIPCalculator::changeLabelName(QPushButton *clickedButton)
// {
//     if (clickedButton == MonthlyBtn) {
//         MonthlyBtn->setCheckable(true);
//         LumpsumBtn->setCheckable(false);
//         Investmentlbl->setText("Monthly investment");
//     } else if (clickedButton == LumpsumBtn) {
//         LumpsumBtn->setCheckable(true);
//         MonthlyBtn->setCheckable(false);
//         Investmentlbl->setText("Total investment");
//     }
// }

void SIPCalculator::changeLabelName()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (clickedButton == MonthlyBtn) {
        MonthlyBtn->setCheckable(true);
        LumpsumBtn->setCheckable(false);
        Investmentlbl->setText("Monthly investment");
    } else if (clickedButton == LumpsumBtn) {
        LumpsumBtn->setCheckable(true);
        MonthlyBtn->setCheckable(false);
        Investmentlbl->setText("Total investment");
    }
}

void SIPCalculator::clearAll()
{
    InvestmentEdit->clear();
    ExpectedReturnEdit->clear();
    TimePeriodEdit->clear();
    Statuslbl->clear();
    series->clear();
}

