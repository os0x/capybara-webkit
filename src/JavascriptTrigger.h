#include <QObject>
#include <QString>
#include <QStringList>

class WebPage;

class JavascriptTrigger : public QObject {
  Q_OBJECT

  public:
    JavascriptTrigger(QObject *parent = 0);
    void set_page(WebPage *page);
  public slots:
    QString get() const;
    void set(const QString &json, const QString &port);
    void specFinished();
    void specStart();
    void handleQuit();

  private:
    QString m_jsonData;
    QString m_port;
    WebPage *m_page;
};

