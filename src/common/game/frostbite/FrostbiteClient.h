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

#ifndef FROSTBITECLIENT_H
#define FROSTBITECLIENT_H

#include <QMap>

#include "Client.h"
#include "FrostbiteConnection.h"
#include "Frostbite2CommandHandler.h"

class QString;
class QByteArray;

class ServerEntry;

class FrostbiteClient : public Client
{
    Q_OBJECT

public:
    FrostbiteClient(ServerEntry *serverEntry, Frostbite2CommandHandler *commandHandler, QObject *parent = nullptr);
    virtual ~FrostbiteClient();

    FrostbiteConnection *getConnection() final {
        return connection;
    }

    virtual Frostbite2CommandHandler *getCommandHandler() override {
        return commandHandler;
    }

    void connectToHost();
    void disconnectFromHost();
    QString getVersionFromBuild(int build);

protected:
    FrostbiteConnection *connection;
    Frostbite2CommandHandler *commandHandler;

    QMap<int, QString> versionMap;

public slots:
    void onConnected();
    void onLoginHashedCommand(const QByteArray &salt);
    void onLoginHashedCommand(bool auth);
    void onVersionCommand(const QString &type, int build);

};

#endif // FROSTBITECLIENT_H
