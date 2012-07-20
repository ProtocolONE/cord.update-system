#ifndef _GGS_UPDATESYSTEM_CHECKUPDATEHELPER_H_
#define _GGS_UPDATESYSTEM_CHECKUPDATEHELPER_H_

#include <UpdateSystem/UpdateSystem_global>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtNetwork/QNetworkReply>

namespace GGS {
  namespace UpdateSystem {

    class UPDATESYSTEMSHARED_EXPORT CheckUpdateHelper : public QObject
    {
      Q_OBJECT
      Q_ENUMS(GGS::UpdateSystem::CheckUpdateHelper::Results)
    public:
      enum Results {
        NotFound = 0,
        Error,
        FoundUpdate
      };

      explicit CheckUpdateHelper(QObject *parent = 0);
      ~CheckUpdateHelper();

      void setUpdateUrl(const QString& updateUrl);

    public slots:
      void checkUpdate();

    signals:
      void finished(GGS::UpdateSystem::CheckUpdateHelper::Results result);

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

Q_DECLARE_METATYPE(GGS::UpdateSystem::CheckUpdateHelper::Results);
#endif // _GGS_UPDATESYSTEM_CHECKUPDATEHELPER_H_