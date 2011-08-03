#include <QtWebKit>
#include "JavascriptTrigger.h"

class WebPage : public QWebPage {
  Q_OBJECT

  public:
    WebPage(QObject *parent = 0);
    QVariant invokeCapybaraFunction(const char *name, QStringList &arguments);
    QVariant invokeCapybaraFunction(QString &name, QStringList &arguments);
    QString failureString();
    QString userAgentForUrl(const QUrl &url ) const;
    bool getJscoverageFlag();
    void setUserAgent(QString userAgent);
    int getLastStatus();
    void resetResponseHeaders();
    void setCustomNetworkAccessManager();
    bool render(const QString &fileName);
    virtual bool extension (Extension extension, const ExtensionOption *option=0, ExtensionReturn *output=0);
    void setIgnoreSslErrors(bool ignore);
    bool ignoreSslErrors();

  public slots:
    bool shouldInterruptJavaScript();
    void injectJavascriptHelpers();
    void loadStarted();
    void loadFinished(bool);
    void specStart();
    void specFinished();
    bool isLoading() const;
    QString pageHeaders();
    void frameCreated(QWebFrame *);
    void replyFinished(QNetworkReply *reply);
    void ignoreSslErrors(QNetworkReply *reply, const QList<QSslError> &);
    void handleUnsupportedContent(QNetworkReply *reply);

  signals:
    void pageFinished(bool);

  signals:
    void loadAndSpecFinished(bool);

  protected:
    virtual void javaScriptConsoleMessage(const QString &message, int lineNumber, const QString &sourceID);
    virtual void javaScriptAlert(QWebFrame *frame, const QString &message);
    virtual bool javaScriptConfirm(QWebFrame *frame, const QString &message);
    virtual bool javaScriptPrompt(QWebFrame *frame, const QString &message, const QString &defaultValue, QString *result);
    virtual QString chooseFile(QWebFrame * parentFrame, const QString &suggestedFile);

  private:
    JavascriptTrigger m_javascript_trigger;
    QString m_capybaraJavascript;
    QString m_userAgent;
    bool m_loading;
    bool m_spec_running;
    bool m_success;
    bool m_jscoverage_flag;
    QString getLastAttachedFileName();
    void loadJavascript();
    void setUserStylesheet();
    int m_lastStatus;
    QString m_pageHeaders;
    bool m_ignoreSslErrors;
};

