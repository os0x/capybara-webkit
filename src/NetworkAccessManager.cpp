#include "NetworkAccessManager.h"
#include "WebPage.h"
#include <iostream>

NetworkAccessManager::NetworkAccessManager(WebPage *page, QObject *parent):QNetworkAccessManager(parent) {
  m_page = page;
}

QNetworkReply* NetworkAccessManager::createRequest(QNetworkAccessManager::Operation oparation, const QNetworkRequest &request, QIODevice * outgoingData = 0) {
  QNetworkRequest new_request(request);
  if (request.url().toString().startsWith("http://www.example.com")) {
    QUrl url = request.url();
    url.setUrl(request.url().toString().replace("http://www.example.com", m_page->getDefaultHost()));
    new_request.setUrl(url);
  }
  QHashIterator<QString, QString> item(m_headers);
  while (item.hasNext()) {
      item.next();
      new_request.setRawHeader(item.key().toAscii(), item.value().toAscii());
  }
  return QNetworkAccessManager::createRequest(oparation, new_request, outgoingData);
};

void NetworkAccessManager::addHeader(QString key, QString value) {
  m_headers.insert(key, value);
};

