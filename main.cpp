#include <QApplication>
#include <QVBoxLayout>
#include "sipcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.resize(400,500);

    window.setWindowTitle("SIP Calculator");

    SIPCalculator *s = new SIPCalculator;

    QVBoxLayout *vlayout = new QVBoxLayout(&window);
    vlayout->addWidget(s);

    window.setLayout(vlayout);
    window.show();

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return a.exec();
}
