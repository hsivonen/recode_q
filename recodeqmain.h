#ifndef RECODEQMAIN_H
#define RECODEQMAIN_H

#include <QObject>

class RecodeQMain : public QObject
{
    Q_OBJECT
public:
    RecodeQMain(const QStringList& inputs,
                const QString& output,
                const QString& fromLabel,
                const QString& toLabel);

signals:
    void done();

public slots:
    void run();

private:
    QStringList inputs;
    const QString output;
    const QString fromLabel;
    const QString toLabel;
};

#endif // RECODEQMAIN_H
