#pragma once

#include <UpdateSystem/Downloader/MultiDownloadResultInterface.h>

#include <QtCore/QString>

namespace P1 {
  namespace Downloader {

    class MultiFileDownloadInterface {
    public:
      ~MultiFileDownloadInterface() {}
      virtual void setResultCallback(MultiFileDownloadResultInterface *resultCallback) = 0;
      virtual void addFile(const QString& url, const QString& targetFilePath) = 0;
      virtual void start() = 0;
    };

  }
}
