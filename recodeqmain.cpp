#include "recodeqmain.h"

RecodeQMain::RecodeQMain() : QObject(nullptr)
{
}

void
RecodeQMain::run()
{
    printf("Hello World!\n");
    emit done();
}
