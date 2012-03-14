/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_
#define _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>
#include "UpdateSystem_global.h"

#include "Downloader/MultiFileDownloader.h"
#include "Downloader/MultiFileDownloadInterface.h"
#include "Downloader/MultiDownloadResultInterface.h"
#include "Extractor/ExtractorInterface.h"

namespace GGS {
  namespace Downloader {

    class UPDATESYSTEMSHARED_EXPORT MultiFileDownloaderWithExtracter : public QObject,
      public MultiFileDownloadInterface,
      public MultiFileDownloadResultInterface
    {
    public:
      explicit MultiFileDownloaderWithExtracter(QObject *parrent = 0);
      virtual ~MultiFileDownloaderWithExtracter(void);

      virtual void setResultCallback( MultiFileDownloadResultInterface *resultCallback ) {
        this->_resultCallback = resultCallback;
      }

      virtual void addFile( const QString& url, const QString& targetFilePath );
      virtual void start();

      // MultiFileDownloadResultInterface
      virtual void fileDownloaded(const QString& filePath);
      virtual void downloadResult( bool isError, DownloadResults error );
      virtual void downloadProgress( quint64 downloadSize, quint64 currentFileDownloadSize, quint64 currestFileSize );
      virtual void downloadWarning( bool isError, DownloadResults error );

      void setMultiDownloader(MultiFileDownloader *multiDownloader) { 
        this->_multiDownloader = multiDownloader; 
        this->_multiDownloader->setResultCallback(this);
      }

      void setExtractor(GGS::Extractor::ExtractorInterface *extractor) {
          this->_extractor = extractor;
      }

    private:
      MultiFileDownloadResultInterface *_resultCallback;
      MultiFileDownloader *_multiDownloader;
      GGS::Extractor::ExtractorInterface *_extractor;
    };

  }
}

#endif // _GGS_DOWNLOAD_MULTIFILEDOWANLOEDERWITHEXTRACTER_H_