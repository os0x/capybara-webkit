#include "NetworkAccessManager.h"
#include "WebPage.h"
#include <iostream>
#include <QDebug>

bool NetworkAccessManager::m_jscoverage_flag = false;
QString NetworkAccessManager::m_javascript_file_path = "";

NetworkAccessManager::NetworkAccessManager(QObject *parent):QNetworkAccessManager(parent) {
}

void NetworkAccessManager::setJscoverageFlag(bool jscoverage_flag) {
  m_jscoverage_flag = jscoverage_flag;
}

void NetworkAccessManager::setJscoveragePath(QString javascript_file_path) {
  m_javascript_file_path = javascript_file_path;
}

QNetworkReply* NetworkAccessManager::createRequest(QNetworkAccessManager::Operation oparation, const QNetworkRequest &request, QIODevice * outgoingData = 0) {
  if ("googleads.g.doubleclick.net" == request.url().host() || "pagead2.googlesyndication.com" == request.url().host()) {
    return QNetworkAccessManager::createRequest(oparation, QNetworkRequest(QUrl()));
  }
  if (m_jscoverage_flag && request.url().path().startsWith("/javascripts/")) {
    QUrl url = request.url();
    url.setPath(url.path().replace("/javascripts/", m_javascript_file_path));
    QNetworkRequest new_request(url);
    return QNetworkAccessManager::createRequest(oparation, new_request, outgoingData);
  }
  QNetworkRequest new_request(request);
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
