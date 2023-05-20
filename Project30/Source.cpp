#mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#define WINDOW_WIDTH "windowwidth"
#define WINDOW_HEIGHT "windowheight"
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Test QMap v15.1");
    filePath = "../test1/config.ini";
    configDelimiter = "=";
    configMap.insert(WINDOW_WIDTH, "555");
    configMap.insert(WINDOW_HEIGHT, "333");
    QFile configFile(filePath);
    configFile.open(QFile::ReadOnly);
    while (!configFile.atEnd()) {
        configLine = configFile.readLine();
        int posDelimited = configLine.indexOf(configDelimiter);
        configKey = configLine.left(posDelimited);
        configValue = configLine.right(configLine.size() - posDelimited - 1);
        qDebug() << "Config Line: " << configLine;
        qDebug() << "Config Key: " << configKey;
        qDebug() << "Config Value: " << configValue;
        if (configMap.count(configKey) > 0) {
            configMap[configKey] = configValue;
        }
    }
    widthWindow = configMap[WINDOW_WIDTH].toInt();
    heightWindow = configMap[WINDOW_HEIGHT].toInt();
    resize(widthWindow, heightWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#config.ini
windowwidth = 600
windowheight = 300

#mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QString filePath;
    QString configLine;
    QString configKey;
    QString configValue;
    QString configDelimiter;
    QMap <QString, QString> configMap;
    int widthWindow;
    int heightWindow;

};

#endif // MAINWINDOW_H

#test1.pro
#-------------------------------------------------
#
# Project created by QtCreator 2023 - 03 - 17T08:28 : 18
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

TARGET = test1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated(the exact warnings
    # depend on your compiler).Please consult the documentation of the
    # deprecated API in order to know how to port your code away from it.
    DEFINES += QT_DEPRECATED_WARNINGS

    # You can also make your code fail to compile if you use deprecated APIs.
    # In order to do so, uncomment the following line.
    # You can also select to disable deprecated APIs only up to a certain version of Qt.
    #DEFINES += QT_DISABLE_DEPRECATED_BEFORE = 0x060000    # disables all the APIs deprecated before Qt 6.0.0

    CONFIG += \
    c++11 \
    console

    SOURCES += \
    main.cpp \
    mainwindow.cpp

    HEADERS += \
    mainwindow.h

    FORMS += \
    mainwindow.ui

    # Default rules for deployment.
    qnx: target.path = / tmp / $${ TARGET } / bin
    else: unix:!android : target.path = / opt / $${ TARGET } / bin
    !isEmpty(target.path) : INSTALLS += target

    DISTFILES += \
    config.ini

    #main.cpp
#include "mainwindow.h"
#include <QApplication>

    int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
