// Copyright 2016 Mozilla Foundation. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

#ifndef RECODEQMAIN_H
#define RECODEQMAIN_H

#include <QObject>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>

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
    QTextCodec* codecForLabel(const QString& label);
    void writeToStdErrAndQuit(const QString& message);
    void convert(QFile& inputFile, QTextCodec* inputCodec, QTextStream& outputStream);

    QStringList inputs;
    const QString output;
    const QString fromLabel;
    const QString toLabel;
};

#endif // RECODEQMAIN_H
