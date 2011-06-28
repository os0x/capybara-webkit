#include "NetworkAccessManager.h"
#include "WebPage.h"
#include <iostream>

NetworkAccessManager::NetworkAccessManager(QObject *parent):QNetworkAccessManager(parent) {
}

QNetworkReply* NetworkAccessManager::createRequest(QNetworkAccessManager::Operation oparation, const QNetworkRequest &request, QIODevice * outgoingData = 0) {
  if ("googleads.g.doubleclick.net" == request.url().host() || "pagead2.googlesyndication.com" == request.url().host()) {
    return QNetworkAccessManager::createRequest(oparation, QNetworkRequest(QUrl()));
  } else {
    QNetworkRequest new_request(request);
    QHashIterator<QString, QString> item(m_headers);
    while (item.hasNext()) {
      item.next();
      new_request.setRawHeader(item.key().toAscii(), item.value().toAscii());
    }
    return QNetworkAccessManager::createRequest(oparation, new_request, outgoingData);
  }
};

void NetworkAccessManager::addHeader(QString key, QString value) {
  m_headers.insert(key, value);
};

