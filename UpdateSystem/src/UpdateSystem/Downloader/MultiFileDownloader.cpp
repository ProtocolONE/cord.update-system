/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <UpdateSystem/Downloader/MultiFileDownloader.h>

namespace GGS {
  namespace Downloader {
    MultiFileDownloader::MultiFileDownloader(QObject *parrent)
      : QObject(parrent)
    {
      this->_complitedFileSized = 0;
    }

    MultiFileDownloader::~MultiFileDownloader(void)
    {
    }

    void MultiFileDownloader::addFile( const QString& url, const QString& targetFilePath )
    {
      this->_fileQueue.enqueue( QPair<QString,QString>(url, QDir::cleanPath(targetFilePath)) );
    }

    void MultiFileDownloader::start()
    {
      this->processNextFile();
    }

    void MultiFileDownloader::downloadResult( bool isError, DownloadResults error )
    {
      if (isError) {
        this->_networkError = this->_downloader->getNetworkError();
        this->_resultCallback->downloadResult(isError, error);
        return;
      }

      this->_complitedFileSized += this->_currentFileTotalSize;
      this->_resultCallback->fileDownloaded(this->_currentFile.second);

      this->processNextFile();
    }

    void MultiFileDownloader::downloadWarning( bool isError, DownloadResults error )
    {
      this->_networkError = this->_downloader->getNetworkError();
      this->_resultCallback->downloadWarning(isError, error);
    }

    void MultiFileDownloader::downloadProgress( quint64 current, quint64 total )
    {
      this->_currentFileProgres = current;
      this->_currentFileTotalSize = total;
      this->_resultCallback->downloadProgress(
        this->_complitedFileSized + this->_currentFileProgres, 
        this->_currentFileProgres, 
        this->_currentFileTotalSize);
    }

    void MultiFileDownloader::processNextFile()
    {
      this->_currentFileProgres = 0;
      this->_currentFileTotalSize = 0;
      if (this->_fileQueue.size() > 0) {
        this->_currentFile = this->_fileQueue.dequeue();
        this->_downloader->downloadFile(this->_currentFile.first, this->_currentFile.second);
      } else {
        this->_resultCallback->downloadResult(false, NoError);
      }
    }
  }
}