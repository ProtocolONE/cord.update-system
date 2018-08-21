#include <UpdateSystem/Downloader/RetryFileDownloader.h>
#include <UpdateSystem/Downloader/DynamicRetryTimeout.h>

namespace P1 {
  namespace Downloader {
    RetryFileDownloader::RetryFileDownloader(QObject *parrent)
      : QObject(parrent)
      , _maxRetryCount(0)
      , _retryCount(0)
      , _networkError(QNetworkReply::NoError)
    {
    }

    RetryFileDownloader::~RetryFileDownloader()
    {
    }

    void RetryFileDownloader::setResultCallback(DownloadResultInterface *result)
    {
      this->_resultCallback = result;
    }

    void RetryFileDownloader::downloadFile(const QString& url,const QString& filePath)
    {
      this->_url = url;
      this->_filePath = filePath;

      this->_downloader->setResultCallback(this);
      this->internalStartDownload();
    }

    void RetryFileDownloader::downloadResult(bool isError, DownloadResults error)
    {
      if(!isError) {
        this->_resultCallback->downloadResult(false, NoError);
        return;
      }

      this->_networkError = this->_downloader->getNetworkError();
      this->_retryCount++;

      if(this->_maxRetryCount == P1::Downloader::DynamicRetryTimeout::InfinityRetryCount || this->_retryCount < this->_maxRetryCount) {
        this->_resultCallback->downloadWarning(true, error);

        int timeout = this->_timeout->getTimeout(this->_retryCount);
        emit downloadRetryNumber(_retryCount);
        if(timeout > 0) {
          QTimer::singleShot(timeout, this, SLOT(internalStartDownload()));
        } else {
          this->internalStartDownload();
        }

      } else {
        this->_resultCallback->downloadResult(true, error);
      }
    }

    void RetryFileDownloader::downloadProgress(quint64 current, quint64 total)
    {
      this->_resultCallback->downloadProgress(current, total);
    }

    void RetryFileDownloader::setDownloader(FileDownloaderInterface *downloader)
    {
      this->_downloader = downloader;
    }

    void RetryFileDownloader::setTimeout(RetryTimeoutInterface *timeout)
    {
      this->_timeout = timeout;
    }

    void RetryFileDownloader::setMaxRetry(qint32 maxRetryCount)
    {
      this->_maxRetryCount = maxRetryCount;
    }

    QNetworkReply::NetworkError RetryFileDownloader::getNetworkError()
    {
      return this->_networkError;
    }

    void RetryFileDownloader::internalStartDownload()
    {
      this->_downloader->downloadFile(this->_url, this->_filePath);
    }

    void RetryFileDownloader::downloadWarning(bool isError, DownloadResults error)
    {
      this->_resultCallback->downloadWarning(isError, error);
    }
  }
}