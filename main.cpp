// Copyright 2016 Mozilla Foundation. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.

#include <QCoreApplication>
#include <QTimer>
#include <QCommandLineParser>

#include "recodeqmain.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("recode_q");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Convert between character encodings");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
                          {{"o", "output"},
                           QCoreApplication::translate("main", "set output file name PATH (- for stdout; the default)."),
                           QCoreApplication::translate("main", "PATH"),
                          },
                          {{"f", "from-code"},
                           QCoreApplication::translate("main", "set input encoding to LABEL (defaults to UTF-8)."),
                           QCoreApplication::translate("main", "LABEL"),
                          },
                          {{"t", "to-code"},
                           QCoreApplication::translate("main", "set output encoding to LABEL (defaults to UTF-8)."),
                           QCoreApplication::translate("main", "LABEL"),
                          },
                      });
    parser.addPositionalArgument("files", QCoreApplication::translate("main", "files to read (- for stdin; the default)."), "[files...]");
    parser.process(app);

    RecodeQMain recode(parser.positionalArguments(),
                       parser.value("output"),
                       parser.value("from-code"),
                       parser.value("to-code"));
    QObject::connect(&recode, SIGNAL(done()), &app, SLOT(quit()), Qt::QueuedConnection);
    QTimer::singleShot(0, &recode, SLOT(run()));
    return app.exec();
}
