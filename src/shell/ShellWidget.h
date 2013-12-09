#pragma once

#include <QWidget>
#include "global/global.h"

QT_BEGIN_NAMESPACE
class QAction;
class QProgressBar;
class QToolButton;
QT_END_NAMESPACE

#include "core/IServer.h"
#include "core/events/EventsInfo.hpp"

namespace fastoredis
{
    class RedisShell;
    class IconLabel;
    class ShellWidget
            : public QWidget
    {
        Q_OBJECT
    public:
        typedef QWidget base_class;
        ShellWidget(const IServerPtr &server, const QString &filePath = QString(), QWidget* parent = 0);

        const IServerPtr &server() const;
        QString text() const;

    Q_SIGNALS:
        void startedExecute(const EventsInfo::ExecuteInfoRequest &req);
        void finishedExecute(const EventsInfo::ExecuteInfoResponce &res);

    public Q_SLOTS:
        void setText(const QString& text);

    private Q_SLOTS:
        void execute();
        void stop();
        void connectToServer();
        void disconnectFromServer();
        void loadFromFile();
        bool loadFromFile(const QString &path);
        void saveToFileAs();
        void saveToFile();

        void startConnect(const EventsInfo::ConnectInfoRequest &req);
        void finishConnect(const EventsInfo::ConnectInfoResponce &res);
        void startDisconnect(const EventsInfo::DisonnectInfoRequest &req);
        void finishDisconnect(const EventsInfo::DisConnectInfoResponce &res);        

        void progressChange(const EventsInfo::ProgressResponceInfo &res);

    private:
        void syncConnectionActions();

        const IServerPtr _server;
        QAction *_executeAction;
        QAction *_connectAction;
        QAction *_disConnectAction;
        QAction *_loadAction;
        QAction *_saveAction;
        QAction *_saveAsAction;


        IconLabel *_serverName;
        RedisShell *_input;
        QProgressBar *_workProgressBar;
        QString _filePath;
    };
}
