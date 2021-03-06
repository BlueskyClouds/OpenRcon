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

#include <QString>
#include <QList>

#include "TeamScores.h"
#include "BF3ServerInfo.h"

BF3ServerInfo::BF3ServerInfo(const QString &serverName,
                             int playerCount,
                             int maxPlayerCount,
                             const QString &gameMode,
                             const QString &currentMap,
                             int roundsPlayed,
                             int roundsTotal,
                             const TeamScores &scores,
                             bool ranked,
                             bool punkBuster,
                             bool gamePassword,
                             int serverUpTime,
                             int roundTime,
                             const QString &gameIpAndPort,
                             const QString &punkBusterVersion,
                             bool joinQueueEnabled,
                             const QString &region,
                             const QString &closestPingSite,
                             const QString &country,
                             bool matchMakingEnabled) :
                   Frostbite2ServerInfo(serverName,
                                        playerCount,
                                        maxPlayerCount,
                                        gameMode,
                                        currentMap,
                                        roundsPlayed,
                                        roundsTotal,
                                        scores,
                                        ranked,
                                        punkBuster,
                                        gamePassword,
                                        serverUpTime,
                                        roundTime,
                                        gameIpAndPort,
                                        punkBusterVersion,
                                        joinQueueEnabled,
                                        region,
                                        closestPingSite,
                                        country),
                   matchMakingEnabled(matchMakingEnabled)
{

}

BF3ServerInfo::~BF3ServerInfo()
{

}

bool BF3ServerInfo::isMatchMakingEnabled() const
{
    return matchMakingEnabled;
}
