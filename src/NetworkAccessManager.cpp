#include "NetworkAccessManager.h"
#include "WebPage.h"
#include <iostream>
#include <QDebug>

bool NetworkAccessManager::m_jscoverage_flag = false;
QString NetworkAccessManager::m_javascript_file_path = "";

NetworkAccessManager::NetworkAccessManager(WebPage *page, QObject *parent):QNetworkAccessManager(parent) {
  m_page = page;
  m_ajax_request_flag = false;
  connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
  connect(this, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), this, SLOT(slotSslErrors(QNetworkReply*, QList<QSslError>)));
};

void NetworkAccessManager::setJscoverageFlag(bool jscoverage_flag) {
  m_jscoverage_flag = jscoverage_flag;
};

void NetworkAccessManager::setJscoveragePath(QString javascript_file_path) {
  m_javascript_file_path = javascript_file_path;
};

void NetworkAccessManager::replyFinished(QNetworkReply* network_reply) {
  if (network_reply->isFinished() && m_ajax_request_flag) {
    m_page->currentFrame()->evaluateJavaScript("setTimeout(function(){CapybaraObject.onload();}, 10);");
    m_ajax_request_flag = false;
  }
};

void NetworkAccessManager::slotSslErrors(QNetworkReply* reply, QList<QSslError> const & errors) {
  Q_UNUSED(errors);
  reply->ignoreSslErrors();
};

QNetworkReply* NetworkAccessManager::createRequest(QNetworkAccessManager::Operation operation, const QNetworkRequest &request, QIODevice * outgoingData = 0) {
  QNetworkRequest new_request(request);
  if (operation != QNetworkAccessManager::PostOperation && operation != QNetworkAccessManager::PutOperation) {
    new_request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant());
  }
  if (!m_page->isLoading()) {
    m_ajax_request_flag = true;
    m_page->loadStarted();
  }
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
  QUrl url = request.url();
  if (url.scheme() == "https") {
    url.setUrl(url.toString().replace("https://", "http://"));
  }
  if (url.host() == m_page->getDefaultHost()) {
    url.setUrl(url.toString().replace(m_page->getDefaultHost(), m_page->getRealHost()));
  }
  new_request.setUrl(url);

  QHashIterator<QString, QString> item(m_headers);
  while (item.hasNext()) {
    item.next();
    new_request.setRawHeader(item.key().toAscii(), item.value().toAscii());
  }
  return QNetworkAccessManager::createRequest(operation, new_request, outgoingData);
};

void NetworkAccessManager::addHeader(QString key, QString value) {
  m_headers.insert(key, value);
};
