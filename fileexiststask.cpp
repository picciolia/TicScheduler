#include "fileexiststask.h"
#include <QDebug>
#include <QFile>

FileExistsTask::FileExistsTask() : TTask() {}

void FileExistsTask::Run() {
  QFile file;
  QString filename = Parameters.GetFilename();

  if ((filename.isNull() == false) && (filename.isEmpty() == false)) {
    file.setFileName(filename);

    if (file.exists() == false) {
      qDebug() << "The file " << filename << "doesn't exists";
    }
  }
}
