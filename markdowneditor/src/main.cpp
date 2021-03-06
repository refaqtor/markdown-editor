﻿#include "document.h"
#include "utils.h"
#include "filemodel.h"
#include "dragarea.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtWebEngine/QtWebEngine>
#include <QIcon>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication app(argc, argv);
    qInfo()<<"args:"<<app.arguments();
    QtWebEngine::initialize();
//    if(app.arguments().contains("--log")){
//        is_loged = true;
//    }

//    qInstallMessageHandler(FileMessageHandler);

    app.setWindowIcon(QIcon(":/logo/images/32x32/markdown-editor-logo.png"));

    QQmlApplicationEngine engine;
    qmlRegisterType<Document>("cxl.normal", 1, 0, "Document");
    qmlRegisterType<DragArea>("cxl.normal", 1, 0, "DragArea");
    qmlRegisterType<Utils>("cxl.normal", 1, 0, "Utils");
    qmlRegisterUncreatableType<FileModel>("cxl.normal", 1, 0,
                                                       "FileModel", "Cannot create a FileSystemModel instance.");

    FileModel *file_model = new FileModel();
    engine.rootContext()->setContextProperty("fileModel", file_model);
    if(app.arguments().length() == 2){
        engine.rootContext()->setContextProperty("argPath", app.arguments().last());
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    file_model->setParent(engine.rootObjects().first());
    return app.exec();
}
