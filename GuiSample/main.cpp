#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeContext>

#ifdef _DEBUG
#pragma comment(lib, "UpdateSystemX86d.lib")
#else
#pragma comment(lib, "UpdateSystemX86.lib")
#endif 

//#include "updatemanagerviewmodel.h"

#include <UpdateSystemViewModel/updatemanagerviewmodel>
/*!
    Устанавливает текстовые кодеки для кодировки \a codecName.
*/

void initTextCodecs(const char *codecName)
{
    QTextCodec *codec = QTextCodec::codecForName(codecName);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
}

int main(int argc, char *argv[])
{
    initTextCodecs("UTF-8");
	
    QString tmp(QObject::tr("123"));
    QApplication a(argc, argv);
	  qmlRegisterType<GGS::UpdateSystem::UpdateManagerViewModel>("qGNA.Library", 1, 0, "UpdateManagerViewModel");

	  QUrl url(QUrl::fromLocalFile("qGNA_Main.qml"));
    QDeclarativeView *nQMLContainer = new QDeclarativeView(url);       
    nQMLContainer->setAlignment(Qt::AlignCenter);                                                                               
    nQMLContainer->setResizeMode(QDeclarativeView::SizeRootObjectToView);     
    nQMLContainer->showNormal();
	
    return a.exec();
}
