#pragma once

#include <UpdateSystem/Downloader/DownloadResultInterface.h>

namespace P1 {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT MultiFileDownloadResultInterface
    {
    public:
      ~MultiFileDownloadResultInterface() {};

      virtual void fileDownloaded(const QString& filePath) = 0;
      virtual void downloadResult(bool isError, DownloadResults error) = 0;
      virtual void downloadProgress(quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize) = 0;
      virtual void downloadWarning(bool isError, DownloadResults error) = 0;
    };
  }
}
