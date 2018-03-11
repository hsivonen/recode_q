// Copyright 2016 Mozilla Foundation. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

#include "recodeqmain.h"

RecodeQMain::RecodeQMain(const QStringList& inputs,
                         const QString& output,
                         const QString& fromLabel,
                         const QString& toLabel)
  : QObject(nullptr)
  , inputs(inputs)
  , output(output)
  , fromLabel(fromLabel)
  , toLabel(toLabel)
{
}

QTextCodec*
RecodeQMain::codecForLabel(const QString& label)
{
    if (label.isEmpty()) {
        return QTextCodec::codecForName("UTF-8");
    }
    return QTextCodec::codecForName(label.toUtf8());
}

void
RecodeQMain::writeToStdErrAndQuit(const QString& message)
{
    QTextStream err(stderr);
    err << message;
    emit done();
}

void
RecodeQMain::convert(QFile& inputFile, QTextCodec* inputCodec, QTextStream& outputStream)
{
    QTextStream inputStream(&inputFile);
    inputStream.setCodec(inputCodec);

    // No signaling of io errors???
    QString text = inputStream.readAll();
    outputStream << text;
}

void
RecodeQMain::run()
{
    QTextCodec* inputCodec = codecForLabel(fromLabel);
    if (!inputCodec) {
        writeToStdErrAndQuit(fromLabel + " is not a known encoding label; exiting.");
        return;
    }

    QTextCodec* outputCodec = codecForLabel(toLabel);
    if (!outputCodec) {
        writeToStdErrAndQuit(toLabel + " is not a known encoding label; exiting.");
        return;
    }

    QFile outputFile;
    if (output.isEmpty() || output == "-") {
        if (!outputFile.open(stdout, QIODevice::WriteOnly)) {
            writeToStdErrAndQuit("Cannot open stdout for writing; exiting.");
            return;
        }
    } else {
        outputFile.setFileName(output);
        if (!outputFile.open(QIODevice::WriteOnly)){
            writeToStdErrAndQuit(QString("Cannot open ") + output + "for writing; exiting.");
            return;
        }
    }
    QTextStream outputStream(&outputFile);
    outputStream.setCodec(outputCodec);

    if (inputs.isEmpty()) {
        QFile inputFile;
        if (!inputFile.open(stdin, QIODevice::ReadOnly)) {
            writeToStdErrAndQuit("Cannot open stdin for writing; exiting.");
            return;
        }
        convert(inputFile, inputCodec, outputStream);
        inputFile.close();
    } else {
        QString fileName;
        foreach (fileName, inputs) {
            if (fileName.isEmpty()) {
                // shouldn't happen with shell
            } else if (fileName == "-") {
                QFile inputFile;
                if (!inputFile.open(stdin, QIODevice::ReadOnly)) {
                    writeToStdErrAndQuit("Cannot open stdin for writing; exiting.");
                    return;
                }
                convert(inputFile, inputCodec, outputStream);
                inputFile.close();
            } else {
                QFile inputFile;
                inputFile.setFileName(fileName);
                if (!inputFile.open(QIODevice::ReadOnly)){
                    writeToStdErrAndQuit(QString("Cannot open ") + fileName + "for reading; exiting.");
                    return;
                }
                convert(inputFile, inputCodec, outputStream);
                inputFile.close();
            }
        }
    }

    // Move these into a RAII thingy
    outputStream.flush();
    outputFile.close();
    emit done();
}
