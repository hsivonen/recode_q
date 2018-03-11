#include "recodeqmain.h"

#include <QTextStream>

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

void
RecodeQMain::run()
{
    QTextStream out(stdout);
    out << "Output: ";
    out << output;
    out << "\n";
    out << "From: ";
    out << fromLabel;
    out << "\n";
    out << "To: ";
    out << toLabel;
    out << "\n";
    out << "Positional: ";
    for (auto&& arg: inputs) {
        out << "\n";
        out << arg;
    }
    out << "\n";

    emit done();
}
