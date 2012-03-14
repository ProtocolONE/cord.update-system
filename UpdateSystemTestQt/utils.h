#ifndef UTILS_H
#define UTILS_H
 
#include <QString>
 
class FileUtils
{
public:
    static bool removeDir(const QString &dirName);
};
 
#endif // UTILS_H