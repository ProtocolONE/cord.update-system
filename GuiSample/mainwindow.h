#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC


#include <QMainWindow>
#include <QtCore/QThread>
#include <QtCore/QPointer>

#include <QtCore/QProcess>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <UpdateSystem/UpdateManagerWorker>
#include <UpdateSystem/updatemanager>

#include <UpdateSystem/UpdateInfoGetter>
#include <UpdateSystem/UpdateInfoGetterInterface>
#include <UpdateSystem/UpdateInfoGetterResultInterface>
#include <UpdateSystem/Extractor/SevenZipExtractor>

#include <UpdateSystem/Downloader/RetryFileDownloader>
#include <UpdateSystem/Downloader/downloadmanager>
#include <UpdateSystem/Downloader/MultiFileDownloader>
#include <UpdateSystem/Downloader/MultiFileDownloaderWithExtracter>
#include <UpdateSystem/Hasher/Md5FileHasher>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void finishedSlot(QNetworkReply* reply);

private slots:
    void on_pushButton_clicked();
    

    void slotFileDownloadString(QString str);

    void slotAllCompleted(bool isNeedRestart);
    void slotDownloadUpdateProgress(quint64 currentSize, quint64 totalSize);
    void slotDownloadUpdateWarning(GGS::Downloader::DownloadResults error);

    // think about error, may be new enum?
    void slotFatalError();

    /*void fileDownloadString(QString path);
    void messageRecieved(QString str);
    void allCompleted();*/


    void updateThreadFinished();
private:
    Ui::MainWindow *ui;
    //QThread *_updateThread;

    int _newCount;
    int _deleteCount;

    QPointer<QThread> _updateThread;
    GGS::UpdateSystem::UpdateManagerWorker *_updateManagerWorker;
    //QNetworkAccessManager * nam;
    //GGS::UpdateSystem::UpdateManager *manager;
    //GGS::Extractor::SevenZipExtactor extractor;
    //GGS::Downloader::DownloadManager downloader;
    //GGS::UpdateSystem::UpdateInfoGetter updateInfoGetter;

    //GGS::Hasher::Md5FileHasher hasher;
    //GGS::Downloader::DownloadManager *downloader2;
    //GGS::Downloader::MultiFileDownloader multi;
    //GGS::Downloader::MultiFileDownloaderWithExtracter multi2;
    // 
    _CrtMemState beginMemoryState;
    bool _leaksFound;

    int _checkCount;
    void startCheckUpdate();

    void restartApplication();

    void startMemoryCheck()
    {
      this->_leaksFound = false;
      _CrtMemCheckpoint(&beginMemoryState);
    }

    void finishMemoryCheck()
    {
      // only check for memory leaks if the test did not end in a failure
      _CrtMemState endingMemoryState; // holds the current memory state (state during destruction)
      _CrtMemState memoryStateDiff;   // holds the difference between states during construction and destruction

      _CrtMemCheckpoint(&endingMemoryState);

      // if there are differences between the memory state at beginning and end, then there are memory leaks
      if (_CrtMemDifference(&memoryStateDiff, &beginMemoryState, &endingMemoryState))
      {
        _CrtMemDumpAllObjectsSince(&memoryStateDiff);
        _CrtMemDumpStatistics(&memoryStateDiff);

        this->_leaksFound = true;
      }
    }
};

#endif // MAINWINDOW_H
