#pragma once
 
#include <QString>
#include <QDir>
 
class Utils
{
public:
    static bool removeDir(const QString &dirName);
    static bool removeDir(const QDir &dirName);
};
 