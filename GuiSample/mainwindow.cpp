#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
  QString str = QString::fromUtf8("ответ получен");
  this->ui->textEdit->append(str);

  QString str2 = QString::fromUtf8(reply->readAll());
  this->ui->textEdit->append(str2);
}

void MainWindow::on_pushButton_clicked()
{
  this->_checkCount = 0;
  this->_newCount = 0;
  this->_deleteCount = 0;

  this->startMemoryCheck();

  this->startCheckUpdate();
  this->ui->updateProgressBar->setMinimum(0);
  this->ui->updateProgressBar->setMaximum(100);
  this->ui->updateProgressBar->setValue(0);
}

void MainWindow::slotFileDownloadString( QString path )
{
  this->ui->textEdit->append(path);
}

void MainWindow::slotAllCompleted(bool isNeedRestart)
{
  if(isNeedRestart) {
    this->ui->textEdit->append("Update found.");
    this->restartApplication();
  } else {
    this->ui->textEdit->append("Update not found.");
  }
}

void MainWindow::updateThreadFinished()
{
  delete this->_updateThread;
}

void MainWindow::startCheckUpdate()
{
  this->_updateThread = new QThread();
  this->_updateManagerWorker = new GGS::UpdateSystem::UpdateManagerWorker(0);
  this->_updateManagerWorker->moveToThread(this->_updateThread);
  connect(
    this->_updateThread, SIGNAL(finished()), 
    this, SLOT(updateThreadFinished()));

  connect(
    this->_updateManagerWorker, SIGNAL(allCompleted(bool)), 
    this, SLOT(slotAllCompleted(bool)));

  connect(
    this->_updateManagerWorker, SIGNAL(fileDownloadString(QString)), 
    this, SLOT(slotFileDownloadString(QString)));

  connect(
    this->_updateManagerWorker, SIGNAL(downloadUpdateProgress(quint64, quint64)), 
    this, SLOT(slotDownloadUpdateProgress(quint64, quint64)));

  connect(
    this->_updateManagerWorker, SIGNAL(downloadUpdateWarning(GGS::Downloader::DownloadResults)), 
    this, SLOT(slotDownloadUpdateWarning(GGS::Downloader::DownloadResults)));

  connect(
    this->_updateManagerWorker, SIGNAL(fatalError()), 
    this, SLOT(slotFatalError()));


  this->_updateThread->start();
  QMetaObject::invokeMethod(this->_updateManagerWorker, "init", Qt::QueuedConnection);
  QMetaObject::invokeMethod(this->_updateManagerWorker, "checkUpdate", Qt::QueuedConnection);
}

void MainWindow::restartApplication()
{
  QString path = QCoreApplication::applicationFilePath();
  QString dir = QCoreApplication::applicationDirPath();
  QProcess *process = new QProcess(0);
  process->start(path, QStringList() << dir);
  process->waitForStarted();
  QCoreApplication::exit();
}

void MainWindow::slotDownloadUpdateProgress( quint64 currentSize, quint64 totalSize )
{
  //  this->ui->textEdit->append( QString("Progress: %1 / %2").arg(currentSize).arg(totalSize) );
  int progress = int(100 * double(currentSize) / double(totalSize));
  this->ui->updateProgressBar->setValue(progress);
}

void MainWindow::slotDownloadUpdateWarning( GGS::Downloader::DownloadResults error )
{
  this->ui->textEdit->append("Some warning");
}

void MainWindow::slotFatalError()
{
  this->ui->textEdit->append("Some fatal error");
}

