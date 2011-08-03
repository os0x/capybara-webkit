#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class NetworkAccessManager : public QNetworkAccessManager {

  Q_OBJECT

  public:
    NetworkAccessManager(bool jscoverage_flag, QObject *parent = 0);
    void addHeader(QString key, QString value);

  protected:
    QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice * outgoingData);

  private:
    QHash<QString, QString> m_headers;
    bool m_jscoverage_flag;
};