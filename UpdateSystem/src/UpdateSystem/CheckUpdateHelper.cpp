#include <UpdateSystem/CheckUpdateHelper.h>

#include <QtCore/QDebug>
#define CRITICAL_LOG qCritical() << __FILE__ << __LINE__ << __FUNCTION__

namespace GGS {
  namespace UpdateSystem {

    CheckUpdateHelper::CheckUpdateHelper(QObject *parent)
      : QObject(parent)
      , _isInitialized(false)
    {
      this->_manager = new QNetworkAccessManager(this);
    }

    CheckUpdateHelper::~CheckUpdateHelper()
    {
    }

    void CheckUpdateHelper::checkUpdate()
    {
      Q_ASSERT(!this->_updateUrl.isEmpty());
      QNetworkRequest request(this->_updateUrl);

      if (this->_isInitialized)
        request.setRawHeader("If-Modified-Since", this->_lastModified.toLatin1());

      QNetworkReply *reply = this->_manager->head(request);
      SIGNAL_CONNECT_CHECK(connect(reply, SIGNAL(finished()), this, SLOT(slotReplyDownloadFinished())));
    }

    void CheckUpdateHelper::setUpdateUrl(const QString& updateUrl)
    {
      this->_updateUrl = updateUrl;
    }

    void CheckUpdateHelper::slotReplyDownloadFinished()
    {
      QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
      if (!reply)
        return;

      reply->deleteLater();

      int httpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      // Http codes defined by rfc: http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
      // 200 OK
      // 304 Not Modified
      if (httpCode != 304 && httpCode != 200) {
        CRITICAL_LOG << "Http error" << httpCode;
        emit this->finished(Error);
        return;
      }

      QString lastModified = QString::fromLatin1(reply->rawHeader(QByteArray("Last-Modified")));
      if (!this->_isInitialized) {
        this->_lastModified = lastModified;
        this->_isInitialized = true;
        emit this->finished(NotFound);
        return;
      }

      emit this->finished(lastModified == this->_lastModified ? NotFound : FoundUpdate);
    }
  }
}
