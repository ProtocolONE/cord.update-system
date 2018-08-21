#include <UpdateSystem/Downloader/MultiFileDownloaderWithExtracter.h>

namespace P1 {
  namespace Downloader {

    MultiFileDownloaderWithExtracter::MultiFileDownloaderWithExtracter(QObject *parrent)
      : QObject(parrent)
    {
    }


    MultiFileDownloaderWithExtracter::~MultiFileDownloaderWithExtracter()
    {
    }

    void MultiFileDownloaderWithExtracter::addFile(const QString& url, const QString& targetFilePath)
    {
      QString archiveUrl = url;
      archiveUrl.append(".7z");
      QString archivePath = targetFilePath;
      archivePath.append(".7z");
      this->_multiDownloader->addFile(archiveUrl, archivePath);
    }

    void MultiFileDownloaderWithExtracter::start()
    {
      this->_multiDownloader->start();
    }

    void MultiFileDownloaderWithExtracter::fileDownloaded(const QString& filePath)
    {
      int q = filePath.lastIndexOf('/');
      QString extractedFile = filePath.mid(0, q);

      P1::Extractor::ExtractionResult result = this->_extractor->extract(filePath, extractedFile);
      if(result != P1::Extractor::NoError) {
        this->_resultCallback->downloadResult(true, ExtractionError);
        return;
      }

      QFile::remove(filePath);
      
      QString path = filePath;
      path.remove(filePath.count() - 3, 3);

      this->_resultCallback->fileDownloaded(path);
    }

    void MultiFileDownloaderWithExtracter::downloadResult(bool isError, DownloadResults error)
    {
      this->_resultCallback->downloadResult(isError, error);
    }

    void MultiFileDownloaderWithExtracter::downloadProgress(quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize)
    {
      this->_resultCallback->downloadProgress(downloadSize, currentFileDownloadSize, currestFileSize);
    }

    void MultiFileDownloaderWithExtracter::downloadWarning(bool isError, DownloadResults error)
    {
      this->_resultCallback->downloadWarning(isError, error);
    }

    void MultiFileDownloaderWithExtracter::setMultiDownloader(MultiFileDownloader *multiDownloader)
    {
      this->_multiDownloader = multiDownloader; 
      this->_multiDownloader->setResultCallback(this);
    }

    void MultiFileDownloaderWithExtracter::setExtractor(P1::Extractor::ExtractorInterface *extractor)
    {
      this->_extractor = extractor;
    }

    void MultiFileDownloaderWithExtracter::setResultCallback(MultiFileDownloadResultInterface *resultCallback)
    {
      this->_resultCallback = resultCallback;
    }

  }
}