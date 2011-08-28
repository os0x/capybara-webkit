#include "Host.h"
#include "WebPage.h"

Host::Host(WebPage *page, QObject *parent) : Command(page, parent) {
}

void Host::start(QStringList &arguments) {
  page()->setRealHost(QString(arguments[0]));
  page()->setDefaultHost(QString(arguments[1]));
  emit finished(new Response(true));
}
