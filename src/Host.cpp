#include "Host.h"
#include "WebPage.h"

Host::Host(WebPage *page, QObject *parent) : Command(page, parent) {
}

void Host::start(QStringList &arguments) {
  page()->setDefaultHost(QString(arguments[0]));
  emit finished(new Response(true));
}
