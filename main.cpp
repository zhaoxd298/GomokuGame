//#include <QtGui/QApplication>
#include <QApplication>
#include "gomokugame.h"
#include <QTextCodec>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb2312"));

    GomokuGame w;
    w.resize(1000, 800);
    w.show();
    
    return a.exec();
}
