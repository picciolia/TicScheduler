#include "ticscheduler.h"
#include <QtWidgets>

int main(int argc, char *argv[]) {
  // Creates an instance of QApplication
  QApplication a(argc, argv);

  // This is our class containing our GUI and functionality
  TicScheduler w;
  w.show(); // Show main window

  // run the application and return execs() return value/code
  return a.exec();
}
