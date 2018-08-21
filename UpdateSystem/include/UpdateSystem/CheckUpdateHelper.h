#pragma once

#include <UpdateSystem/UpdateSystem_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtNetwork/QNetworkReply>

namespace P1 {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT CheckUpdateHelper : public QObject
    {
      Q_OBJECT
      Q_ENUMS(P1::UpdateSystem::CheckUpdateHelper::Results)
    public:
      enum Results {
        NotFound = 0,
        Error,
        FoundUpdate
      };

      explicit CheckUpdateHelper(QObject *parent = 0);
      virtual ~CheckUpdateHelper();

      void setUpdateUrl(const QString& updateUrl);

    public slots:
      void checkUpdate();

    signals:
      void finished(P1::UpdateSystem::CheckUpdateHelper::Results result);

    private slots:
      void slotReplyDownloadFinished();

    private:
      bool _isInitialized;
      QString _updateUrl;
      QString _lastModified;
      QNetworkAccessManager *_manager;
    };

  }
}

Q_DECLARE_METATYPE(P1::UpdateSystem::CheckUpdateHelper::Results);
