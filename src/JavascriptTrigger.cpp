#include "Server.h"
#include "WebPage.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>

JavascriptTrigger::JavascriptTrigger(QObject *parent) : QObject(parent) {
  connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(handleQuit()));
}

void JavascriptTrigger::set_page(WebPage *page) {
  m_page = page;
}

void JavascriptTrigger::specFinished() {
  m_page->specFinished();
}

void JavascriptTrigger::specStart() {
  m_page->specStart();
}

void JavascriptTrigger::handleQuit() {
  if (m_port.isEmpty()) {
    return;
  }
  QString dir = QString(getenv("JSCOVERAGE_REPORT"));
  QString path = dir + QString("/jscoverage.") + m_port  + QString(".json");
  QFile *_f = new QFile(path);
  QFile::OpenMode modeCode = QFile::NotOpen;
  modeCode |= QFile::WriteOnly;
  if ( _f->exists() || QDir().mkpath((QFileInfo(path).dir().absolutePath())) ) {
    if ( _f->open(modeCode) ) {
      QTextStream file_stream;
      file_stream.setDevice(_f);
      file_stream << m_jsonData;
      file_stream.flush();
      _f->close();
    }
  }
}

void JavascriptTrigger::set(const QString &json, const QString &port) {
  m_jsonData = json;
  m_port = port;
}
QString JavascriptTrigger::get() const {
  if (m_jsonData.isEmpty()) {
    return QString("{}");
  } else {
    return m_jsonData;
  }
}
