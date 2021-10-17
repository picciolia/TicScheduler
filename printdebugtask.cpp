#include "printdebugtask.h"

#include <QDebug>

PrintDebugTask::PrintDebugTask() : TTask() {}

void PrintDebugTask::Run() { qDebug() << Parameters.GetText(); }
