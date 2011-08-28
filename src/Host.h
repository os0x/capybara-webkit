#include "Command.h"

class WebPage;

class Host : public Command {
  Q_OBJECT

  public:
    Host(WebPage *page, QObject *parent = 0);
    virtual void start(QStringList &arguments);
};
