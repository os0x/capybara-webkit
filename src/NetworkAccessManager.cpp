#include "NetworkAccessManager.h"
#include "WebPage.h"
#include <iostream>


NetworkAccessManager::NetworkAccessManager(QObject *parent):QNetworkAccessManager(parent) {
}

QNetworkReply* NetworkAccessManager::createRequest(QNetworkAccessManager::Operation oparation, const QNetworkRequest &request, QIODevice * outgoingData = 0) {
  if (request.url().toString().startsWith("http://www.example.com")) {
    request.url().setUrl(request.url().toString().replace("http://www.example.com", m_default_host))
    //request.setUrl()
  } else {
  QHashIterator<QString, QString> item(m_headers);
  while (item.hasNext()) {
      item.next();
      request.setRawHeader(item.key().toAscii(), item.value().toAscii());
  }
  return QNetworkAccessManager::createRequest(oparation, request, outgoingData);
};

void NetworkAccessManager::addHeader(QString key, QString value) {
  m_headers.insert(key, value);
};

