#ifndef TICSCHEDULER_H
#define TICSCHEDULER_H

#include "tasklist.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QWidget>

// This is the declaration of main dialog class
// The definition/implementation is in ticscheduler.cpp
// A Model/View pattern has not been implemented for this application
class TicScheduler : public QDialog {
  Q_OBJECT

public:
  TicScheduler();

  void setVisible(bool visible) override;

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  void createActions();
  void createTrayIcon();
  void setIcon();
  void timerTimeout();
  void updateTaskList();

  TaskList *taskList;

  QAction *minimizeAction;
  QAction *maximizeAction;
  QAction *restoreAction;
  QAction *quitAction;
  QTimer *timer;

  QLabel *label;
  QLineEdit *textEdit;
  QPushButton *updateButton;
  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;
};

#endif
