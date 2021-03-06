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

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

class QString;
template<class T>
class QList;

class GameEntry;
enum class GameTypeEnum;
class ServerEntry;

class GameManager : public QObject
{
    Q_OBJECT

public:
    static bool isGameSupported(int gameId);
    static GameEntry getGame(GameTypeEnum gameType);
    static GameEntry getGame(int gameId);
    static GameEntry getGame(const QString &gamePrefix);
    static QList<GameEntry> getGames();
    static int toInt(GameTypeEnum gameType);
    static GameTypeEnum toGameType(int gameTypeId);
    static GameTypeEnum toGameType(const QString &gameType);

private: 
    static QList<GameEntry> gameList;

};

#endif // GAMEMANAGER_H
