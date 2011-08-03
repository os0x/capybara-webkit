//#include "JavascriptTrigger.h"
#include "Server.h"
#include "WebPage.h"
#include <QDebug>

#include <QFile>
#include <QFileInfo>
#include <QDir>

JavascriptTrigger::JavascriptTrigger(QObject *parent) : QObject(parent) {
}

void JavascriptTrigger::set_page(WebPage *page) {
  //m_page = page;
}

void JavascriptTrigger::specFinished() {
  //m_page->specFinished();
}

void JavascriptTrigger::set(const QString &json, const QString &port) {
  m_jsonData = json;
  QString path = QString("/tmp/js/jscoverage") + port  + QString(".json");
  QFile *_f = new QFile(path);
  QFile::OpenMode modeCode = QFile::NotOpen;
  modeCode |= QFile::WriteOnly;
  if ( _f->exists() || QDir().mkpath((QFileInfo(path).dir().absolutePath())) ) {
    if ( _f->open(modeCode) ) {
      QTextStream file_stream;
      file_stream.setDevice(_f);
      file_stream << json;
      file_stream.flush();
      _f->close();
    }
  }
}
QString JavascriptTrigger::get() const {
  if (m_jsonData.isEmpty()) {
    return QString("{}");
  } else {
    return m_jsonData;
  }
}
