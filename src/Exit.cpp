#include "Exit.h"
#include "WebPage.h"

Exit::Exit(WebPage *page, QObject *parent) : Command(page, parent) {
}

void Exit::start(QStringList &arguments) {
  Q_UNUSED(arguments);
  QCoreApplication::instance()->exit(0);
}
