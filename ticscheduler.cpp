#include "TicScheduler.h"

#include "tasklist.h"
#include <QAction>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDebug>
#include <QIcon>
#include <QMenu>
#include <QtWidgets>

using namespace TI_Care;

TicScheduler::TicScheduler() {
  createActions();
  createTrayIcon();
  setIcon();

  trayIcon->show();

  // Get the task list
  taskList = TaskList::getInstance();

  // This is an oversimplification: an improvement could be to use a Model/View
  // pattern to create a tab for each task using a dedicated widget for each
  // TTask<T> template
  label = new QLabel("Text");
  textEdit = new QLineEdit("This is a text");
  updateButton = new QPushButton("Update");
  QObject::connect(updateButton, &QPushButton::clicked, this, &updateTaskList);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(label);
  layout->addWidget(textEdit);
  layout->addWidget(updateButton);
  setLayout(layout);

  setWindowTitle(tr("TI-Care Scheduler"));
  resize(300, 50);

  // Background processing is done using a timer to schedule execution
  // See TicScheduler::timerTimeout() for more details
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &timerTimeout);
  timer->start(1000); // 1 second timer as base tick for scheduler
}

void TicScheduler::setVisible(bool visible) {
  minimizeAction->setEnabled(visible);
  maximizeAction->setEnabled(!isMaximized());
  restoreAction->setEnabled(isMaximized() || !visible);
  QDialog::setVisible(visible);
}

void TicScheduler::closeEvent(QCloseEvent *event) {
  if (trayIcon->isVisible()) {
    hide();
    event->ignore();
  }
}

void TicScheduler::createActions() {
  minimizeAction = new QAction(tr("Mi&nimize"), this);
  connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

  maximizeAction = new QAction(tr("Ma&ximize"), this);
  connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

  restoreAction = new QAction(tr("&Restore"), this);
  connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

  quitAction = new QAction(tr("&Quit"), this);
  connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void TicScheduler::createTrayIcon() {
  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(minimizeAction);
  trayIconMenu->addAction(maximizeAction);
  trayIconMenu->addAction(restoreAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  trayIcon = new QSystemTrayIcon(this);
  trayIcon->setContextMenu(trayIconMenu);
}

void TicScheduler::setIcon() {
  QIcon icon = QIcon(":/Images/schedule.png");
  trayIcon->setIcon(icon);
  setWindowIcon(icon);
}

// At each timer timeout, the task list is checked to verify the tasks to be
// executed immediately
void TicScheduler::timerTimeout() {
  if (taskList != nullptr) {
    for (int taskIndex = 0; taskIndex < taskList->List.size(); taskIndex++) {
      Task *currentTask = TaskList::List[taskIndex];
      if (currentTask->IsToBeExecuted() == true) {
        currentTask->Run();
      }
    }
  } else {
    // Trace error
  }
}

void TicScheduler::updateTaskList() {
  // This is an oversimplification: using a mapping between the widgets and data
  // it could be possible to update each task in the task list in a better way
  if (taskList != nullptr) {
    taskList->updatePrintDebugTask(textEdit->text());
  } else {
    // Trace error
  }
}
