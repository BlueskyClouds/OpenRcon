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

#ifndef BF4SERVERINFO_H
#define BF4SERVERINFO_H

#include "Frostbite2ServerInfo.h"

class BF4ServerInfo : public Frostbite2ServerInfo
{
public:
    BF4ServerInfo(const QString &serverName,
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
                  int blazePlayerCount,
                  const QString &blazeGameState);
    ~BF4ServerInfo() final;

    int getBlazePlayerCount() const;
    QString getBlazeGameState() const;

private:
    int blazePlayerCount;
    QString blazeGameState;

};

#endif // BF4SERVERINFO_H
