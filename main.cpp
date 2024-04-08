#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <fstream>
#include <QDebug>
#include <QDir>

#include "song.h"
#include "repository.h"
#include "file_repository.h"
#include "controller.h"
#include "playlist.h"

int main(int argc, char *argv[])
{
    SongTest::testSong();
    RepoTest::testRepo();
    //FileRepoTest::testFileRepo();
    ControllerTest::testController();
    PlaylistTest::testPlayList();

    QString currentPath = QDir::currentPath();
    qDebug() << "Current working directory:" << currentPath;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
