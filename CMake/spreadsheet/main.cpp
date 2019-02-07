#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QTranslator qtTranslator;
  qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&qtTranslator);
  QTranslator myappTranslator;
  myappTranslator.load("spreadsheet_" + QLocale::system().name());
  app.installTranslator(&myappTranslator);

  MainWindow mainWin;
  mainWin.show();
  return QApplication::exec();
}
