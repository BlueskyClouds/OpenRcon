/*
 * Copyright (C) 2016 The OpenRcon Project.
 *
 * This file is part of OpenRcon.
 *
 * OpenRcon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenRcon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>
#include <QSettings>

#include "ServerManager.h"
#include "ServerEntry.h"
#include "GameManager.h"

ServerManager *ServerManager::instance = nullptr;

ServerManager::ServerManager(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings(APP_NAME, APP_NAME, this);

    // Load the stored servers.
    readSettings();
}

ServerManager::~ServerManager()
{
    writeSettings();

    delete settings;
}

ServerManager *ServerManager::getInstance(QObject *parent)
{
    if (!instance) {
        instance = new ServerManager(parent);
    }

    return instance;
}

void ServerManager::readSettings()
{
    settings->beginGroup("ServerManager");
        int size = settings->beginReadArray("ServerEntries");

        for (int i = 0; i < size; i++) {
            settings->setArrayIndex(i);

            int gameIndex = settings->value("game").toInt();

            if (GameManager::isGameSupported(gameIndex)) {
                ServerEntry *serverEntry = new ServerEntry(
                    GameManager::toGameType(gameIndex),
                    settings->value("name").toString(),
                    settings->value("host").toString(),
                    settings->value("port").toInt(),
                    settings->value("password").toString(),
                    settings->value("autoconnect").toBool()
                );

                serverList.append(serverEntry);
            } else {
                qDebug() << tr("Tried to load server belonging to unsupported game type, removing...");
            }
        }

        settings->endArray();
    settings->endGroup();
}

void ServerManager::writeSettings()
{
    settings->beginGroup("ServerManager");
        settings->remove("ServerEntries");

        int size = serverList.size();
        settings->beginWriteArray("ServerEntries");
            for (int i = 0; i < size; i++) {
                settings->setArrayIndex(i);

                ServerEntry *serverEntry = serverList.at(i);
                settings->setValue("game", GameManager::toInt(serverEntry->getGameType()));
                settings->setValue("name", serverEntry->getName());
                settings->setValue("host", serverEntry->getHost());
                settings->setValue("port", serverEntry->getPort());
                settings->setValue("password", serverEntry->getPassword());
                settings->setValue("autoconnect", serverEntry->getAutoConnect());
            }
        settings->endArray();
    settings->endGroup();
}

ServerEntry *ServerManager::getServer(int index) const
{
    return serverList.at(index);
}

ServerEntry *ServerManager::getServer(ServerEntry *serverEntry) const
{
    return getServer(serverList.indexOf(serverEntry));
}

void ServerManager::setServers(const QList<ServerEntry*> &list)
{
    serverList.clear();
    serverList = list;
    writeSettings();

    emit (onServerUpdated());
}

QList<ServerEntry*> ServerManager::getServers() const
{
    return serverList;
}

QList<ServerEntry*> ServerManager::getServers(GameTypeEnum gameType) const
{
    QList<ServerEntry*> list;

    for (ServerEntry *serverEntry : serverList) {
        if (serverEntry->getGameType() == gameType) {
            list.append(serverEntry);
        }
    }

    return list;
}

void ServerManager::addServer(ServerEntry *serverEntry)
{
    serverList.append(serverEntry);

    emit (onServerUpdated());
}

void ServerManager::removeServer(int index)
{
    serverList.removeAt(index);

    emit (onServerUpdated());
}

void ServerManager::removeServer(ServerEntry *serverEntry)
{
    removeServer(serverList.indexOf(serverEntry));
}
