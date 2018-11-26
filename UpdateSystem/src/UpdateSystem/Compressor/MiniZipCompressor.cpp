#include <UpdateSystem/Compressor/MiniZipCompressor.h>

#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QTCore/QDir>
#include <QTCore/QDebug>
#include <Windows.h>
#include <memory>

#include "minizip/zip.h"
#include "minizip/iowin32.h"

using namespace P1::Compressor;

MiniZipCompressor::MiniZipCompressor(QObject *parent)
  : QObject(parent), _level(Best), _numThreads(1)
{
}

MiniZipCompressor::~MiniZipCompressor()
{

}

void MiniZipCompressor::setNumThreads(int threads)
{
  this->_numThreads = threads;
}

void MiniZipCompressor::setCompressionLevel(CompressionLevel level)
{
  this->_level = level;
}

template <typename T, typename D>
class Defer
{
public:
  Defer(T t, D d) : _t(t), _d(d) {
  }

  ~Defer() {
    _d(_t);
  }

  void reset(T t ) {
    this->_t = t ;
  }

private:
  T _t;
  D _d;
};

CompressorInterface::CompressionResult MiniZipCompressor::compressFile(const QString& sourcePath, const QString& targetPath)
{
  if (!QFile::exists(sourcePath))
    return CompressorInterface::ReadError;

  QString sourcePath2 = QDir::toNativeSeparators(sourcePath);
  QString targetPath2 = QDir::toNativeSeparators(targetPath);

  QFileInfo info(targetPath2);
  QDir archivePathDir = info.dir();
  if (!archivePathDir.exists()) {
      QString pathToFile = info.absolutePath();
      archivePathDir.mkpath(pathToFile);
  }

  QFileInfo sourceInfo(sourcePath2);
  QString sourceName = sourceInfo.fileName();

  zlib_filefunc64_def ffunc;
  fill_win32_filefunc64W(&ffunc);

  zipFile zf = zipOpen2_64(targetPath.toStdWString().c_str(), APPEND_STATUS_CREATE, nullptr, &ffunc);
  if (zf == nullptr) {
    DEBUG_LOG << "Cannot create archive file " << targetPath2;
    return WriteError;
  }

  // To auto delete archiver file when error
  auto deleter = [zf](QString* name) {
      zipClose(zf, nullptr);
      ::DeleteFileW(name->toStdWString().c_str());
      delete name;
  };

  using ZipDefer = std::unique_ptr<QString, decltype(deleter)>;
  ZipDefer zipDefer(new QString(targetPath2), deleter);

  zip_fileinfo zi = {0};

  int err = zipOpenNewFileInZip4_64(zf, sourceName.toUtf8(), &zi, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, static_cast<int>(this->_level), 0, MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, nullptr, 0, 0, 1<<11, 1);
  if (err != ZIP_OK) {
      DEBUG_LOG << "zipOpenNewFileInZip error: " << err;
      return WriteError;
  }

  QFile file(sourcePath);
  if (!file.open(QIODevice::OpenModeFlag::ReadOnly)) {
      DEBUG_LOG << "Open source file error: " << file.errorString();
      return ReadError;
  }

  QByteArray buff;
  do
  {
      buff = file.read(SIZE_BUF);
      if (buff.size() < SIZE_BUF && !file.atEnd()) {
        DEBUG_LOG << "Error in reading: " << file.errorString();
        return ReadError;
      }

      if (buff.size() > 0) {
          err = zipWriteInFileInZip(zf, buff.data(), buff.size());
          if (err < 0) {
              DEBUG_LOG << "Error in writing: " << err;
              return WriteError;
          }
      }
  } while (buff.size() > 0);

  file.close();
  zipDefer.release();
  zipClose(zf, nullptr);

  return CompressorInterface::NoError;
}