#ifndef RECODEQMAIN_H
#define RECODEQMAIN_H

#include <QObject>

class RecodeQMain : public QObject
{
    Q_OBJECT
public:
    RecodeQMain();

signals:
    void done();

public slots:
    void run();
};

#endif // RECODEQMAIN_H
