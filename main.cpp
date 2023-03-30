#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QFile file(":/DxUI.qss");
    if (file.open(QFile::ReadOnly)){
        QString qss = file.readAll();
        a.setStyleSheet(qss);
        file.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
