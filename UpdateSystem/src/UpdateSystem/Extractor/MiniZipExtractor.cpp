#include <UpdateSystem/Extractor/MiniZipExtractor.h>

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QTCore/QDir>
#include <Windows.h>
#include <memory>
#include <codecvt>

#include "minizip/unzip.h"
#include "minizip/iowin32.h"

#define DEBUG_LOG qDebug() << __FILE__ << __LINE__ << __FUNCTION__

using namespace P1::Extractor;

MiniZipExtractor::MiniZipExtractor(QObject *parent)
  : QObject(parent)
{
}

MiniZipExtractor::~MiniZipExtractor()
{
}

ExtractionResult MiniZipExtractor::extract(const QString& archivePath, const QString& extractDirectory)
{
  if (!QFile::exists(archivePath))
    return NoArchive;

  zlib_filefunc64_def ffunc;
  fill_win32_filefunc64W(&ffunc);

  unzFile uf = unzOpen2_64(archivePath.toStdWString().c_str(), &ffunc);
  if (uf == nullptr) {
    DEBUG_LOG << "Cannot open archive file " << archivePath;
    return BadArchive;
  }

  using UniqueZipFile = std::unique_ptr<std::remove_pointer<unzFile>::type, decltype(&unzClose)>;
  UniqueZipFile uniqueZipFile(uf, unzClose);

  unz_global_info64 gi = {0};
  int err = unzGetGlobalInfo64(uf, &gi);
  if (err != UNZ_OK) {
    DEBUG_LOG << "unzGetGlobalInfo failed: " << err;
    return BadArchive;
  }
    
  for (int i = 0; i < gi.number_entry; i++)
  {
    ExtractionResult result = this->extractFile(uf, extractDirectory);
    if (NoError != result)
      return NoError;

    if ((i + 1) < gi.number_entry) {
      err = unzGoToNextFile(uf);
      if (err != UNZ_OK) {
        DEBUG_LOG << "unzGoToNextFile failed: " << err;
        return BadArchive;
      }
    }
  }

  return P1::Extractor::NoError;
}

ExtractionResult MiniZipExtractor::extractFile(unzFile uf, const QString& extractDirectory) const
{
  unz_file_info64 file_info;
  std::vector<char> filename;
  filename.resize(MAX_PATH);
  std::vector<char> extraFields;
  extraFields.resize(1024);

  int err = unzGetCurrentFileInfo64(uf, &file_info, filename.data(), filename.size(), extraFields.data(), extraFields.size(), nullptr, 0);
  if (err != UNZ_OK) {
    DEBUG_LOG << "unzGetCurrentFileInfo failed: " << err;
    return BadArchive;
  }

  QString destFilename = filename.data();

  if (file_info.size_file_extra > 0) {

    // Read extra fields to obtain unicode filename
    // see https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT (4.5, 4.6.9)

    const char* p = extraFields.data();
    while (p <= extraFields.data() + file_info.size_file_extra - sizeof(short)) {
      
      const unsigned short* d = reinterpret_cast<const unsigned short*>(p);

      if (*d == 0x7075) {
        
        unsigned short fnsize = d[1] - 1 - sizeof(uint32_t);
        p += sizeof(short) + sizeof(short) + 1 + sizeof(uint32_t);
        std::string fname(p, p + fnsize);
        std::wstring wfname = this->a2w(fname);
        destFilename = QString::fromStdWString(wfname.c_str());
        break;
      }
      else {
        p += d[1] + sizeof(short) + sizeof(short);
      }
    }
  }
  
  err = unzOpenCurrentFile(uf);
  if (err != UNZ_OK) {
      DEBUG_LOG << "unzOpenCurrentFile failed: " << err;
      return BadArchive;
  }

  using UniqueCurrentFile = std::unique_ptr<std::remove_pointer<unzFile>::type, decltype(&unzCloseCurrentFile)>;
  UniqueCurrentFile uniqueCurrentFile(uf, unzCloseCurrentFile);

  QString destPath = QDir::toNativeSeparators(extractDirectory) + destFilename;

  QFile file(destPath);
  if (!file.open(QIODevice::OpenModeFlag::WriteOnly | QIODevice::OpenModeFlag::Truncate)) {
    DEBUG_LOG << "Cannot create file " << destPath;
    DEBUG_LOG << "error: " << file.errorString();
    return WriteError;
  }

  std::vector<char> buf;
  int num = 0;
  do {

    buf.resize(SIZE_BUF);
    num = unzReadCurrentFile(uf, buf.data(), buf.size());
    if (num < 0) {

      DEBUG_LOG << "unzReadCurrentFile failed: " << num;
      return BadArchive;
    }
    else if (num > 0) {

      file.write(buf.data(), num);
    }

  } while (num > 0);

  return NoError;
}

std::wstring MiniZipExtractor::a2w(const std::string& str) const
{
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
  return conversion.from_bytes(str);
}
