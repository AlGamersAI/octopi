#include "../../src/unixcommand.h"
#include "../../src/wmhelper.h"
#include "mainwindow.h"

#include <QApplication>
#include <QtGui>

//#define NO_GTK_STYLE

int main(int argc, char *argv[])
{
  if (UnixCommand::isAppRunning("octopi-notifier")) return (-1);

  QApplication a(argc, argv);

#if QT_VERSION < 0x050000
  #ifndef NO_GTK_STYLE
  QApplication::setGraphicsSystem(QLatin1String("raster"));

  if(!WMHelper::isKDERunning() && (!WMHelper::isLXQTRunning()) && (!WMHelper::isRazorQtRunning()))
  {
    qApp->setStyle(new QGtkStyle());
  }
  else
    qApp->setStyle(new QCleanlooksStyle);
  #endif
#endif

  QTranslator appTranslator;
  appTranslator.load(":/resources/translations/octopi_" +
                     QLocale::system().name());
  a.installTranslator(&appTranslator);
  a.setQuitOnLastWindowClosed(false);

  MainWindow w;
  QResource::registerResource("./resources.qrc");

  return a.exec();
}
