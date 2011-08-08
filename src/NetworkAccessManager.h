#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class NetworkAccessManager : public QNetworkAccessManager {

  Q_OBJECT

  public:
    NetworkAccessManager(QObject *parent = 0);
    void addHeader(QString key, QString value);
    void setJscoverageFlag(bool jscoverage_flag);
    void setJscoveragePath(QString javascript_file_path);

  protected:
    QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &req, QIODevice * outgoingData);

  private:
    QHash<QString, QString> m_headers;
    static bool m_jscoverage_flag;
    static QString m_javascript_file_path;
};