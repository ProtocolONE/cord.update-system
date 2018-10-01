#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
 
#include "Utils.h"
 
/*!
   Delete a directory along with all of its contents.
 
   \param dirName Path of directory to remove.
   \return true on success; false on error.
*/
bool Utils::removeDir(const QString &dirName){
    bool result = true;
    QDir dir(dirName);
 
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
 
            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
 
    return result;
}

bool Utils::removeDir(const QDir &dirName){
  return removeDir(dirName.absolutePath());
}

