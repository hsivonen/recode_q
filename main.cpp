#include <QCoreApplication>
#include <QTimer>

#include "recodeqmain.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    RecodeQMain recode;
    QObject::connect(&recode, SIGNAL(done()), &app, SLOT(quit()), Qt::QueuedConnection);
    QTimer::singleShot(0, &recode, SLOT(run()));
    return app.exec();
}
