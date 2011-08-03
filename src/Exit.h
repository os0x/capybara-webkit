#include "Command.h"

class WebPage;

class Exit : public Command {
  Q_OBJECT

  public:
    Exit(WebPage *page, QObject *parent = 0);
    virtual void start(QStringList &arguments);
};

