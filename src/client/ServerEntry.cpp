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

 * You should have received a copy of the GNU General Public License
 * along with OpenRcon.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QString>

#include "ServerEntry.h"
#include "GameType.h"

ServerEntry::ServerEntry()
{

}

ServerEntry::ServerEntry(GameTypeEnum gameType, const QString &name, const QString &host, int port, const QString &password, bool autoConnect) :
    gameType(gameType),
    name(name),
    host(host),
    port(port),
    password(password),
    autoConnect(autoConnect)
{

}

ServerEntry::~ServerEntry()
{

}

GameTypeEnum ServerEntry::getGameType() const
{
    return gameType;
}

QString ServerEntry::getName() const
{
    return name;
}

QString ServerEntry::getHost() const
{
    return host;
}

int ServerEntry::getPort() const
{
    return port;
}

QString ServerEntry::getPassword() const
{
    return password;
}

bool ServerEntry::getAutoConnect() const
{
    return autoConnect;
}

void ServerEntry::setAutoConnect(bool autoConnect)
{
    this->autoConnect = autoConnect;
}
