#include "tasklist.h"
#include "fileexiststask.h"
#include "printdebugtask.h"
#include <QDebug>

TaskList* TaskList::instance = 0;
QList<Task *> TaskList::List;

TaskList* TaskList::getInstance() {
	if(instance == 0)
	{
        qDebug() << "Creating a new instance of TaskList";
		instance = new TaskList();
	}
	
	return instance;
}

void TaskList::Serialize() {
    qDebug() << "Serializing TaskList...";

    // To be implemented
}

void TaskList::Deserialize() {
    // This is an oversimplification
    qDebug() << "Deserializing TaskList...";

	FileExistsTask *task1 = new FileExistsTask();
    task1->SetDescription(QString("Task1"));
	task1->Parameters.SetFilename(QString("C:/ESEMPIO.txt"));
	task1->SetSchedulingType(SchedulingType::Periodic);
    task1->SetDayOfWeek(DayOfWeek::EveryWeekDay, true);
    task1->SetPeriod(10);
    task1->SetActive(true);

	TaskList::List.append(task1);
	
	PrintDebugTask *task2 = new PrintDebugTask();
    task2->SetDescription(QString("Task2"));
	task2->Parameters.SetText(QString("This is a text"));
	task2->SetSchedulingType(SchedulingType::Periodic);
    task2->SetDayOfWeek(DayOfWeek::EveryWeekDay, true);
    task2->SetPeriod(30);
	task2->SetActive(true);
	
	TaskList::List.append(task2);
}

void TaskList::updatePrintDebugTask(QString text) {
    // This is an oversimplification
    Task *task = TaskList::List[1];

    auto *pdTask = dynamic_cast<PrintDebugTask*> (task);
    if(pdTask != nullptr)
    {
        pdTask->Parameters.SetText(text);
    }


}

TaskList::TaskList() {
	TaskList::Deserialize();
}
